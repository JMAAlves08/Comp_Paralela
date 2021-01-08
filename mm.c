#include <stdio.h>
#include <stdlib.h>

/**
 * distribute parallel for
 * real    1m12.598s
   user    1m55.672s
   sys     0m0.984s
 

 * distribute parallel for simd
 * real    1m7.429s
   user    2m1.672s
   sys     0m1.047s
 

 * distribute
 * real    1m35.649s
   user    1m24.328s
   sys     0m0.641s


  *parallel cpu
    real    0m40.680s
    user    1m47.094s
    sys     0m0.500s

  *seq
    real    2m36.414s
    user    2m23.094s
    sys     0m0.594s
 */



void mm(double* a, double* b, double* c, int width) 
{
  #pragma omp target map(to:a[0:( width*width)-1] , b[0:(width*width)-1], c[0:(width*width )-1])
   #pragma omp teams distribute parallel for simd
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < width; j++) {
      double sum = 0;
      for (int k = 0; k < width; k++) {
	double x = a[i * width + k];
	double y = b[k * width + j];
	sum += x * y;
      }
      c[i * width + j] = sum;
    }
  }
}

int main()
{
  int width = 2000;
  double *a = (double*) malloc (width * width * sizeof(double));
  double *b = (double*) malloc (width * width * sizeof(double));
  double *c = (double*) malloc (width * width * sizeof(double));

  for(int i = 0; i < width; i++) {
    for(int j = 0; j < width; j++) {
      a[i*width+j] = i;
      b[i*width+j] = j;
      c[i*width+j] = 0;
    }
  }

  mm(a,b,c,width);

  //  for(int i = 0; i < width; i++) {
  //  for(int j = 0; j < width; j++) {
  //    printf("\n c[%d][%d] = %f",i,j,c[i*width+j]);
  //  }
  // }

}
