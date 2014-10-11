#include <stdio.h>
#include <stdlib.h>
#include <cilk/cilk_api.h>
#include <cilk/cilk.h>
#include <cilk/cilk_undocumented.h>
#include <timer.h>
#include <cycle.h>

#include <time.h>

long pfib(int n) {
  if (n<2) return 1;

  long x;
  long y;
  x = cilk_spawn pfib(n-1);
  // We add a spawn here in order to match time_fib in qthreads
  y =  pfib(n-2);

  cilk_sync;
  return x+y;
}

int main(int argc, char** argv) {
  int n;
  long j;
  my_timer_t t;


  if (argc>1)
    n = atoi(argv[1]);
  else
    n = 42;

// passing a dummy argument through in order to warm things up (and keep them warm...)
  //long ret;
  //ret = pfib(n);

  TIMER_START(t);
  clock_t c1 = clock();
  struct timeval r0,r1;
  gettimeofday(&r0, 0);
  ticks t1 = getticks();
  j=pfib(n);
  ticks t2 = getticks();
  gettimeofday(&r1, 0);
  clock_t c2 = clock();
  clock_t c_elapsed = c2 - c1;
  double real = (r1.tv_sec - r0.tv_sec) + ((double)(r1.tv_usec - r0.tv_usec))/1000000;
  TIMER_STOP(t);

  printf("%ld\t", j);
  printf("%d\t%f\t%lf\t%d\n", n, TIMER_EVAL(t), elapsed(t2,t1), __cilkrts_get_total_workers());

  printf("PARFIB_INPUT: %d\n", n);
  printf("CPUTIME: %lf\n", ((double)c_elapsed)/CLOCKS_PER_SEC);
  printf("SELFTIMED: %lf\n", real);

  // TIMER_EVAL(t), elapsed(t2,t1), __cilkrts_get_total_workers());

  __cilkrts_dump_stats();
  //printf("%d\t%f\n", n, TIMER_EVAL(t));
  return 0;
}

