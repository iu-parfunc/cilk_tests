#include <stdio.h>
#include <cilk/cilk.h>
#include <cilk/concurrent_cilk.h>


void fun() {
__cilkrts_ivar iv1;
__cilkrts_ivar iv2;
__cilkrts_ivar iv3;
__cilkrts_ivar iv4;
__cilkrts_ivar iv5;

__cilkrts_ivar_clear(&iv1);
__cilkrts_ivar_clear(&iv2);
__cilkrts_ivar_clear(&iv3);
__cilkrts_ivar_clear(&iv4);
__cilkrts_ivar_clear(&iv5);

int i1 = 0, i2 = 0, i3 = 0, i4 = 0, i5 = 0;

printf("spawning reader1\n");
i1 = cilk_spawn __cilkrts_ivar_read(&iv1);
printf("spawning reader2\n");
i2 = cilk_spawn __cilkrts_ivar_read(&iv2);
printf("spawning reader3\n");
i3 = cilk_spawn __cilkrts_ivar_read(&iv3);
printf("spawning reader4\n");
i4 = cilk_spawn __cilkrts_ivar_read(&iv4);
printf("spawning reader5\n");
i5 = cilk_spawn __cilkrts_ivar_read(&iv5);

printf("done spawning readers. Now starting to write\n");

printf("writing 1 to iv1\n");
cilk_spawn __cilkrts_ivar_write(&iv1, (ivar_payload_t) 1);
printf("writing 2 to iv2\n");
cilk_spawn __cilkrts_ivar_write(&iv2, (ivar_payload_t) 2);
printf("writing 3 to iv3\n");
cilk_spawn __cilkrts_ivar_write(&iv3, (ivar_payload_t) 3);
printf("writing 4 to iv4\n");
cilk_spawn __cilkrts_ivar_write(&iv4, (ivar_payload_t) 4);
printf("writing 5 to iv5\n");
cilk_spawn __cilkrts_ivar_write(&iv5, (ivar_payload_t) 5);

printf("going for a sync now!\n");

cilk_sync;
if ((i1+i2+i3+i4+i5) == 15)
  printf("sum of ivars is corect! (15)\n");
else 
  printf("sum wrong!! (expected 15, got %d)\n", i1+i2+i3+i4+i5);

}

int main(int argc, char **argv) {
  printf("nested deadlock test\n");
  fun();
}
