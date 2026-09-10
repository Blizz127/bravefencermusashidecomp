"""Exact MTC2/MFC2 leaf with real owners; fixture-only scalar inputs."""
import pytest
from test_gte_init_source import _run_gte_source_probe


@pytest.mark.parametrize("variant", ["baseline", "immediate_load_mutant", "sub_swap_mutant", "srav_mutant", "div_site_mutant", "mvmva_dispatch_mutant", "swc2_site_mutant", "camera2_site_mutant", "sanitizers"])
def test_gte_data_source(tmp_path, variant):
    def mvmva_dispatch(source):
        old = "} else if (rs == 18u) {"
        assert source.count(old) == 1
        return source.replace(old, "} else if (rs == 19u) {")
    def swc2_site(source):
        old = "cpu->pc != 0x80048e98u || instruction != 0xe88b0010u ||"
        assert source.count(old) == 1
        return source.replace(old, "cpu->pc != 0x80048e98u || instruction != 0xe88b0011u ||")
    def camera2_site(source):
        old = "{0x80048598u, 0x488b4800u, 0}"
        assert source.count(old) == 1
        return source.replace(old, "{0x80048598u, 0x488b4801u, 0}")
    def immediate(source):
        old = "cpu->gte_load_pending = 1;"
        assert source.count(old) == 1
        return source.replace(old, old + "\n        cpu->r[rt] = scheduled_gte_load;")
    def sub_swap(source):
        old = "diff = (int64_t)(int32_t)cpu->r[rs] - (int64_t)(int32_t)cpu->r[rt];"
        assert source.count(old) == 1
        return source.replace(old, "diff = (int64_t)(int32_t)cpu->r[rt] - (int64_t)(int32_t)cpu->r[rs];")
    def srav(source):
        old = "cpu->r[rd] = formatter_sra(cpu->r[rt], amount);"
        assert source.count(old) == 1
        return source.replace(old, "cpu->r[rd] = cpu->r[rt] >> amount;")
    def div_site(source):
        old = "(cpu->pc == 0x80054070u && instruction == 0x0212001au)"
        assert source.count(old) == 1
        return source.replace(old, "(cpu->pc == 0x80054070u && instruction == 0x0212001bu)")
    mutate = {"immediate_load_mutant": immediate, "sub_swap_mutant": sub_swap, "srav_mutant": srav, "div_site_mutant": div_site, "mvmva_dispatch_mutant": mvmva_dispatch, "swc2_site_mutant": swc2_site, "camera2_site_mutant": camera2_site}.get(variant)
    _run_gte_source_probe(tmp_path, variant, "gte_data_source_probe.c",
        "GTE_DATA_SOURCE_PASS fixture_only=1 positive_sqrt=298 second_caller=540D8 light_case=53EA0 camera_out0=00400010 camera2_out0=0000ffff\n",
        ((0x80047d3c, 33), (0x80053f6c, 245), (0x80053e28, 49), (0x80048d9c, 68), (0x800484ec, 88)),
        mutate_formatter=mutate, real_gte=True)
