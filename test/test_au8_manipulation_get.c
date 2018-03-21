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


#include <unity.h>
#include <numc.h>
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

int main() {
  UNITY_BEGIN();
  RUN_TEST(test_au8_get);
  RUN_TEST(test_au8_get_elem);
  return UNITY_END();
}
