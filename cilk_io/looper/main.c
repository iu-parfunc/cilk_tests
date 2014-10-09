

#include "pthread.h"
#include "cilk/cilk.h"
#include "cilk/concurrent_cilk.h"
#include <unistd.h>

int main () {

  cilk_spawn sleep(10);

  return 0;
}
