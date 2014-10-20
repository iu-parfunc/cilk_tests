#define PERTURB_VARIANT
#define CILK_CILK_VARIANT
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <cilk/cilk.h>
//#include <cilk/concurrent_cilk.h>

long fib_cilk_cilk_perturbed(int n) {
  if (n<2) return n;

  long x;
  long y;
  if (n == 3)
    usleep(5000);
  x = cilk_spawn fib_cilk_cilk_perturbed(n-1);
  // We add a spawn here in order to match time_fib in qthreads
  y =  fib_cilk_cilk_perturbed(n-2);
  cilk_sync;
  return x+y;
}

#include "naive_server_Ccilk.c"


