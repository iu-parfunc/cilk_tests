#include <stdio.h>
#include <stdlib.h>
#include <cilk/cilk.h>
#include <cilk/concurrent_cilk.h>
#include <timer.h>
#include <cycle.h>
#include <string.h>

// This benchmark currently does a slighty odd thing.  It doesn't
// compute a tiled version of the scalar wavefront algorithm.  It
// computes a single flat instance of wavefront, where each "element"
// is a bigger piece of work -- a tile-to-tile opration with memory
// traffic.

int TILE_DIM = 16;
// Size of tiled matrix.  Total size depends on MATRIX_DIM*TILE_DIM
int MATRIX_DIM = 64;

// typedef ivar_payload_t tile;
typedef long tile;
typedef ivar_t matrix;

// ================================================================================
// General Helpers

void sum_tiles(tile *src, tile *dst) 
{
  int i;
  for(i=0; i < TILE_DIM * TILE_DIM; i++) {
    dst[i] += src[i];
  } 
}
long sum_tile(tile *src)
{
  int i; long acc = 0;
  for(i=0; i < TILE_DIM * TILE_DIM; i++) {
    acc += src[i];
  }
  return acc;
}


void init_tile(tile *t) { memset(t, 1, TILE_DIM*TILE_DIM); } 

// ================================================================================
// Tile-to-tile operations:

void do_tile_iv(matrix *mat, int i, int j) 
{
  ivar_t *cur_tile = &(mat[i * MATRIX_DIM + j]);
  tile *src; 
  tile *dst = (tile *) malloc(sizeof(tile) * TILE_DIM * TILE_DIM);
  memset(dst, 1, sizeof(tile) * TILE_DIM * TILE_DIM);

  //add the tile diagonally above to the current tile.
  if(i>0 && j>0) {
     src = (tile *) read_iv(&(mat[(i-1) * MATRIX_DIM + (j-1)]));
     sum_tiles(src, dst);
  }

  //if possible add the tile above the current tile.
  if (i>0) {
    src = (tile *) read_iv(&(mat[(i-1)* MATRIX_DIM + j]));
    sum_tiles(src, dst);
  } 

  //if possible add the tile to the left of the current tile
  if (j>0) {
    src = (tile *) read_iv(&(mat[i * MATRIX_DIM + (j-1)]));
    sum_tiles(src, dst);
  }

  // printf("cur tile %p val %ld idx %i\n", cur_tile, *cur_tile, i*MATRIX_DIM + j);
  write_iv(cur_tile, (ivar_payload_t) dst);
}

// ================================================================================
// Non-IVar versions:

// Sequential version:
void sequential(matrix* mat)
{
    printf(" *** Begin SEQUENTIAL traversal to fill matrix: for | for | do_tile\n");
    for (int i=0; i < MATRIX_DIM; i++) 
    for (int j=0; j < MATRIX_DIM; j++) {
      do_tile_iv(mat,i,j);
    }
    printf("Done with sequential traversal...\n");
}

// Non-IVar parallel version: 
void divide_and_conquer(matrix* mat,int i, int j, int w, int h) 
{
    // TODO -- INSERT ERROR MESSAGE IF NOT POWER OF TWO!!!  use popcount if you want ;-).
  // printf(" *** Divide and conquer: pos %d,%d dims %dx%d\n", i,j,w,h);
    // ASSUME POWER OF TWO!
    if (w == 1 && h == 1) 
    {
      do_tile_iv(mat,i,j);
    }
    else if (w == 1 || h == 1) 
    {
        fprintf(stderr, "wavefront.c: ERROR INVARIANT BROKEN!\n");
        abort();
    }
    else
    {
        int mid_row = i + w/2;
        int mid_col = j + h/2;
	// NW by itself, then NE/SW in par, then SE by itself:
  	           divide_and_conquer(mat, i      ,j,       w/2,h/2); // nw         
        cilk_sync;
        cilk_spawn divide_and_conquer(mat, mid_row,j,       w/2,h/2); // ne
                   divide_and_conquer(mat, i      ,mid_col, w/2,h/2); // sw
        cilk_sync; 
    	           divide_and_conquer(mat, mid_row,mid_col, w/2,h/2); // se 

// Try with and without a sync in the ivar version...
    }
}


// ================================================================================
// IVar versions


// IVar version 1: 
// rows and column elements are computed in parallel.
void traverse_by_par_row_and_column(matrix *mat) {
  int i,j;
  for (i=0; i < MATRIX_DIM; i++)  {
    for (j=0; j < MATRIX_DIM; j++)  {
      cilk_spawn do_tile_iv(mat,i,j);
    }
  }
}

// ================================================================================

int main(int argc, char **argv) {
  matrix* mat = __cilkrts_new_ivar_array(MATRIX_DIM*MATRIX_DIM);
  my_timer_t t; TIMER_RESET(t);
  ticks start, end;
  unsigned long long sum;
  char* version;

  printf("Usage: %s mode matrixDimension tileDimension\n", argv[0]);
  printf("  mode one of { sequential dnc ivar }\n");
  if (argc > 4)
    {
        printf("Too many command line arguments!\n"); 
        exit(-1);
    }
  if (argc > 1)  version = argv[1];
  if (argc > 2)  MATRIX_DIM = atoi(argv[2]);
  if (argc > 3)  TILE_DIM   = atoi(argv[3]);

  printf("mat %p\n", mat);

  if(! strcmp("sequential",version) ) {

    TIMER_START(t);
    start = getticks(); 
    sequential(mat);
    end = getticks();
    TIMER_STOP(t);

  } else if(! strcmp("dnc",version) ) {

    TIMER_START(t);
    start = getticks(); 
    divide_and_conquer(mat, 0,0, MATRIX_DIM, MATRIX_DIM);
    end = getticks();
    TIMER_STOP(t);

  } else if(! strcmp("ivar",version) ) {

    TIMER_START(t);
    start = getticks(); 
    traverse_by_par_row_and_column(mat);
    end = getticks();
    TIMER_STOP(t);

  } else {
    fprintf(stderr, "Unrecognized mode %s\n", version);
    return 1;
  }

  printf("SELFTIMED: %lf\n", TIMER_EVAL(t) );
  printf("%i\t%f\t%lf\n", MATRIX_DIM, TIMER_EVAL(t), elapsed(end,start));

  printf("The final tile should contain the sum of the others and when we sum it...\n");
  int i=MATRIX_DIM-1; int j = i;
  long result = sum_tile((tile*) read_iv(&(mat[i * MATRIX_DIM + (j-1)])));
  printf(" ... we get %ld\n", result);
  free(mat);
  return 0;
}

