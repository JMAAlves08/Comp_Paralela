#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

/*
   TEMPO SEQUENCIAL:
   test passed
   real    0m4.384s
   user    0m4.382s
   sys     0m0,000s
   --------------------------------------------------
   TEMPO COM ESCALONAMENTO PADRÃO:
   test passed
   real    0m4.236s
   user    0m6.793s
   sys     0m0,000s
   --------------------------------------------------
   TEMPO COM ESCALONAMENTO DYNAMIC: 
   test passed
   real    0m3.049s
   user    0m6.086s
   sys     0m0,000s
*/

int main() 
{
   int i, j, n = 30000;

   // Allocate input, output and position arrays
   int *in = (int*) calloc(n, sizeof(int));
   int *pos = (int*) calloc(n, sizeof(int));   
   int *out = (int*) calloc(n, sizeof(int));  

   for(i=0; i < n; i++)
      in[i] = n-i;  

   // Print input array
   //   for(i=0; i < n; i++) 
   //      printf("%d ",in[i]);
   
   // Silly sort (you have to make this code parallel)
   #pragma omp parallel for private(i,j) schedule(dynamic,8) num_threads(2)
   for(i=0; i < n; i++) 
      for(j=0; j < n; j++)
      if(in[i] > in[j]) 
            pos[i]++;	

   // Move elements to final position
   for(i=0; i < n; i++) 
      out[pos[i]] = in[i];
   
   // print output array
   //   for(i=0; i < n; i++) 
   //      printf("%d ",out[i]);

   // Check if answer is correct
   for(i=0; i < n; i++)
      if(i+1 != out[i]) 
      {
         printf("test failed\n");
         exit(0);
      }

   printf("test passed\n");
}  