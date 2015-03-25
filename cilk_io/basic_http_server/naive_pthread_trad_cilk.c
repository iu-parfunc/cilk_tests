#define PERTURB_VARIANT
#define PTHREAD_TRAD_CILK_VARIANT

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <cilk/cilk.h>
#include "common.h"

long fib_seq(int n) {
  if (n<2) return 1;
  return fib_seq(n-1) + fib_seq(n-2);
}

long fib_cilk_trad_perturbed(int n) {
  if (n<2) return 1;

  long x;
  long y;
  if (n == FIB_BOTTOM_OUT)
    return fib_seq(n);
  x = cilk_spawn fib_cilk_trad_perturbed(n-1);
  // We add a spawn here in order to match time_fib in qthreads
  y =  fib_cilk_trad_perturbed(n-2);

  cilk_sync;
  return x+y;
}

#include "naive_server_pthread.c"
