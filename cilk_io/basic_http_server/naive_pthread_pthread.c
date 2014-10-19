#define PERTURB_VARIANT
#define PTHREAD_PTHREAD_VARIANT
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void *fib_pthread_perturbed(void *n) { 
  
  int *fib = (int *)n;
  pthread_t pthread_fib_thread_1, pthread_fib_thread_2;
  int *thread_1_result, *thread_2_result, *final_result;
  void *thread_1_return_value, *thread_2_return_value;
  int number_less_one = *fib - 1, number_less_two = *fib - 2;
  int thread_create_status, thread_join_status;
  
  if (*fib == 5)
    usleep(250000);
  if ((*fib == 0) || (*fib == 1)) { 
    pthread_exit((void *)fib); 
  } else { 
    thread_1_result = (int *)malloc(sizeof(int *));
    thread_2_result = (int *)malloc(sizeof(int *));

    final_result = (int *)malloc(sizeof(int *));

    thread_create_status = pthread_create(&pthread_fib_thread_1, NULL, (void *)fib_pthread_perturbed, (void *)&number_less_one);
    thread_create_status = pthread_create(&pthread_fib_thread_2, NULL, (void *)fib_pthread_perturbed, (void *)&number_less_two);

    thread_join_status = pthread_join(pthread_fib_thread_1, &thread_1_return_value);
    thread_join_status = pthread_join(pthread_fib_thread_2, &thread_2_return_value);

    thread_1_result = (int *)thread_1_return_value;
    thread_2_result = (int *)thread_2_return_value;

    *final_result = ((*thread_1_result) + (*thread_2_result));

    pthread_exit((void *) (final_result)); 
  } 
}

#include "naive_server_pthread.c"


