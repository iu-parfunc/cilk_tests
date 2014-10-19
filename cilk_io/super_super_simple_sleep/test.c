#include <stdio.h>
#include <stdlib.h>
#include <cilk/cilk.h>
#include <cilk/concurrent_cilk.h>
#include <timer.h>
#include <cycle.h>

/*
 *#define CILK_BLOCK
 *
 *#ifdef CILK_BLOCK
 *#define perturb(prob, n, length) { \
 *  if (prob && (n % prob == 0)) { \
 *    cilk_sleep(length); \
 *  } \
 *}
 *#else
 *#define perturb(prob, n, length) { \
 *  if (prob && (n % prob == 0)) { \
 *    usleep(length);\
 *  } \
 *}
 *#endif
 */

void foo() {
  printf("-------- before ---------\n");
  /*cilk_sleep(500000);*/
  perturb(1, 1, 500000);
  printf("-------- after ---------\n");
}

int main(int argc, const char *argv[])
{
  cilk_io_init();
  printf("BEFORE\n");
  int i = 0;
  for (i = 0; i < 20; i++) {
    cilk_spawn foo();
    /*foo();*/
  }
  /*sleep(2);*/
  /*cilk_spawn foo();*/
  cilk_sync;
  printf("AFTER\n");
  cilk_io_teardown();
  return 0;
}
