

#include "pthread.h"
#include "cilk/cilk.h"
#include "cilk/concurrent_cilk.h"
#include <unistd.h>


char* msg = "Here is cilk_write...\n";

void foo()  {
  printf (" [hello] Hello world from Cilk\n");  
  //  cilk_read()
  cilk_write(STDOUT_FILENO, msg, strlen(msg));
}

int main () {
  printf(" [hello] Start of main function\n");

  if (cilk_io_init()) {
    fprintf(stderr,"cilk_io_init failed\n");
    exit(1);
  }

  printf(" [hello] Pthread launched for IO dispatcher (event loop)\n");
  cilk_spawn foo();

  // sleep(10);
  return 0;
}
