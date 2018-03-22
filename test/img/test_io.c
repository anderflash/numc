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

#include <nc/img.h>
#include <unity.h>
static void
test_io_au16_read_pgm() {
  au16* a = au16_read_pgm("../rsc/pattern.pgm");
  TEST_ASSERT_EQUAL(480, a->h.shape[0]);
  TEST_ASSERT_EQUAL(640, a->h.shape[1]);
  TEST_ASSERT_EQUAL(156, a->d[0]);
  au16_destroy(a);
}
static void
test_io_au16_write_pgm() {
  au16* a = au16_read_pgm("../rsc/pattern.pgm"), *b;
  au16_write_pgm(a, "../rsc/pattern2.pgm");
  b = au16_read_pgm("../rsc/pattern2.pgm");
  TEST_ASSERT_EQUAL(480, b->h.shape[0]);
  TEST_ASSERT_EQUAL(640, b->h.shape[1]);
  TEST_ASSERT_EQUAL(156, b->d[0]);
  au16_destroy(a);
  au16_destroy(b);
}
int main() {
  UNITY_BEGIN();
  RUN_TEST(test_io_au16_read_pgm);
  RUN_TEST(test_io_au16_write_pgm);
  return UNITY_END();
}
