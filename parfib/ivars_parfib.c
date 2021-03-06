#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <cilk/cilk.h>
#include <cilk/concurrent_cilk.h>
#include <cilk/cilk_undocumented.h> //for dump_stats()
#include <timer.h>
#include <cycle.h>


#define READIV(IV, TYPE) ((TYPE)__cilkrts_ivar_read(IV))
#define WRITEIV(IV,VAL) (__cilkrts_ivar_write(IV,(ivar_payload_t)VAL))
#define CLEARIV(IV) (__cilkrts_ivar_clear(IV))

typedef __cilkrts_ivar ivar;

int perturbation_point;

void pfib(ivar *iv, int n){
  long res;
   ivar iv1;
   ivar iv2;
  CLEARIV(&iv1);
  CLEARIV(&iv2);

  if(n < 2) { 
    WRITEIV(iv, 1);
    return;
  }


  cilk_spawn pfib(&iv1, n-1);
  cilk_spawn pfib(&iv2, n-2);

#ifdef PERTURB_PTHREAD_SLEEP
  if(n == perturbation_point) {
    usleep(5000);
  }
#endif

#ifdef PERTURB_CILK_SLEEP
  if(n == perturbation_point) {
    cilk_sleep(5000);
  }
#endif

  res = READIV(&iv1, long) + READIV(&iv2, long);
  //printf("fib of %d read of ivars %p and %p writing value: %ld\n", n, &iv1, &iv2, res);
  WRITEIV(iv, res);
}

int main(int argc, char** argv) {
  int n;
  long j = 0;
  my_timer_t t;


  if (argc>1)
    n = atoi(argv[1]);
  else
    n = 42;

  if (argc>2) {
    perturbation_point = atoi(argv[2]);
  } else {
    perturbation_point = n/2;
  }

  ivar iv;
  CLEARIV(&iv);

  TIMER_RESET(t);  
  TIMER_START(t);
  ticks t1 = getticks();
  pfib(&iv, n);
  j =  (long) __cilkrts_ivar_read(&iv);
  ticks t2 = getticks();
  TIMER_STOP(t);

  printf("result: %ld\t", j);
  printf("SELFTIMED: %lf\n", TIMER_EVAL(t));
  printf("%d\t%f\t%lf\t%d\n", n, TIMER_EVAL(t), elapsed(t2,t1), __cilkrts_get_total_workers());
  //printf("%d\t%f\n", n, TIMER_EVAL(t));
  __cilkrts_dump_stats();
  return 0;
}
