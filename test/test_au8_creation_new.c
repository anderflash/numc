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
#include <stdlib.h>
#include <unity.h>
#include <string.h>
#include "test.h"

void
test_au8_new() {
  au8* a = au8_new();
  TEST_ASSERT_NOT_NULL(a);
  TEST_ASSERT_NULL(a->h.shape);
  TEST_ASSERT_NULL(a->h.step);
  TEST_ASSERT_NULL(a->h.ostep);
  TEST_ASSERT_NULL(a->d);
  TEST_ASSERT_EQUAL(0, a->h.dim);
  TEST_ASSERT_EQUAL(0, a->h.n);
  TEST_ASSERT_FALSE(a->h.owns);
  TEST_ASSERT_EQUAL(0, a->h.start);
  TEST_ASSERT_EQUAL(1, a->h.bitsize);
  free(a);
}

void
test_au8_new_dim() {
  au8* a = au8_new_dim(4);
  TEST_ASSERT_NOT_NULL(a);
  TEST_ASSERT_NOT_NULL(a->h.shape);
  TEST_ASSERT_NOT_NULL(a->h.step);
  TEST_ASSERT_NOT_NULL(a->h.ostep);
  TEST_ASSERT_NULL(a->d);
  TEST_ASSERT_EQUAL(4, a->h.dim);
  TEST_ASSERT_EQUAL(0, a->h.n);
  TEST_ASSERT_FALSE(   a->h.owns);
  TEST_ASSERT_EQUAL(0, a->h.start);
  au8_destroy(a);
  a = NULL;
}

void
test_au8_new_shape() {
  nelem_t shape[] = {3,5,1,2};
  au8* a = au8_new_shape(4, shape);
  TEST_AU8_DIM_N(a, 4, 30);
  TEST_ASSERT_EQUAL(3,  a->h.shape[0]);
  TEST_ASSERT_EQUAL(5,  a->h.shape[1]);
  TEST_ASSERT_EQUAL(1,  a->h.shape[2]);
  TEST_ASSERT_EQUAL(2,  a->h.shape[3]);
  TEST_ASSERT_EQUAL(10, a->h.step[0]);
  TEST_ASSERT_EQUAL(2,  a->h.step[1]);
  TEST_ASSERT_EQUAL(2,  a->h.step[2]);
  TEST_ASSERT_EQUAL(1,  a->h.step[3]);
  TEST_ASSERT_EQUAL(10, a->h.ostep[0]);
  TEST_ASSERT_EQUAL(2,  a->h.ostep[1]);
  TEST_ASSERT_EQUAL(2,  a->h.ostep[2]);
  TEST_ASSERT_EQUAL(1,  a->h.ostep[3]);
  TEST_ASSERT_TRUE(     a->h.owns);
  au8_destroy(a);
}

void
test_au8_new_like() {
  au8 *a = au8_new_1d(2), *b;
  uint8_t a_d[] = {1,2};
  au8_set(a, a_d);
  b = au8_new_like(a);
  TEST_AU8_DIM_N(b, a->h.dim, a->h.n);
  TEST_ASSERT_EQUAL(2,b->h.shape[0]);
  TEST_ASSERT_EQUAL(1, a->h.step[0]);
  TEST_ASSERT_TRUE(b->h.owns);
  au8_destroy(a);
  au8_destroy(b);
}


void
test_au8_new_data() {
  uint8_t a_d[] = {1,2};
  nelem_t shape = 2;
  au8* a = au8_new_data(1,&shape,a_d);
  TEST_AU8_DIM_N(a, 1, 2);
  TEST_ASSERT_EQUAL(1, a->d[0]);
  TEST_ASSERT_EQUAL(2, a->d[1]);
  a_d[1] = 3;
  TEST_ASSERT_EQUAL(3, a->d[1]);
  au8_destroy(a);
}

void
test_au8_new_1D(){
  au8* a = au8_new_1d(5);
  TEST_AU8_DIM_N(a, 1, 5);
  TEST_ASSERT_EQUAL(5, a->h.shape[0]);
  TEST_ASSERT_EQUAL(1, a->h.step[0]);
  TEST_ASSERT_EQUAL(1, a->h.ostep[0]);
  TEST_ASSERT_TRUE(a->h.owns);
}

void
test_au8_new_2D(){
  au8* a = au8_new_2d(2,3);
  TEST_AU8_DIM_N(a, 2, 6);
  TEST_ASSERT_EQUAL(2, a->h.shape[0]);
  TEST_ASSERT_EQUAL(3, a->h.shape[1]);
  TEST_ASSERT_EQUAL(3, a->h.step[0]);
  TEST_ASSERT_EQUAL(1, a->h.step[1]);
  TEST_ASSERT_EQUAL(3, a->h.ostep[0]);
  TEST_ASSERT_EQUAL(1, a->h.ostep[1]);
  TEST_ASSERT_TRUE(a->h.owns);
}

void
test_au8_new_3D() {
  au8* a = au8_new_3d(1,2,3);
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
}

void
test_au8_new_4D() {
  au8* a = au8_new_4d(1,2,3,2);
  TEST_AU8_DIM_N(a, 4, 12);
  TEST_ASSERT_EQUAL(1, a->h.shape[0]);
  TEST_ASSERT_EQUAL(2, a->h.shape[1]);
  TEST_ASSERT_EQUAL(3, a->h.shape[2]);
  TEST_ASSERT_EQUAL(2, a->h.shape[3]);
  TEST_ASSERT_EQUAL(12, a->h.step[0]);
  TEST_ASSERT_EQUAL(6,  a->h.step[1]);
  TEST_ASSERT_EQUAL(2,  a->h.step[2]);
  TEST_ASSERT_EQUAL(1,  a->h.step[3]);
  TEST_ASSERT_EQUAL(12, a->h.ostep[0]);
  TEST_ASSERT_EQUAL( 6, a->h.ostep[1]);
  TEST_ASSERT_EQUAL( 2, a->h.ostep[2]);
  TEST_ASSERT_EQUAL( 1, a->h.ostep[3]);
  TEST_ASSERT_TRUE(a->h.owns);
}


int main() {
  UNITY_BEGIN();
  RUN_TEST(test_au8_new);
  RUN_TEST(test_au8_new_dim);
  RUN_TEST(test_au8_new_shape);
  RUN_TEST(test_au8_new_like);
  RUN_TEST(test_au8_new_data);
  RUN_TEST(test_au8_new_1D);
  RUN_TEST(test_au8_new_2D);
  RUN_TEST(test_au8_new_3D);
  RUN_TEST(test_au8_new_4D);
  return UNITY_END();
}
