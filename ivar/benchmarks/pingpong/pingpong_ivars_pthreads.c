
#include <stdio.h>
#include <stdlib.h>

#include <cilk/cilk.h>
#include <pthread.h>
#include <cilk/concurrent_cilk.h>
#include "../../../common/timer.h"

void* ping(void* ptr);
void* pong(void* ptr);

long iterations = 10000;
long num_fibers = 2;

pthread_t* threads;
pthread_mutex_t* locks; 
pthread_cond_t* condc;
pthread_cond_t* condp;
long* ids;
long* shared;

long* progress;

void* ping(void *ptr) {

  long id = *((long*) ptr);

  while (1) {

    // // printf(" [ping] w_ivar[%ld] address : %p\n", id, &w_ivars[id]);
    // // printf(" [ping] r_ivar[%ld] address : %p\n", id, &r_ivars[id]);

    pthread_mutex_lock(&locks[id]);

    printf(" [ping] producer %ld acquired mutex..\n", id);
    fflush(stdout);

    while (shared[id] > 0) {
      printf(" [ping] producer %ld going to wait..\n", id);
      fflush(stdout);
      pthread_cond_wait(&condp[id], &locks[id]);
    }

    shared[id]++;

    printf(" [ping] unlocking the mutex %ld..\n", id);
    fflush(stdout);
    pthread_mutex_unlock(&locks[id]);
    printf(" [ping] signalling consumer %ld..\n", id);
    fflush(stdout);
    pthread_cond_signal(&condc[id]);

    __sync_fetch_and_add(&progress[id], 1);
    if (progress[id] >= iterations) {
      pthread_mutex_lock(&locks[id]);
      shared[id]++;
      pthread_mutex_unlock(&locks[id]);
      pthread_cond_signal(&condc[id]);
      printf("[ping] producer %ld exiting... $$$$$$$$$$\n", id);
      fflush(stdout);
      // __cilkrts_ivar_write(&w_ivars[id], 1); // Unblocks the consumer so it can finish
      pthread_exit(NULL);
    }
  }
}

void* pong(void* ptr) {

  long id = *((long*) ptr);

  while (1) {

    // __cilkrts_ivar_read(&w_ivars[id]);
    // __cilkrts_ivar_clear(&w_ivars[id]);
    
    pthread_mutex_lock (&locks[id]);
    printf(" [pong] consumer %ld acquired mutex..\n", id);
    fflush(stdout);
    
    while (shared[id] == 0) {
      printf(" [pong] consumer %ld going to wait..\n", id);
      fflush(stdout);
      pthread_cond_wait(&condc[id], &locks[id]);
    }

    shared[id]--;

    printf(" [pong] signalling producer %ld..\n", id);
    fflush(stdout);
    pthread_mutex_unlock(&locks[id]);
    pthread_cond_signal(&condp[id]);

    // __sync_synchronize();
    
    // // printf(" [pong] writing to ivar %p\n", &r_ivars[id]);
    printf(" [pong] progress[%ld] : %ld\n", id, progress[id]);
    // __cilkrts_ivar_write(&r_ivars[id], 1);


    if (progress[id] >= iterations) {
      printf("[pong] consumer %ld exiting... ^^^^^^^^^^^^^^^\n", id);
      fflush(stdout);

      pthread_exit(NULL);
    }

  }

}

/** 
 * Usage ./pingpong_ivar.exe <num-of-fiber-pairs> <num-of-iterations>
 *
 * */

int main(int argc, char **argv) {

  if (argc >= 2) num_fibers = atol(argv[1]);
  if (argc >= 3) iterations = atol(argv[2]);

  printf(" [pingpong] Running benchmark with %ld fiber pairs with %ld iterations each..\n", num_fibers, iterations);

  threads = malloc(sizeof(pthread_t) * num_fibers * 2);

  if (threads == NULL) {
    printf(" [pingpong] Failed allocating pthreads. Aborting benchmark..\n");
    exit(-1);
  }

  locks = malloc(sizeof(pthread_mutex_t) * num_fibers);

  if (locks == NULL) {
    printf(" [pingpong] Failed allocating mutex locks. Aborting benchmark..\n");
    exit(-1);
  }

  condp = malloc(sizeof(pthread_cond_t) * num_fibers);

  if (condp == NULL) {
    printf(" [pingpong] Failed allocating conditions. Aborting benchmark..\n");
    exit(-1);
  }

  condc = malloc(sizeof(pthread_cond_t) * num_fibers);

  if (condc == NULL) {
    printf(" [pingpong] Failed allocating conditions. Aborting benchmark..\n");
    exit(-1);
  }

  progress = malloc(sizeof(long) * num_fibers);

  if (progress == NULL) {
    printf(" [pingpong] Failed allocating progress indicators. Aborting benchmark..\n");
    exit(-1);
  }

  shared = malloc(sizeof(long) * num_fibers);

  if (shared == NULL) {
    printf(" [pingpong] Failed allocating shared data for bechmark. Aborting benchmark..\n");
    exit(-1);
  }

  ids = malloc(sizeof(long) * num_fibers);

  if (shared == NULL) {
    printf(" [pingpong] Failed allocating shared data for bechmark. Aborting benchmark..\n");
    exit(-1);
  }

  my_timer_t t;

  int i;
  for (i = 0; i < num_fibers; i++) {
    progress[i] = 0;
    shared[i] = 0;
    ids[i] = i;
    // printf(" [pingpong] w_ivars[%d] address : %p\n", i, &w_ivars[i]); 
    // printf(" [pingpong] r_ivars[%d] address : %p\n", i, &r_ivars[i]); 
    pthread_mutex_init(&locks[i], NULL);
    pthread_cond_init(&condc[i], NULL);
    pthread_cond_init(&condp[i], NULL);
  }

  // printf(" [pingpong] w_ivars[%d] address : %p\n", 0, &w_ivars[0]); 
  // printf(" [pingpong] r_ivars[%d] address : %p\n", 0, &r_ivars[0]); 

  TIMER_RESET(t);
  TIMER_START(t);

  for (i = 0; i < num_fibers; i++) {
    pthread_create(&threads[i], NULL, ping, &ids[i]);
    pthread_create(&threads[i+1], NULL, pong, &ids[i]);

    pthread_join(threads[i],NULL);
    pthread_join(threads[i+1], NULL);
  }

  // printf(" [pingpong] Before cilk_sync\n");

  // printf(" [pingpong] After cilk_sync\n");

  TIMER_STOP(t);

  printf("SELFTIMED: %f\n", TIMER_EVAL(t));

  for (i=0; i<num_fibers; i++) {
    assert(shared[i] == 0);
  }

  free(locks);
  free(ids);
  free(shared);
  free(progress);
  free(condc);
  free(condp);

}
