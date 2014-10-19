#if 0
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

// Pthreads with sleep perturbation 

void *fibonacci(void *n) {

  int *fib = (int *)n;
  pthread_t pthread_fib_thread_1, pthread_fib_thread_2;
  int *thread_1_result, *thread_2_result, *final_result;
  void *thread_1_return_value, *thread_2_return_value;
  int number_less_one = *fib - 1, number_less_two = *fib - 2;
  int thread_create_status, thread_join_status;

  if ((*fib == 0) || (*fib == 1)) {
    pthread_exit((void *)fib);
  } else {
    thread_1_result = (int *)malloc(sizeof(int *));
    thread_2_result = (int *)malloc(sizeof(int *));

    final_result = (int *)malloc(sizeof(int *));

    thread_create_status = pthread_create(&pthread_fib_thread_1, NULL, (void *)fibonacci, (void *)&number_less_one);
    thread_create_status = pthread_create(&pthread_fib_thread_2, NULL, (void *)fibonacci, (void *)&number_less_two);

    if (*fib == 10) {
      usleep(5000);
    }

    thread_join_status = pthread_join(pthread_fib_thread_1, &thread_1_return_value);
    thread_join_status = pthread_join(pthread_fib_thread_2, &thread_2_return_value);

    thread_1_result = (int *)thread_1_return_value;
    thread_2_result = (int *)thread_2_return_value;

    *final_result = ((*thread_1_result) + (*thread_2_result));

    pthread_exit((void *) (final_result));
  }
}


long fib_pthread_sleep(int n) {

  pthread_t initial_thread;

  int initial_thread_return_value;
  int thread_create_status, thread_join_status;

  thread_create_status = pthread_create (&initial_thread, NULL, (void *)fibonacci, (void *)&number);
  thread_create_status = pthread_join(initial_thread, (void *)&initial_thread_return_value);

  int* result = (int *)initial_thread_return_value;

  return *result;

}

// Cilk with sleep perturbation 

void pfib_cilk_sleep(ivar *iv, int n){
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

  if(n == 10) {
    usleep(5000);
  }

  res = READIV(&iv1, long) + READIV(&iv2, long);
  WRITEIV(iv, res);
}

long fib_cilk_sleep(int n) {

  ivar iv;
  pfib_cilk_sleep(&iv, n);

  long j =  (long) __cilkrts_ivar_read(&iv);
  return j;

}

// Cilk with cilk_sleep perturbation

void pfib_cilk_cilk_sleep(ivar *iv, int n){
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

  if(n == 10) {
    cilk_sleep(5000);
  }

  res = READIV(&iv1, long) + READIV(&iv2, long);
  WRITEIV(iv, res);
}

long fib_cilk_cilk_sleep(int n) {

  ivar iv;
  pfib_cilk_cilk_sleep(&iv, n);

  long j =  (long) __cilkrts_ivar_read(&iv);
  return j;

}
#endif
