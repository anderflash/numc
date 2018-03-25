#include <nc/chart.h>
#include <stdint.h>

#define UNUSED __attribute__((unused))

int main() {
  uint8_t data[] = {3,6,1,2,8};
  au8* a = au8_new_1d_data(5, data);
  chart* c = chart_new();
  chart_line_au8(c, a);
  chart_show("", c);
  return 0;
}
