#include <stdio.h>
#include <stdlib.h>

#include <cilk/cilk.h>
#include <pthread.h>
// #include <cilk/concurrent_cilk.h>
#include "../../../common/timer.h"

long iterations = 10000;
long num_fibers = 2;
pthread_t* threads;
pthread_mutex_t* locks; 
pthread_cond_t* condc;
pthread_cond_t* condp;
long* ids;
long* shared;
long* progress;

// This tests idling by having a long-non-parallel region:
void foo() {
  for(long i=0; i< 100 * 1000 * 1000; i++)
    rand();
}

int main(int argc, char **argv) {
  my_timer_t t;
  TIMER_RESET(t);
  TIMER_START(t);
  cilk_spawn foo();
  cilk_sync;
  TIMER_STOP(t);

  printf("SELFTIMED: %f\n", TIMER_EVAL(t));
}
