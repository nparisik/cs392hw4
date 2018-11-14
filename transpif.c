#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#define ROUND(x, y) (((x)+((y)-1)) & -(y))

void populate_array(int *array, int height, int width) {
  for (int i=0; i < height*width; i++) {
    array[i] = rand();
  }
}

void transpose_helper(int *array, int *out_array, int a, int b, int blocksize) {
  for (int i=0; i < blocksize; i++) {
    for (int j=0; j < blocksize; j++) {
      out_array[j*b+i] = array[i*a+j];
    }
  }
}

void transpose(int *array, int *out_array, int m, int n, int a, int b, int blocksize) {
  for (int i=0; i < n; i += blocksize) {
    for (int j=0; j < m; j += blocksize) {
      transpose_helper(&array[i*a+j], &out_array[j*b+i], a, b, blocksize);
    }
  }
}

// Same as transp.c, except matrix is no longer square/dimensions power of 2.
int main(int argc, char **argv) {

  if (argc != 4) {
    fprintf(stderr, "Wrong number of arguments. Usage: <matrix height> <matrix width> <block width>.\n");
    return -1;
  }

  int height = atoi(argv[1]);
  int width = atoi(argv[2]);
  int blocksize = atoi(argv[3]);
  int n = atoi(argv[1]);
  int m = atoi(argv[2]);
  int ra = ROUND(m, blocksize);
  int rb = ROUND(n, blocksize);
  int *in_array = malloc(ra * rb * sizeof(int));
  int *out_array = malloc(ra * rb * sizeof(int));
  struct timeval start, stop;

  populate_array(in_array, height, width);
  gettimeofday(&start, 0);
  transpose(in_array, out_array, height, width, ra, rb, blocksize);
  gettimeofday(&stop, 0);
  int elapsed_s = (stop.tv_sec - start.tv_sec);
  int elapsed_ms = ((stop.tv_sec - start.tv_sec) * 1000000) + (stop.tv_usec - start.tv_usec);
  printf("%d s\n", elapsed_s);
  printf("%d ms\n", elapsed_ms);
  free(in_array);
  free(out_array);

  return 0;
}
