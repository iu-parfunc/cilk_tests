#define PERTURB_VARIANT
#define PTHREAD_SEQ_VARIANT

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

long fib_sequential_perturbed(int n) {
  if (n<2) return 1;

  long x;
  long y;
  x = fib_sequential_perturbed(n-1);
  // We add a spawn here in order to match time_fib in qthreads
  y =  fib_sequential_perturbed(n-2);
  return x+y;
}

#include "naive_server_pthread.c"
