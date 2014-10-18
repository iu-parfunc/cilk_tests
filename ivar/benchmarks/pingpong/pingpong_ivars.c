
#include <stdio.h>
#include <stdlib.h>

#include <cilk/cilk.h>
#include <cilk/concurrent_cilk.h>
// For dump_stats:
#include <cilk/cilk_undocumented.h>
#include "../../../common/timer.h"

#ifdef CCILK_PROFILE
#include <google/profiler.h>
#endif

void ping(long id);
void pong(long id);

long iterations = 10000;
long num_fibers = 2;

__cilkrts_ivar*  r_ivars;
__cilkrts_ivar*  w_ivars;

long* progress;

volatile int all_done = 0;

void ping(long id) {

  while (1) {

    // // printf(" [ping] w_ivar[%ld] address : %p\n", id, &w_ivars[id]);
    // // printf(" [ping] r_ivar[%ld] address : %p\n", id, &r_ivars[id]);

    // printf(" [ping] writing to ivar %p\n", &w_ivars[id]);

    cilk_spawn __cilkrts_ivar_write(&w_ivars[id], 1);

    __cilkrts_ivar_read(&r_ivars[id]);
    __cilkrts_ivar_clear(&r_ivars[id]);

    __sync_fetch_and_add(&progress[id], 1);
    if (progress[id] >= iterations) {
      __cilkrts_ivar_write(&w_ivars[id], 1); // Unblocks the consumer so it can finish
      return;
    }
  }
}

void pong(long id) {

  while (1) {

    __cilkrts_ivar_read(&w_ivars[id]);
    __cilkrts_ivar_clear(&w_ivars[id]);

    // __sync_synchronize();
    
    // // printf(" [pong] writing to ivar %p\n", &r_ivars[id]);
    // printf(" [pong] progress[%ld] : %ld\n", id, progress[id]);
    __cilkrts_ivar_write(&r_ivars[id], 1);


    if (progress[id] >= iterations) {
      return;
    }

  }

}

/** 
 * Usage ./pingpong_ivar.exe <num-of-fiber-pairs> <num-of-iterations>
 *
 * */

void waste_one_core() {
  printf(" CORE WASTER: put this core in a busywait until we're signaled...\n");
  while(!all_done) { }
  printf(" CORE WASTER: all done spinning, returning now.\n");
}

void run_benchmark() {
  my_timer_t t;

  int i;
  for (i = 0; i < num_fibers; i++) {
    progress[i] = 0;
    // printf(" [pingpong] w_ivars[%d] address : %p\n", i, &w_ivars[i]); 
    // printf(" [pingpong] r_ivars[%d] address : %p\n", i, &r_ivars[i]); 
    __cilkrts_ivar_clear(&w_ivars[i]);
    __cilkrts_ivar_clear(&r_ivars[i]);
  }

  // printf(" [pingpong] w_ivars[%d] address : %p\n", 0, &w_ivars[0]); 
  // printf(" [pingpong] r_ivars[%d] address : %p\n", 0, &r_ivars[0]); 

  TIMER_RESET(t);
  TIMER_START(t);

#ifdef CCILK_PROFILE
  ProfilerStart("./pingpong_ivars.prof");
#endif
  for (i = 0; i < num_fibers; i++) {
    cilk_spawn ping(i);
    cilk_spawn pong(i);
  }

  // printf(" [pingpong] Before cilk_sync\n");

  cilk_sync;
  // printf(" [pingpong] After cilk_sync\n");

#ifdef CCILK_PROFILE
  ProfilerStop();
#endif
  TIMER_STOP(t);
  printf("SELFTIMED: %f\n", TIMER_EVAL(t));
}

int main(int argc, char **argv) {

  if (argc >= 2) num_fibers = atol(argv[1]);
  if (argc >= 3) iterations = atol(argv[2]);

  printf(" [pingpong] Running benchmark with %ld fiber pairs with %ld iterations each..\n", num_fibers, iterations);

  r_ivars = malloc(sizeof(__cilkrts_ivar) * num_fibers);
  if (r_ivars == NULL) {
    printf(" [pingpong] Failed allocating ivars. Aborting benchmark..\n");
    exit(-1);
  }

  w_ivars = malloc(sizeof(__cilkrts_ivar) * num_fibers);
  if (w_ivars == NULL) {
    printf(" [pingpong] Failed allocating ivars. Aborting benchmark..\n");
    exit(-1);
  }

  progress = malloc(sizeof(long) * num_fibers);
  if (progress == NULL) {
    printf(" [pingpong] Failed allocating progress indicators. Aborting benchmark..\n");
    exit(-1);
  }

  // Turning OFF for now.  Something is wrong and it makes it twice as slow [2014.10.18].
  if(0) cilk_spawn waste_one_core();
  run_benchmark();
  // Tell the wasted core to quit it:
  all_done = 1; __sync_synchronize();
  cilk_sync; // Wait for the waster to come back.
  free(w_ivars);
  free(r_ivars);
  free(progress);
  __cilkrts_dump_stats();
} 

