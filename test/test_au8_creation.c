#include <numc.h>
#include <stdlib.h>
#include <unity.h>
#include <string.h>

void
test_au8_new() {
  au8* mat = au8_new();
  TEST_ASSERT_EQUAL(0, mat->n);
  TEST_ASSERT_EQUAL(0, mat->dim);
  TEST_ASSERT_NULL(mat->shape);
  TEST_ASSERT_NULL(mat->d);
  free(mat);
}

void
test_au8_new_dim() {
  au8* a = au8_new_dim(4);
  TEST_ASSERT_NOT_NULL(a);
  TEST_ASSERT_EQUAL(4, a->dim);
  TEST_ASSERT_NOT_NULL(a->shape);
  au8_destroy(a);
  a = NULL;
}

void
test_au8_new_shape() {
  nelem_t shape[] = {3,5,1,2};
  au8* a = au8_new_shape(4, shape);
  TEST_ASSERT_NOT_NULL(a);
  TEST_ASSERT_EQUAL(4, a->dim);
  TEST_ASSERT_NOT_NULL(a->shape);
  TEST_ASSERT_EQUAL(3, a->shape[0]);
  TEST_ASSERT_EQUAL(5, a->shape[1]);
  TEST_ASSERT_EQUAL(1, a->shape[2]);
  TEST_ASSERT_EQUAL(2, a->shape[3]);
  TEST_ASSERT_EQUAL(3*5*1*2, a->n);
  au8_destroy(a);
}

void
test_au8_new_like() {
  au8 *a = au8_new_1D(2), *b;
  uint8_t a_d[] = {1,2};
  au8_set(a, a_d);
  b = au8_new_like(a);
  TEST_ASSERT_NOT_NULL(b);
  TEST_ASSERT_NOT_NULL(b->d);
  TEST_ASSERT_NOT_NULL(b->shape);
  TEST_ASSERT_EQUAL(1,b->dim);
  TEST_ASSERT_EQUAL(2,b->n);
  TEST_ASSERT_EQUAL(2,b->shape[0]);
  au8_destroy(a);
  au8_destroy(b);
}

void
test_au8_zeros() {
  uint8_t i;
  nelem_t a_shape[] = {2, 3};
  au8 *a = au8_zeros(2, a_shape);
  TEST_ASSERT_NOT_NULL(a);
  TEST_ASSERT_NOT_NULL(a->shape);
  TEST_ASSERT_NOT_NULL(a->d);
  TEST_ASSERT_EQUAL(2, a->dim);
  TEST_ASSERT_EQUAL(2, a->shape[0]);
  TEST_ASSERT_EQUAL(3, a->shape[1]);
  for(i = 0; i < 6; i++) {
    TEST_ASSERT_EQUAL(0, a->d[i]);
  }
  au8_destroy(a);
}

void
test_au8_zeros_like() {
  uint64_t i;
  au8 *a = au8_new_1D(2), *b;
  uint8_t a_d[] = {1,2};
  au8_set(a, a_d);
  b = au8_zeros_like(a);
  TEST_ASSERT_NOT_NULL(b);
  TEST_ASSERT_NOT_NULL(b->d);
  TEST_ASSERT_NOT_NULL(b->shape);
  TEST_ASSERT_EQUAL(1,b->dim);
  TEST_ASSERT_EQUAL(2,b->n);
  TEST_ASSERT_EQUAL(2,b->shape[0]);
  for(i = 0; i < 2; i++) {
    TEST_ASSERT_EQUAL(0, b->d[i]);
  }
  au8_destroy(a);
  au8_destroy(b);
}

void
test_au8_ones() {
  uint8_t i;
  nelem_t a_shape[] = {2, 3};
  au8 *a = au8_ones(2, a_shape);
  TEST_ASSERT_NOT_NULL(a);
  TEST_ASSERT_NOT_NULL(a->shape);
  TEST_ASSERT_NOT_NULL(a->d);
  TEST_ASSERT_EQUAL(2, a->dim);
  TEST_ASSERT_EQUAL(2, a->shape[0]);
  TEST_ASSERT_EQUAL(3, a->shape[1]);
  for(i = 0; i < 6; i++) {
    TEST_ASSERT_EQUAL(1, a->d[i]);
  }
  au8_destroy(a);
}

void
test_au8_ones_like() {
  uint64_t i;
  au8 *a = au8_new_1D(2), *b;
  uint8_t a_d[] = {1,2};
  au8_set(a, a_d);
  b = au8_ones_like(a);
  TEST_ASSERT_NOT_NULL(b);
  TEST_ASSERT_NOT_NULL(b->d);
  TEST_ASSERT_NOT_NULL(b->shape);
  TEST_ASSERT_EQUAL(1,b->dim);
  TEST_ASSERT_EQUAL(2,b->n);
  TEST_ASSERT_EQUAL(2,b->shape[0]);
  for(i = 0; i < 2; i++) {
    TEST_ASSERT_EQUAL(1, b->d[i]);
  }
  au8_destroy(a);
  au8_destroy(b);
}

void
test_au8_new_1D_empty(){
  au8* mat = au8_new_1D(5);
  TEST_ASSERT_EQUAL(5, mat->n);
  TEST_ASSERT_EQUAL(1, mat->dim);
  TEST_ASSERT_EQUAL(5, mat->shape[0]);
  TEST_ASSERT_NOT_NULL(mat->d);
}

void
test_au8_new_1D_set() {
  au8* mat = au8_new_1D(5);
  uint8_t mat_d[] = {0,1,2,3,4};
  au8_set(mat, mat_d);
  TEST_ASSERT_EQUAL(5, mat->n);
  TEST_ASSERT_EQUAL(1, mat->dim);
  TEST_ASSERT_EQUAL(5, mat->shape[0]);
  TEST_ASSERT_NOT_NULL(mat->d);
  TEST_ASSERT_EQUAL_MEMORY(mat_d, mat->d, sizeof(uint8_t) * 5);
}

void
test_au8_new_1D_d() {
  au8* mat;
  uint8_t mat_d[] = {0,1,2,3,4};
  mat = au8_new_1D_d(5, mat_d);
  TEST_ASSERT_EQUAL(5, mat->n);
  TEST_ASSERT_EQUAL(1, mat->dim);
  TEST_ASSERT_NOT_NULL(mat->d);
  TEST_ASSERT_EQUAL_MEMORY(mat_d, mat->d, sizeof(uint8_t) * 5);
}

void
test_au8_1D_dot() {
  au8 *a, *b;
  uint8_t a_d[] = {0,1,2,3,4};
  uint8_t b_d[] = {5,6,7,8,9};
  uint32_t c;
  a = au8_new_1D_d(5,a_d);
  b = au8_new_1D_d(5,b_d);
  c = au8_dot(a,b);
  TEST_ASSERT_EQUAL(80, c);
}

void
test_au8_new_2D_empty(){
  au8* mat = au8_new_2D(2,3);
  TEST_ASSERT_EQUAL(6, mat->n);
  TEST_ASSERT_EQUAL(2, mat->dim);
  TEST_ASSERT_EQUAL(2, mat->shape[0]);
  TEST_ASSERT_EQUAL(3, mat->shape[1]);
  TEST_ASSERT_NOT_NULL(mat->d);
}

void
test_au8_new_2D_set() {
  au8* mat = au8_new_2D(2,3);
  uint8_t mat_d[] = {0,1,2,3,4,5};
  au8_set(mat, mat_d);
  TEST_ASSERT_EQUAL(6, mat->n);
  TEST_ASSERT_EQUAL(2, mat->dim);
  TEST_ASSERT_NOT_NULL(mat->shape);
  TEST_ASSERT_EQUAL(2, mat->shape[0]);
  TEST_ASSERT_EQUAL(3, mat->shape[1]);
  TEST_ASSERT_NOT_NULL(mat->d);
  TEST_ASSERT_EQUAL_MEMORY(mat_d, mat->d, sizeof(uint8_t) * 6);
}

int main() {
  UNITY_BEGIN();
  RUN_TEST(test_au8_new);
  RUN_TEST(test_au8_new_dim);
  RUN_TEST(test_au8_new_shape);
  RUN_TEST(test_au8_new_like);
  RUN_TEST(test_au8_zeros);
  RUN_TEST(test_au8_zeros_like);
  RUN_TEST(test_au8_ones);
  RUN_TEST(test_au8_ones_like);

  RUN_TEST(test_au8_new_1D_empty);
  RUN_TEST(test_au8_new_1D_set);
  RUN_TEST(test_au8_new_1D_d);
  RUN_TEST(test_au8_1D_dot);
  RUN_TEST(test_au8_new_2D_empty);
  RUN_TEST(test_au8_new_2D_set);
  return UNITY_END();
}
