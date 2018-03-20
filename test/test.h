#ifndef TEST_H
#define TEST_H
#define TEST_AU8_DIM_N(a, adim, an) TEST_AU8_DIM_N_START(a, adim, an, 0)
#define TEST_AU8_DIM_N_START(a, adim, an, astart) \
  TEST_ASSERT_NOT_NULL(a);\
  TEST_ASSERT_NOT_NULL(a->d);\
  TEST_ASSERT_NOT_NULL(a->shape);\
  TEST_ASSERT_NOT_NULL(a->step);\
  TEST_ASSERT_NOT_NULL(a->ostep);\
  TEST_ASSERT_EQUAL(adim, a->dim);\
  TEST_ASSERT_EQUAL(an, a->n);\
  TEST_ASSERT_EQUAL(astart, a->start);
#endif
