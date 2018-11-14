#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

void populate_array(int *array, int width) {
  for (int i=0; i < width*width; i++) {
    array[i] = rand();
  }
}

void transpose(int *array, int m, int n, int blocksize) {
  int *out_array = malloc(m*n*sizeof(int));
  for (int i=0; i < n; i += blocksize) {
    for (int j=0; j < n; j+= blocksize) {
      for (int k=i; k < i + blocksize; ++k) {
        for (int l=j; l < j + blocksize; ++l) {
          out_array[l*n+k] = array[k*n+l];
        }
      }
    }
  }
  for (int i=0; i < m*n; i++) {
    array[i] = out_array[i];
  }
  free(out_array);
}


int main(int argc, char **argv) {

  if (argc != 3) {
    fprintf(stderr, "Wrong number of arguments. Usage: <width of matrix> <width of block>.\n");
    return -1;
  }

  int width = atoi(argv[1]);
  int blocksize = atoi(argv[2]);
  int *in_array = malloc(width * width * sizeof(int));
  struct timeval start, stop;

  populate_array(in_array, width);
  gettimeofday(&start, 0);
  transpose(in_array, width, width, blocksize);
  gettimeofday(&stop, 0);
  int elapsed_s = (stop.tv_sec - start.tv_sec);
  int elapsed_ms = ((stop.tv_sec - start.tv_sec) * 1000000) + (stop.tv_usec - start.tv_usec);
  printf("%d s\n", elapsed_s);
  printf("%d ms\n", elapsed_ms);
  free(in_array);
// blocksize = 4 might be quickest.
// Pretty sure this code works.
  return 0;
}
