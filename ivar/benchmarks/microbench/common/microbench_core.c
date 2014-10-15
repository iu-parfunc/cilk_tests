#include <cilk/concurrent_cilk.h>
#include <cilk/cilk.h>
#include <cilk/cilk_api.h>
#include <cilk/cilk_undocumented.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <cycle.h>
#include <timer.h>

volatile int readers_launched = 0;

void writer(__cilkrts_ivar *array, long num_fibers)
{
  int i;
  //printf("inside spawned writer... WRITING\n");

#ifdef MICROBENCH_ALLBLOCK
  // Wait until the readers are (probably) all blocked:
  // usleep(1000 * 1000); // microseconds
  while(!readers_launched) { }
#endif

  for(i = 0; i < num_fibers; i++){
  unsigned long num = 1000+i;
  __cilkrts_ivar_write(&(array[i]), (ivar_payload_t) num);
  }
  //printf("inside spawned writer.. ALL WRITES DONE\n");
}

void read_one(int i, __cilkrts_ivar *iv){
 long val;
  val = (long)  __cilkrts_ivar_read(iv); 
  //printf("read %d with value %d\n", i, val);
}

void readers(__cilkrts_ivar *array, long num_fibers) {
  int i;
  for(i = 0; i < num_fibers; i++) {
    cilk_spawn read_one(i, &array[i]);
  }
  readers_launched = 1; __sync_synchronize();
  // printf("====     Done spawning readers.  Can't know quite whether they've blocked yet.\n");
  printf(".");fflush(stdout);
}

int main(int argc, char **argv){
  //printf("===== Microbench many blocking ======\n");

  ticks start, end;
  my_timer_t t;
  long num_fibers = 1000; // Default
  long num_iters = 100; // Default
  if (argc >= 2) num_fibers = atoi(argv[1]);
  if (argc >= 3) num_iters  = atoi(argv[2]);
  
  __cilkrts_ivar *all_ivars = __cilkrts_new_ivar_array(num_fibers);
  if(NULL == all_ivars) perror("CALLOC failed to allocate array\n");

  //printf("creating %d blocked fibers\n", num_fibers);
  //printf("created array of ivars\n");

  printf("==== microbench_many_blocking test program, fibers=%ld, iters=%ld\n", num_fibers, num_iters);
#ifdef MICROBENCH_ALLBLOCK
  printf("==== Running in ALLBLOCK mode....\n");
#elif defined(MICROBENCH_NOBLOCK)
  printf("==== Running in NOBLOCK mode....\n");
#elif defined(MICROBENCH_RACE)
  printf("==== Running in RACE mode....\n");
#else
  #error "Must be compiled with -DMICROBENCH_NOBLOCK or -DMICROBENCH_ALLBLOCK or -DMICROBENCH_RACE !!"
#endif

  int i; 
  TIMER_RESET(t);
  TIMER_START(t);
  start = getticks();
  for (i=0; i<num_iters; i++) {
    __cilkrts_ivar_array_clear(all_ivars, num_fibers);
    readers_launched = 0;  __sync_synchronize();
    cilk_spawn writer(all_ivars, num_fibers);
#ifdef MICROBENCH_NOBLOCK
      cilk_sync;
#endif
    cilk_spawn readers(all_ivars, num_fibers);
    cilk_sync;
  }
  end = getticks();
  TIMER_STOP(t);
  printf("\nSELFTIMED: %lf\n", TIMER_EVAL(t) );
  printf("==== All iterations complete, checking final sum.\n");

  // Only after the last iteration, check the sum:
  long long sum = 0;
  for(i = 0; i < num_fibers; i++) {
    sum += (long) __cilkrts_ivar_read(&all_ivars[i]);
  }
  //printf("sum of all values: %ld\n", sum);

  long long expected = 0;
  for(i = 0; i < num_fibers; i++) {
    expected += 1000 + i;
  }

  free(all_ivars);
  if(sum != expected){
    fprintf(stderr, "BAD SUM!!\n");
    abort();
    return 1;
  } else {
    //printf("SUM CORRECT\n");
    printf("%ldt%f\t%lf\n", num_fibers, TIMER_EVAL(t), elapsed(end,start));
    __cilkrts_dump_stats();
    return 0;
  }
}
