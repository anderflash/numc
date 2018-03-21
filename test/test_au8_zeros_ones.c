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

#include <numc.h>
#include <unity.h>
#include "test.h"

void
test_au8_zeros() {
  uint8_t i;
  nelem_t a_shape[] = {2, 3};
  au8 *a = au8_zeros(2, a_shape);
  TEST_AU8_DIM_N(a, 2, 6);
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
  au8 *a = au8_new_1d(2), *b;
  uint8_t a_d[] = {1,2};
  au8_set(a, a_d);
  b = au8_zeros_like(a);
  TEST_AU8_DIM_N(b, 1, 2);
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
  TEST_AU8_DIM_N(a, 2, 6);
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
  au8 *a = au8_new_1d(2), *b;
  uint8_t a_d[] = {1,2};
  au8_set(a, a_d);
  b = au8_ones_like(a);
  TEST_AU8_DIM_N(b, 1, 2);
  TEST_ASSERT_EQUAL(2,b->shape[0]);
  for(i = 0; i < 2; i++) {
    TEST_ASSERT_EQUAL(1, b->d[i]);
  }
  au8_destroy(a);
  au8_destroy(b);
}

void
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

int main() {
  UNITY_BEGIN();
  RUN_TEST(test_au8_zeros);
  RUN_TEST(test_au8_zeros_like);
  RUN_TEST(test_au8_ones);
  RUN_TEST(test_au8_ones_like);
  RUN_TEST(test_au8_eye);
  return UNITY_END();
}
