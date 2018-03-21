#ifndef TEST_H
#define TEST_H
#define TEST_AU8_DIM_N(a, adim, an) TEST_AU8_DIM_N_START(a, adim, an, 0)
#define TEST_AU8_DIM_N_START(a, adim, an, astart) \
  TEST_ASSERT_NOT_NULL(a);\
  TEST_ASSERT_NOT_NULL(a->d);\
  TEST_ASSERT_NOT_NULL(a->h.shape);\
  TEST_ASSERT_NOT_NULL(a->h.step);\
  TEST_ASSERT_NOT_NULL(a->h.ostep);\
  TEST_ASSERT_EQUAL(adim, a->h.dim);\
  TEST_ASSERT_EQUAL(an, a->h.n);\
  TEST_ASSERT_EQUAL(astart, a->h.start);\
  TEST_ASSERT_EQUAL(1, a->h.bitsize);
#endif
