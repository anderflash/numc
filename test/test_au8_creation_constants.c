/*
 MIT License

 Copyright (c) 2018 Anderson Tavares <acmt at outlook.com>

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
*/

#include <nc/core.h>
#include <unity.h>
#include "test.h"

static void
test_au8_zeros() {
  uint8_t i;
  nelem_t a_shape[] = {2, 3};
  au8 *a = au8_zeros(2, a_shape);
  TEST_AU8_DIM_N(a, 2, 6);
  TEST_ASSERT_EQUAL(2, a->h.shape[0]);
  TEST_ASSERT_EQUAL(3, a->h.shape[1]);
  for(i = 0; i < 6; i++) {
    TEST_ASSERT_EQUAL(0, a->d[i]);
  }
  au8_destroy(a);
}

static void
test_au8_zeros_like() {
  uint64_t i;
  au8 *a = au8_new_1d(2), *b;
  uint8_t a_d[] = {1,2};
  au8_set(a, a_d);
  b = au8_zeros_like(a);
  TEST_AU8_DIM_N(b, 1, 2);
  TEST_ASSERT_EQUAL(2,b->h.shape[0]);
  for(i = 0; i < 2; i++) {
    TEST_ASSERT_EQUAL(0, b->d[i]);
  }
  au8_destroy(a);
  au8_destroy(b);
}

static void
test_au8_ones() {
  uint8_t i;
  nelem_t a_shape[] = {2, 3};
  au8 *a = au8_ones(2, a_shape);
  TEST_AU8_DIM_N(a, 2, 6);
  TEST_ASSERT_EQUAL(2, a->h.shape[0]);
  TEST_ASSERT_EQUAL(3, a->h.shape[1]);
  for(i = 0; i < 6; i++) {
    TEST_ASSERT_EQUAL(1, a->d[i]);
  }
  au8_destroy(a);
}

static void
test_au8_ones_like() {
  uint64_t i;
  au8 *a = au8_new_1d(2), *b;
  uint8_t a_d[] = {1,2};
  au8_set(a, a_d);
  b = au8_ones_like(a);
  TEST_AU8_DIM_N(b, 1, 2);
  TEST_ASSERT_EQUAL(2,b->h.shape[0]);
  for(i = 0; i < 2; i++) {
    TEST_ASSERT_EQUAL(1, b->d[i]);
  }
  au8_destroy(a);
  au8_destroy(b);
}

static void
test_au8_eye() {
  au8* a = au8_eye(2);
  TEST_ASSERT_EQUAL(a->d[0], 1);
  TEST_ASSERT_EQUAL(a->d[1], 0);
  TEST_ASSERT_EQUAL(a->d[2], 0);
  TEST_ASSERT_EQUAL(a->d[3], 1);

  au8* b = au8_eye_cols(2, 3);
  TEST_ASSERT_EQUAL(b->d[0], 1);
  TEST_ASSERT_EQUAL(b->d[1], 0);
  TEST_ASSERT_EQUAL(b->d[2], 0);
  TEST_ASSERT_EQUAL(b->d[3], 0);
  TEST_ASSERT_EQUAL(b->d[4], 1);
  TEST_ASSERT_EQUAL(b->d[5], 0);

  au8_destroy(a);
  au8_destroy(b);
}

static void
test_au8_filled() {
  nelem_t shape[] = {2, 2};
  au8* a = au8_filled(2, shape, 5);
  TEST_AU8_DIM_N(a, 2, 4);
  TEST_ASSERT_EQUAL(a->d[0], 5);
  TEST_ASSERT_EQUAL(a->d[1], 5);
  TEST_ASSERT_EQUAL(a->d[2], 5);
  TEST_ASSERT_EQUAL(a->d[3], 5);

  au8* b = au8_filled_like(a, 6);
  TEST_AU8_DIM_N(b, 2, 4);
  TEST_ASSERT_EQUAL(b->d[0], 6);
  TEST_ASSERT_EQUAL(b->d[1], 6);
  TEST_ASSERT_EQUAL(b->d[2], 6);
  TEST_ASSERT_EQUAL(b->d[3], 6);

  au8_destroy(a);
  au8_destroy(b);
}

static void
test_au8_copy() {
  nelem_t shape[] = {2, 2};
  au8* a = au8_filled(2, shape, 5);
  au8* b = au8_copy(a);
  TEST_AU8_DIM_N(b, 2, 4);
  TEST_ASSERT_EQUAL(b->d[0], 5);
  TEST_ASSERT_EQUAL(b->d[1], 5);
  TEST_ASSERT_EQUAL(b->d[2], 5);
  TEST_ASSERT_EQUAL(b->d[3], 5);

  b->d[0] = 3;
  TEST_ASSERT_EQUAL(a->d[0], 5);
}

static void
test_au8_save_load() {
  nelem_t shape[] = {2, 2};
  au8* a = au8_filled(2, shape, 5);
  au8* b = au8_filled(2, shape, 4);
  au8* c_save[] = {a,b};
  char* names_save[] = {"a", "b"};
  char** names_load = NULL;
  uint8_t n_load;
  au8_save_gzip("shape.ncz", 2, names_save, c_save);
  au8* c_load = au8_load_gzip("shape.ncz", &n_load, &names_load);
  TEST_ASSERT_NOT_NULL(c_load);
  TEST_ASSERT_EQUAL(2, n_load);
  TEST_ASSERT_NOT_NULL(names_load);
  TEST_ASSERT_EQUAL_STRING("a", names_load[0]);
  TEST_ASSERT_EQUAL_STRING("b", names_load[1]);
  TEST_ASSERT_EQUAL(5, c_load[0].d[0]);
  TEST_ASSERT_EQUAL(4, c_load[1].d[0]);
}

int main() {
  UNITY_BEGIN();
  RUN_TEST(test_au8_zeros);
  RUN_TEST(test_au8_zeros_like);
  RUN_TEST(test_au8_ones);
  RUN_TEST(test_au8_ones_like);
  RUN_TEST(test_au8_eye);
  RUN_TEST(test_au8_filled);
  RUN_TEST(test_au8_copy);
  RUN_TEST(test_au8_save_load);
  return UNITY_END();
}
