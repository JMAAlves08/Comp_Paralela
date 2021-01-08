/*
* Adapted from: http://w...content-available-to-author-only...s.org/sieve-of-eratosthenes
*/
 
 /**
  * schedule 1
  * real    0m2,258s
    user    0m0,000s
    sys     0m0,000s
  */
 /**
  * schedule 2
  * real    0m1,844s
    user    0m0,000s
    sys     0m0,000s
  */
 /**
  * schedule 4
  * real    0m1,815s
    user    0m0,030s
    sys     0m0,015s
  */
 /**
  * schedule 8
  * real    0m1,745s
    user    0m0,000s
    sys     0m0,015s
  */
 /**
  * schedule 16
  * real    0m1,918s
    user    0m0,015s
    sys     0m0,031s
  */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <time.h>
 
int sieveOfEratosthenes(int n)
{
   // Create a boolean array "prime[0..n]" and initialize
   // all entries it as true. A value in prime[i] will
   // finally be false if i is Not a prime, else true.
   int primes = 0; 
   bool *prime = (bool*) malloc((n+1)*sizeof(bool));
   int sqrt_n = sqrt(n);
 
   memset(prime, true,(n+1)*sizeof(bool));
    #pragma omp parallel for schedule(dynamic, 16)
   for (int p=2; p <= sqrt_n; p++)
   {
       // If prime[p] is not changed, then it is a prime
       //#pragma omp ordered
       if (prime[p] == true)
       {
           // Update all multiples of p
           //#pragma omp parallel for
           for (int i=p*2; i<=n; i += p)
           prime[i] = false;
        }
    }
 
    // count prime numbers
    #pragma omp parallel for reduction(+:primes)
    for (int p=2; p<=n; p++)
       if (prime[p])
         primes++;
 
    return(primes);
}
 
int main()
{

        int n = 100000000;
         printf("%d\n",sieveOfEratosthenes(n));
   return 0;
}   