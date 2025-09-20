/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#define N 50
unsigned long mem[N+1];
unsigned long fibonacci3(int n) {

   if (n == 1) return 1;
   if (n == 2) return 2;

   unsigned long n_1 = 2;
   unsigned long n_2 = 1;

   unsigned long result = 0;
   for (int i=3; i<=n; i++) {

      result = n_1 + n_2;
      
      n_2 = n_1;
      n_1 = result;
      
   }

   return result;
}

unsigned long fibonacci2(int n) {

    if (mem[n] != 0 ) return mem[n];
    unsigned long result = 0;
    
    if (n == 1) {
        result = 1;
    }
    else if (n == 2) {
        result = 2;
    }
    else {
        result = fibonacci2(n-1) + fibonacci2(n-2);    
    }
    
    mem[n] = result;
    return result; 
}

unsigned long fibonacci(int n) {

    if (n == 1) return 1;
    if (n == 2) return 2;
    
    
    return fibonacci(n-1) + fibonacci(n-2);
}

int main()
{
    printf("Hello World\n");
    unsigned long fib_n;
//    fib_n = fibonacci(N);
//    printf ("N: %d fib_n: %lu\n", N, fib_n);
    fib_n = fibonacci2(N);
    printf ("N: %d fib_n: %lu\n", N, fib_n);
    fib_n = fibonacci3(N);
    printf ("N: %d fib_n: %lu\n", N, fib_n);
    return 0;
}
