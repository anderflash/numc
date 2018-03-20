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
test_au8_get() {
  au8 *a, *b;
  nelem_t ranges[] = {1, REND, 1, REND};
  uint8_t a_d[] = {0,1,2,3,4,5,6,7,8};
  a = au8_new_2d_data(3,3,a_d);
  b = au8_get(a, 2, ranges);
  TEST_AU8_DIM_N_START(b, 2, 4, 4);
  TEST_ASSERT_EQUAL(2, b->shape[0]);
  TEST_ASSERT_EQUAL(2, b->shape[1]);
  TEST_ASSERT_EQUAL(2, b->step[0]);
  TEST_ASSERT_EQUAL(1, b->step[1]);
  TEST_ASSERT_EQUAL(3, b->ostep[0]);
  TEST_ASSERT_EQUAL(1, b->ostep[1]);
  uint8_t b_d[] = {4,5,7,8};
  uint8_t i;
  for(i = 0; i < 4; i++) {
    TEST_ASSERT_EQUAL(b_d[i], au8_get_elem_offset(b, i));
  }
  au8_destroy(b);
  au8_destroy(a);
}

void
test_au8_get_elem() {
  uint8_t a_d[] = {0,1,2,3};
  au8* a = au8_new_2d_data(2,2,a_d);
  nelem_t pos[] = {1,1};
  uint8_t b = au8_get_elem(a, pos);
  TEST_ASSERT_EQUAL(b, 3);
  au8_destroy(a);
}

void
test_au8_set() {
  au8* a = au8_new_2d(2,2);
  uint8_t i;
  uint8_t a_d[] = {0,1,2,3};
  au8_set(a,a_d);
  for(i = 0; i < 4; i++) {
    TEST_ASSERT_EQUAL(a_d[i], a->d[i]);
  }
  a_d[2] = 6;
  TEST_ASSERT_EQUAL(2, a->d[2]);
  au8_destroy(a);
}

void
test_au8_set_elem() {
  au8* a = au8_new_2d(2,2);
  nelem_t pos[] = {1,1};
  au8_set_elem(a, pos, 5);
  uint8_t i;
  uint8_t a_d[] = {0,0,0,5};
  for(i = 0; i < 4; i++) {
    TEST_ASSERT_EQUAL(a_d[i], a->d[i]);
  }
}

void
test_au8_1D_dot() {
  au8 *a, *b;
  uint8_t a_d[] = {0,1,2,3,4};
  uint8_t b_d[] = {5,6,7,8,9};
  uint32_t c;
  a = au8_new_1d_data(5,a_d);
  b = au8_new_1d_data(5,b_d);
  c = au8_dot(a,b);
  TEST_ASSERT_EQUAL(80, c);
}

void
test_au8_1D_1D_add() {
  uint8_t a_d[] = {0,1,2,3};
  uint8_t b_d[] = {4,5,6,7};
  au8* a = au8_new_1d_data(4, a_d);
  au8* b = au8_new_1d_data(4, b_d);
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
  RUN_TEST(test_au8_get);
  RUN_TEST(test_au8_get_elem);
  RUN_TEST(test_au8_set);
  RUN_TEST(test_au8_set_elem);
//  RUN_TEST(test_au8_1D_1D_add);
  return UNITY_END();
}
