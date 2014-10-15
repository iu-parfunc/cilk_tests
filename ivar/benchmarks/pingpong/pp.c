
#include <stdio.h>
#include <stdlib.h>

#include <cilk/cilk.h>
#include <cilk/concurrent_cilk.h>
#include "../../../common/timer.h"

void ping(long id);
void pong(long id, __cilkrts_ivar* w_ivar, __cilkrts_ivar* r_var);

long iterations = 1000;
long num_fibers = 1;

long* progress;

void ping(long id) {

  while (1) {

    // printf(" [ping] w_ivar[%ld] address : %p\n", id, &w_ivars[id]);
    // printf(" [ping] r_ivar[%ld] address : %p\n", id, &r_ivars[id]);

    __cilkrts_ivar* w_ivar = malloc(sizeof(__cilkrts_ivar));
    __cilkrts_ivar* r_ivar = malloc(sizeof(__cilkrts_ivar));
    __cilkrts_ivar_clear(w_ivar);
    __cilkrts_ivar_clear(r_ivar);

    // for now we are passing stack allocated ivars. should be safe since we just
    // doing a subroutine call
    cilk_spawn pong(id, w_ivar, r_ivar); 

    // printf(" [ping] writing to ivar %p\n", w_ivar);
    __cilkrts_ivar_write(w_ivar, 1);

    // printf(" [ping] blocking on ivar %p\n", r_ivar);
    __cilkrts_ivar_read(r_ivar);

    progress[id]++;
    
    free(w_ivar);
    free(r_ivar);

    // __sync_fetch_and_add(&progress[id], 1);
    if (progress[id] >= iterations) {
      return;
    }

  }
}

void pong(long id, __cilkrts_ivar *w_ivar, __cilkrts_ivar *r_ivar) {

    __cilkrts_ivar_read(w_ivar);

    // __sync_synchronize();
    
    // printf(" [pong] writing to ivar %p\n", &r_ivars[id]);
    printf(" [pong] progress[%ld] : %ld\n", id, progress[id]);
    __cilkrts_ivar_write(r_ivar, 1);


    /*
    if (progress[id] >= iterations) {
      return;
    }
    */


}

/** 
 * Usage ./pingpong_ivar.exe <num-of-fiber-pairs> <num-of-iterations>
 *
 * */

int main(int argc, char **argv) {

  if (argc >= 2) num_fibers = atol(argv[1]);
  if (argc >= 3) iterations = atol(argv[2]);

  printf(" [pingpong] Running benchmark with %ld fiber pairs with %ld iterations each..\n", num_fibers, iterations);

  // r_ivars = malloc(sizeof(__cilkrts_ivar) * num_fibers);

  /*
  if (r_ivars == NULL) {
    printf(" [pingpong] Failed allocating ivars. Aborting benchmark..\n");
    exit(-1);
  }

  // w_ivars = malloc(sizeof(__cilkrts_ivar) * num_fibers);

  if (w_ivars == NULL) {
    printf(" [pingpong] Failed allocating ivars. Aborting benchmark..\n");
    exit(-1);
  }
  */

  progress = malloc(sizeof(long) * num_fibers);

  if (progress == NULL) {
    printf(" [pingpong] Failed allocating progress indicators. Aborting benchmark..\n");
    exit(-1);
  }

  my_timer_t t;

  int i;
  for (i = 0; i < num_fibers; i++) {
    progress[i] = 0;
    // printf(" [pingpong] w_ivars[%d] address : %p\n", i, &w_ivars[i]); 
    // printf(" [pingpong] r_ivars[%d] address : %p\n", i, &r_ivars[i]); 
    // __cilkrts_ivar_clear(&w_ivars[i]);
    // __cilkrts_ivar_clear(&r_ivars[i]);
  }

  // printf(" [pingpong] w_ivars[%d] address : %p\n", 0, &w_ivars[0]); 
  // printf(" [pingpong] r_ivars[%d] address : %p\n", 0, &r_ivars[0]); 

  TIMER_START(t);

  for (i = 0; i < num_fibers; i++) {
    cilk_spawn ping(i);
  }

  printf(" [pingpong] Before cilk_sync\n");

  cilk_sync;

  printf(" [pingpong] After cilk_sync\n");

  TIMER_STOP(t);

  printf(" [pingpong] time taken %f\n", TIMER_EVAL(t));

  // free(w_ivars);
  // free(r_ivars);
  free(progress);

}
