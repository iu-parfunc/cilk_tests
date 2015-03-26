#define PERTURB_VARIANT
#define CILK_CCILK_VARIANT
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <cilk/cilk.h>
#include <cilk/concurrent_cilk.h>
#include "common.h"

long fib_seq(int n) {
  if (n<2) return 1;
  return fib_seq(n-1) + fib_seq(n-2);
}

long fib_cilk_ccilk_perturbed(int n) {
  if (n<2) return n;

  long x;
  long y;
  if (n <= FIB_BOTTOM_OUT)
    return fib_seq(n);
  x = cilk_spawn fib_cilk_ccilk_perturbed(n-1);
  // We add a spawn here in order to match time_fib in qthreads
  y =  fib_cilk_ccilk_perturbed(n-2);

  cilk_sync;
  return x+y;
}

#include "naive_server_Ccilk.c"


