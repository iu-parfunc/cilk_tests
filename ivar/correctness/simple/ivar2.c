
// A parallel write that may happen after (in realtime) the read.

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <cilk/concurrent_cilk.h>
// For access to Cilk RTS internals:
#include <internal/abi.h>
#include <cilk/cilk.h>
#include <cilk/cilk_api.h>
#include "timing.h"

// TOGGLES:
#define DELAY_WRITER 
//#define DELAY_READER

#define DELAY (1000*1000)


void writer(__cilkrts_ivar* iv) {
    int val = 39;
    printf("     Inside spawned writer... (approx stack addr %p) sleeping for a bit\n", &val);
#ifdef DELAY_WRITER
    __cilkrts_usleep(DELAY); printf("  Writer done sleeping, now returning to sync point.\n");
#endif
    __cilkrts_ivar_write(iv, (ivar_payload_t)val);
    printf("     Inside spawned writer... WRITE OF %d DONE (ivar %p).\n", val, iv);

}

void fun() {
     __cilkrts_ivar iv;
    __cilkrts_ivar_clear(&iv);

    printf("   Spawn to write ivar:\n");
    cilk_spawn writer(&iv);

    printf("   After spawn, wrote or stolen successfully, now read:\n");

    unsigned long val = (unsigned long)__cilkrts_ivar_read(&iv);
    __cilkrts_worker* w_ = __cilkrts_get_tls_worker();
    printf("   Ivar (%p) read successfully: %lu w=%d\n",  &iv, val, w_->self);

    struct __cilkrts_worker* w = __cilkrts_get_tls_worker();
    printf("fun(): Going to attempt Sync.  Current Cilk worker = %d\n", w->self);

#ifdef DELAY_READER
    __cilkrts_usleep(DELAY);   printf("fun(): Reader done sleeping, now sync\n");
#endif
    cilk_sync;
    printf("   fun(): reached position AFTER cilk_sync\n");

    if (val != 39) { printf("TEST ERROR - BAD VALUE, %ld, EXPECTED 39 - ABORTING!\n", val); abort(); }
}

int main(int argc, char **argv) 
{
    printf("==== ivar2: simple test program...\n");

    // cilk_spawn fun();
    fun();

    printf("==== ivar2: Finished.\n");
    return 0;
}
