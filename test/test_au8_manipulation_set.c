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
test_au8_new_1D_set() {
  au8* a = au8_new_1d(5);
  uint8_t a_d[] = {0,1,2,3,4};
  au8_set(a, a_d);
  TEST_AU8_DIM_N(a, 1, 5);
  TEST_ASSERT_EQUAL(5, a->h.shape[0]);
  TEST_ASSERT_EQUAL(1, a->h.step[0]);
  TEST_ASSERT_EQUAL(1, a->h.ostep[0]);
  TEST_ASSERT_TRUE(a->h.owns);
  TEST_ASSERT_EQUAL_MEMORY(a_d, a->d, sizeof(uint8_t) * 5);
}

void
test_au8_new_2D_set() {
  au8* a = au8_new_2d(2,3);
  uint8_t mat_d[] = {0,1,2,3,4,5};
  au8_set(a, mat_d);
  TEST_AU8_DIM_N(a, 2, 6);
  TEST_ASSERT_EQUAL(2, a->h.shape[0]);
  TEST_ASSERT_EQUAL(3, a->h.shape[1]);
  TEST_ASSERT_EQUAL(3, a->h.step[0]);
  TEST_ASSERT_EQUAL(1, a->h.step[1]);
  TEST_ASSERT_EQUAL(3, a->h.ostep[0]);
  TEST_ASSERT_EQUAL(1, a->h.ostep[1]);
  TEST_ASSERT_TRUE(a->h.owns);
  TEST_ASSERT_EQUAL_MEMORY(mat_d, a->d, sizeof(uint8_t) * 6);
}

void
test_au8_new_3D_set() {
  au8* a = au8_new_3d(1,2,3);
  uint8_t a_d[] = {0,1,2,3,4,5};
  au8_set(a, a_d);
  TEST_AU8_DIM_N(a, 3, 6);
  TEST_ASSERT_EQUAL(1, a->h.shape[0]);
  TEST_ASSERT_EQUAL(2, a->h.shape[1]);
  TEST_ASSERT_EQUAL(3, a->h.shape[2]);
  TEST_ASSERT_EQUAL(6, a->h.step[0]);
  TEST_ASSERT_EQUAL(3, a->h.step[1]);
  TEST_ASSERT_EQUAL(1, a->h.step[2]);
  TEST_ASSERT_EQUAL(6, a->h.ostep[0]);
  TEST_ASSERT_EQUAL(3, a->h.ostep[1]);
  TEST_ASSERT_EQUAL(1, a->h.ostep[2]);
  TEST_ASSERT_TRUE(a->h.owns);
  TEST_ASSERT_EQUAL_MEMORY(a_d, a->d, sizeof(uint8_t) * 6);
}

void
test_au8_new_4D_set() {
  au8* a = au8_new_4d(1,2,3,2);
  uint8_t a_d[] = {0,1,2,3,4,5,6,7,8,9,10,11};
  au8_set(a, a_d);
  TEST_AU8_DIM_N(a, 4, 12);
  TEST_ASSERT_EQUAL(1, a->h.shape[0]);
  TEST_ASSERT_EQUAL(2, a->h.shape[1]);
  TEST_ASSERT_EQUAL(3, a->h.shape[2]);
  TEST_ASSERT_EQUAL(2, a->h.shape[3]);
  TEST_ASSERT_EQUAL(12, a->h.step[0]);
  TEST_ASSERT_EQUAL( 6, a->h.step[1]);
  TEST_ASSERT_EQUAL( 2, a->h.step[2]);
  TEST_ASSERT_EQUAL( 1, a->h.step[3]);
  TEST_ASSERT_EQUAL(12, a->h.ostep[0]);
  TEST_ASSERT_EQUAL( 6, a->h.ostep[1]);
  TEST_ASSERT_EQUAL( 2, a->h.ostep[2]);
  TEST_ASSERT_EQUAL( 1, a->h.ostep[3]);
  TEST_ASSERT_TRUE(a->h.owns);
  TEST_ASSERT_EQUAL_MEMORY(a_d, a->d, sizeof(uint8_t) * 12);
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

int main() {
  UNITY_BEGIN();
  RUN_TEST(test_au8_new_1D_set);
  RUN_TEST(test_au8_new_2D_set);
  RUN_TEST(test_au8_new_3D_set);
  RUN_TEST(test_au8_new_4D_set);
  RUN_TEST(test_au8_set);
  RUN_TEST(test_au8_set_elem);
  return UNITY_END();
}
