// How long does it take to do a single pause_a_bit.

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <cilk/cilk.h>
#include <cilk/ivar.h>
#include <cilk/concurrent_cilk.h>

#include <pthread.h>
#include <cycle.h>

#include <internal/abi.h>
#include <cilk/cilk_api.h>


void print_context() 
{
   pthread_t id = pthread_self(); 
   char buf[512];
   struct __cilkrts_worker* tw = __cilkrts_get_tls_worker();
//   fprintf(stderr, " context [tid/W %3d %2d] \n", (int)(((int)id)%1000), tw->self); 
}

ticks start, end;
void test_spawn_helper() {
    end = getticks();
}
int test_spawn() {
    start = getticks();
    cilk_spawn test_spawn_helper();
    //printf(" ** Cost of a spawn: %lf cycles\n", elapsed(end,start));
}

double test_pause() {
    struct __cilkrts_worker* w = (struct __cilkrts_worker*)__cilkrts_get_tls_worker();
    //printf("Starting test with current worker = %d\n", w->self);
    print_context();
    ticks start = getticks();
    __cilkrts_pause(w);
    ticks end   = getticks();
   // print_context();
    return elapsed(end,start);
}

void test_repeat_set_then_jmp() 
{
    int counter = 0;
    ticks before,after;
    jmp_buf tmp;

    before = getticks();
    while (counter < 1000) {
        if ( ! setjmp(tmp) ) 
        {
            longjmp(tmp, 1);
            abort();
        }
        counter ++;
    }
    after = getticks();
    //printf(" ** Avg cost of 1000 setjmp/longjmp pairs: %lf cycles.\n", elapsed(after,before) / 1000);
    return;
}


int main(int argc, char **argv) 
{
    //printf("==== measure_one_pause test program...\n");

    ticks start = getticks();
    ticks end   = getticks();
    //printf(" ** Smallest measurable increment: %lf cycles.\n", elapsed(end,start));

    jmp_buf tmp;    
    ticks preset,postset,postjmp;
    preset = getticks();
    if ( ! setjmp(tmp) ) {
        postset = getticks();
        longjmp(tmp, 1);
        abort();
    }
    postjmp = getticks();
    //printf(" ** Cost of a setjmp: %lf cycles.\n", elapsed(postset, preset));
    //printf(" ** Cost of a longjmp: %lf cycles.\n", elapsed(postjmp, postset));

    preset = getticks();
    for(int i=0; i<10000; i++)
        setjmp(tmp);
    postset = getticks();
    //printf(" ** Avg cost over 10,000 setjmps: %lf cycles.\n", elapsed(postset, preset) / 10000);

    test_repeat_set_then_jmp(); 

    test_spawn();

    // TODO: Need to add entrypoints that do not assume the thread is bound to cilk:
    // __cilkrts_pause(w);    

    double durat = cilk_spawn test_pause();    
        cilk_sync;
    //printf("==== Done with pause, elapsed cycles: %lf \n", durat);
    //printf("%lf \n", durat);

    struct __cilkrts_worker* w = (struct __cilkrts_worker*)__cilkrts_get_tls_worker();
    ticks before = getticks();
    for(int i=0; i<=1000; i++)
        __cilkrts_pause(w);
    ticks after = getticks();
    // TZ: Why are they so disparate
    //printf("%lf\t%lf \n", durat, elapsed(after, before)/ (float)1000);
    printf("%lf \n", durat);
    //printf("==== Done with 1000 pauses, average elapsed cycles: %lf \n", elapsed(after,before) / 1000); // I feel like this number is incorrect...

    return 0;
}
