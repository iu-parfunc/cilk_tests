#include <stdio.h>
#include <stdlib.h>
#include <cilk/concurrent_cilk.h>
#include <cilk/cilk.h>

void foo(__cilkrts_ivar *iv) {
    sleep(1);
    printf("Attempt to write ivar:\n");
    __cilkrts_ivar_write(iv, (ivar_payload_t)39);
    printf("Wrote successfully, now read:\n");
}

int main(int argc, char **argv) 
{
    printf("Simplest ivar test program...\n");
    __cilkrts_ivar iv;
    __cilkrts_ivar_clear(&iv);

    cilk_spawn foo(&iv);

    int val = (int) __cilkrts_ivar_read(&iv);
    printf("Ivar read successfully: %d\n", val);
    if (val != 39) abort();

    return 0;
}
