#include <numc.h>
#include <unity.h>

void
test_au8_1D_1D_add() {
  uint8_t a_d[] = {0,1,2,3};
  uint8_t b_d[] = {4,5,6,7};
  au8* a = au8_new_1D_d(4, a_d);
  au8* b = au8_new_1D_d(4, b_d);
  au8* c = au8_add(a, b);
  TEST_ASSERT_NOT_NULL(c);
  TEST_ASSERT_EQUAL(4, c->n);
  TEST_ASSERT_EQUAL(1, c->dim);
  TEST_ASSERT_NOT_NULL(c->shape);
  TEST_ASSERT_EQUAL(4, c->shape[0]);
  TEST_ASSERT_NOT_NULL(c->d);
  TEST_ASSERT_EQUAL(4, c->d[0]);
  TEST_ASSERT_EQUAL(6, c->d[1]);
  TEST_ASSERT_EQUAL(8, c->d[2]);
  TEST_ASSERT_EQUAL(10,c->d[3]);
}

int main() {
  UNITY_BEGIN();
  RUN_TEST(test_au8_1D_1D_add);
  return UNITY_END();
}
