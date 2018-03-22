#include <unity.h>
#include <nc/core.h>

static void
test_wfm_read() {
  wfm* w = wfm_read("../rsc/signal.bin");
  TEST_ASSERT_EQUAL(1, w->header.n);
  TEST_ASSERT_NOT_NULL(w->waveforms);
  TEST_ASSERT_EQUAL(4000000, w->waveforms[0].header.points);
  TEST_ASSERT_EQUAL(WFM_NORMAL, w->waveforms[0].header.type);
  double x = WFM_TIMESTAMP(1, w->waveforms[0].header);
  TEST_ASSERT_NOT_EQUAL(0, x);
  wfm_destroy(w);
}

int main() {
  UNITY_BEGIN();
  RUN_TEST(test_wfm_read);
  return UNITY_END();
}
