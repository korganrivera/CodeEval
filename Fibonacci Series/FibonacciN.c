/*  CodeEval problem: Fibonacci Series: given a number n, print F(n).
    Example: F(0) = 0; F(1) = 1; F(n) = F(n–1) + F(n–2).
    Numbers are read from a file.  This code uses 64-bit numbers
    to hold the Fibonacci numbers, so it can only go up to the
    93rd Fibonacci number.
*/
#include <stdio.h>
#include <stdlib.h>

#define MAX 93  //  64-bit number can hold F(93) at most.

int main(int argc, char *argv[]){

    unsigned long long Fn[MAX + 1];
    unsigned i, n, highest = 1;
    FILE *fp;

    Fn[0] = 0;
    Fn[1] = 1;

    //  open file in text mode.
    if ((fp=fopen(argv[1],"r")) == NULL){ puts("\ncan't open file."); exit(1); }

    //  read a number n from the file, print Fn.
    while(EOF != fscanf(fp, "%u\n", &n)){

        //  make sure number is within range.
        if (n > MAX){ printf("OUT OF RANGE: number must be <= %d", MAX); exit(1); }

        //  check if number has already been calculated.
        else if (n <= highest) printf("%llu\n", Fn[n]);

        //  otherwise, calculate it.
        else {
            for(i = highest; i < n; i++) Fn[i + 1] = Fn[i] + Fn[i-1];
            highest = n;
            printf("%llu\n", Fn[n]);
        }
    }
}
