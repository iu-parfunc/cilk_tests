#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <cilk/cilk.h>
#include <cilk/concurrent_cilk.h>

#ifdef CILK_BLOCK
#define perturb(prob, n, length) { \
  if (prob && (n % prob == 0)) { \
    cilk_sleep(length); \
  } \
}
#else
#define perturb(prob, n, length) { \
  if (prob && (n % prob == 0)) { \
    usleep(length);\
  } \
}
#endif

/*
 *static inline void perturb(long prob, long n, long length) {
 *  if (prob && (n % prob == 0)) {
 *#ifdef CILK_BLOCK
 *    cilk_sleep(length);
 *#else
 *    usleep(length);
 *#endif
 *  }
 *}
 */
