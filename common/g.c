#include <timer.h>
#include <stdio.h>


int main() {
  my_timer_t t;
  TIMER_START(t);
  int i,j;
  for (i = 0; i < 100000000; i++) 
    while (j++ < 100000000);
  TIMER_STOP(t);

  printf("%f\n", TIMER_EVAL(t));
  return 0;
}
