#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <timer.h>
#include <cycle.h>

int perturbation_point;

long fib (n) {

#ifdef PERTURB_PTHREAD_SLEEP
  if (n == perturbation_point) {
    usleep(5000);
  }
#endif

  if (n == 0) {
    return 0;
  } else if (n == 1) {
    return 1;
  } else {
    return fib(n-1) + fib(n-2);
  }
}

int main(int argc, char** argv) {
  int n;
  long j = 0;
  my_timer_t t;

  if (argc > 1) {
    printf("argv[1]:%s\n", argv[1]);
    n = atoi(argv[1]);
   } else {
    n = 42;
   }

  if (argc>=2) {
    perturbation_point = atoi(argv[2]);
  } else {
    perturbation_point = n/2;
  }

  TIMER_RESET(t);
  TIMER_START(t);
  ticks t1 = getticks();
  long res = fib(n);
  ticks t2 = getticks();
  TIMER_STOP(t);

  printf("result: %ld\t", res);
  printf("SELFTIMED: %lf\n", TIMER_EVAL(t));
  printf("%d\t%f\t%lf\n", n, TIMER_EVAL(t), elapsed(t2,t1));

}

