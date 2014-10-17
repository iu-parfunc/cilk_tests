#include <stdio.h>
#include <stdlib.h>
#include <cilk/cilk.h>
#include <cilk/concurrent_cilk.h>
#include <timer.h>
#include <cycle.h>

int main(int argc, const char *argv[])
{
  cilk_io_init();
  printf("BEFORE\n");
  int i = 0;
  /*for (i = 0; i < 20; i++)*/
    cilk_spawn cilk_sleep(500);
  /*sleep(2);*/
  cilk_sync;
  printf("AFTER\n");
  cilk_io_teardown();
  return 0;
}
