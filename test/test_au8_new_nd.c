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
test_au8_new_1D(){
  au8* a = au8_new_1d(5);
  TEST_AU8_DIM_N(a, 1, 5);
  TEST_ASSERT_EQUAL(5, a->shape[0]);
  TEST_ASSERT_TRUE(a->owns);
}

void
test_au8_new_1D_set() {
  au8* a = au8_new_1d(5);
  uint8_t a_d[] = {0,1,2,3,4};
  au8_set(a, a_d);
  TEST_AU8_DIM_N(a, 1, 5);
  TEST_ASSERT_EQUAL(5, a->shape[0]);
  TEST_ASSERT_TRUE(a->owns);
  TEST_ASSERT_EQUAL_MEMORY(a_d, a->d, sizeof(uint8_t) * 5);
}

void
test_au8_new_1D_data() {
  au8* a;
  uint8_t a_d[] = {0,1,2,3,4};
  a = au8_new_1d_data(5, a_d);
  TEST_AU8_DIM_N(a, 1, 5);
  TEST_ASSERT_EQUAL(5, a->shape[0]);
  TEST_ASSERT_FALSE(a->owns);
  TEST_ASSERT_EQUAL_MEMORY(a_d, a->d, sizeof(uint8_t) * 5);
}

void
test_au8_new_2D(){
  au8* a = au8_new_2d(2,3);
  TEST_AU8_DIM_N(a, 2, 6);
  TEST_ASSERT_EQUAL(2, a->shape[0]);
  TEST_ASSERT_EQUAL(3, a->shape[1]);
  TEST_ASSERT_TRUE(a->owns);
}

void
test_au8_new_2D_set() {
  au8* a = au8_new_2d(2,3);
  uint8_t mat_d[] = {0,1,2,3,4,5};
  au8_set(a, mat_d);
  TEST_AU8_DIM_N(a, 2, 6);
  TEST_ASSERT_EQUAL(2, a->shape[0]);
  TEST_ASSERT_EQUAL(3, a->shape[1]);
  TEST_ASSERT_TRUE(a->owns);
  TEST_ASSERT_EQUAL_MEMORY(mat_d, a->d, sizeof(uint8_t) * 6);
}

void
test_au8_new_2D_data() {
  au8* a;
  uint8_t a_d[] = {0,1,2,3,4,5};
  a = au8_new_2d_data(2, 3, a_d);
  TEST_AU8_DIM_N(a, 2, 6);
  TEST_ASSERT_EQUAL(2, a->shape[0]);
  TEST_ASSERT_EQUAL(3, a->shape[1]);
  TEST_ASSERT_FALSE(a->owns);
  TEST_ASSERT_EQUAL_MEMORY(a_d, a->d, sizeof(uint8_t) * 6);
}

void
test_au8_new_3D() {
  au8* a = au8_new_3d(1,2,3);
  TEST_AU8_DIM_N(a, 3, 6);
  TEST_ASSERT_EQUAL(1, a->shape[0]);
  TEST_ASSERT_EQUAL(2, a->shape[1]);
  TEST_ASSERT_EQUAL(3, a->shape[2]);
  TEST_ASSERT_TRUE(a->owns);
}

void
test_au8_new_3D_set() {
  au8* a = au8_new_3d(1,2,3);
  uint8_t a_d[] = {0,1,2,3,4,5};
  au8_set(a, a_d);
  TEST_AU8_DIM_N(a, 3, 6);
  TEST_ASSERT_EQUAL(1, a->shape[0]);
  TEST_ASSERT_EQUAL(2, a->shape[1]);
  TEST_ASSERT_EQUAL(3, a->shape[2]);
  TEST_ASSERT_TRUE(a->owns);
  TEST_ASSERT_EQUAL_MEMORY(a_d, a->d, sizeof(uint8_t) * 6);
}

void
test_au8_new_3D_data() {
  au8* a;
  uint8_t a_d[] = {0,1,2,3,4,5};
  a = au8_new_3d_data(1, 2, 3, a_d);
  TEST_AU8_DIM_N(a, 3, 6);
  TEST_ASSERT_EQUAL(1, a->shape[0]);
  TEST_ASSERT_EQUAL(2, a->shape[1]);
  TEST_ASSERT_EQUAL(3, a->shape[2]);
  TEST_ASSERT_FALSE(a->owns);
  TEST_ASSERT_EQUAL_MEMORY(a_d, a->d, sizeof(uint8_t) * 6);
}

void
test_au8_new_4D() {
  au8* a = au8_new_4d(1,2,3,2);
  TEST_AU8_DIM_N(a, 4, 12);
  TEST_ASSERT_EQUAL(1, a->shape[0]);
  TEST_ASSERT_EQUAL(2, a->shape[1]);
  TEST_ASSERT_EQUAL(3, a->shape[2]);
  TEST_ASSERT_EQUAL(2, a->shape[3]);
  TEST_ASSERT_TRUE(a->owns);
}

void
test_au8_new_4D_set() {
  au8* a = au8_new_4d(1,2,3,2);
  uint8_t a_d[] = {0,1,2,3,4,5,6,7,8,9,10,11};
  au8_set(a, a_d);
  TEST_AU8_DIM_N(a, 4, 12);
  TEST_ASSERT_EQUAL(1, a->shape[0]);
  TEST_ASSERT_EQUAL(2, a->shape[1]);
  TEST_ASSERT_EQUAL(3, a->shape[2]);
  TEST_ASSERT_EQUAL(2, a->shape[3]);
  TEST_ASSERT_TRUE(a->owns);
  TEST_ASSERT_EQUAL_MEMORY(a_d, a->d, sizeof(uint8_t) * 12);
}

void
test_au8_new_4D_data() {
  au8* a;
  uint8_t a_d[] = {0,1,2,3,4,5,6,7,8,9,10,11};
  a = au8_new_4d_data(1, 2, 3, 2, a_d);
  TEST_AU8_DIM_N(a, 4, 12);
  TEST_ASSERT_EQUAL(1, a->shape[0]);
  TEST_ASSERT_EQUAL(2, a->shape[1]);
  TEST_ASSERT_EQUAL(3, a->shape[2]);
  TEST_ASSERT_EQUAL(2, a->shape[3]);
  TEST_ASSERT_FALSE(a->owns);
  TEST_ASSERT_EQUAL_MEMORY(a_d, a->d, sizeof(uint8_t) * 12);
}

int main() {
  UNITY_BEGIN();
  RUN_TEST(test_au8_new_1D);
  RUN_TEST(test_au8_new_1D_set);
  RUN_TEST(test_au8_new_1D_data);
  RUN_TEST(test_au8_new_2D);
  RUN_TEST(test_au8_new_2D_set);
  RUN_TEST(test_au8_new_2D_data);
  RUN_TEST(test_au8_new_3D);
  RUN_TEST(test_au8_new_3D_set);
  RUN_TEST(test_au8_new_3D_data);
  RUN_TEST(test_au8_new_4D);
  RUN_TEST(test_au8_new_4D_set);
  RUN_TEST(test_au8_new_4D_data);
  return UNITY_END();
}
