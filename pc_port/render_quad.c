/* Draw one flat quad and report the pixels that came back.
 *
 * This proves the path from decomp-owned C to actual pixels: ordering table,
 * primitive, DrawOTag, then a read back out of VRAM. It is not a game loop and
 * draws a single frame.
 *
 * The program only samples and prints. Judging the colours is left to the
 * harness, so the comparison logic stays unit-tested in tools/vram_pixel.py
 * rather than hiding in a binary that needs a display to run.
 */

#include <stdio.h>

#include "PsyX/PsyX_public.h"
#include "PsyX/PsyX_render.h"
#include "psx/libgte.h"
#include "psx/libgpu.h"
#include "psx/libetc.h"

#define SCREEN_W 320
#define SCREEN_H 240
#define OT_LENGTH 8

/* Quad corners, well inside the screen so the sample points are unambiguous. */
#define QUAD_X0 80
#define QUAD_Y0 60
#define QUAD_X1 240
#define QUAD_Y1 180

/* Red quad on a black field. Only the top five bits of each component survive
 * into VRAM, so 248 is the largest value that round-trips exactly. */
#define QUAD_R 248
#define QUAD_G 0
#define QUAD_B 0

static DISPENV g_disp;
static DRAWENV g_draw;
/* An ordering table entry is an OT_TAG, not a u_long.
 *
 * PS1 source declares these as `u_long ot[N]` because a tag was exactly one
 * 32-bit word. On x86-64 an OT_TAG is 12 bytes: DECLARE_P_ADDR carries a
 * uintptr_t plus bitfields. Declaring the table as u_long[N] gives ClearOTagR a
 * buffer barely half the size it writes, which corrupts memory and crashes.
 * Every ordering table in ported code has to be typed this way. */
static OT_TAG g_ot[OT_LENGTH];
static POLY_F4 g_quad;

static unsigned short sample(int x, int y) {
    unsigned short pixel = 0;
    GR_ReadVRAM(&pixel, x, y, 1, 1);
    return pixel;
}

int main(void) {
    PsyX_Initialise("musashi_render_quad", SCREEN_W, SCREEN_H, 0);

    ResetGraph(0);
    SetDefDispEnv(&g_disp, 0, 0, SCREEN_W, SCREEN_H);
    SetDefDrawEnv(&g_draw, 0, 0, SCREEN_W, SCREEN_H);
    /* Clear to black each frame so the outside sample is unambiguous. */
    g_draw.isbg = 1;
    setRGB0(&g_draw, 0, 0, 0);
    PutDispEnv(&g_disp);
    PutDrawEnv(&g_draw);
    SetDispMask(1);

    ClearOTagR((u_long *)g_ot, OT_LENGTH);

    setPolyF4(&g_quad);
    setRGB0(&g_quad, QUAD_R, QUAD_G, QUAD_B);
    setXY4(&g_quad,
           QUAD_X0, QUAD_Y0,
           QUAD_X1, QUAD_Y0,
           QUAD_X0, QUAD_Y1,
           QUAD_X1, QUAD_Y1);
    /* ClearOTagR chains ot[i] -> ot[i-1], so ot[0] is the terminator and the
     * head is the last entry. Drawing from ot[0] walks nothing. */
    addPrim(&g_ot[1], &g_quad);

    DrawOTag((u_long *)&g_ot[OT_LENGTH - 1]);
    DrawSync(0);

    /* Pull the rendered frame into the VRAM mirror that GR_ReadVRAM reads. */
    GR_StoreFrameBuffer(0, 0, SCREEN_W, SCREEN_H);
    GR_ReadFramebufferDataToVRAM();

    printf("PIXEL inside 0x%04X\n", sample((QUAD_X0 + QUAD_X1) / 2, (QUAD_Y0 + QUAD_Y1) / 2));
    printf("PIXEL outside 0x%04X\n", sample(8, 8));
    fflush(stdout);

    PsyX_Shutdown();
    return 0;
}
