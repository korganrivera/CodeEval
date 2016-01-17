/*
    CodeEval problem: Fibonacci.
    Reads a number n from a file.
    Prints the Fibonacci number F(n).
    Repeats until end of file.
*/


#include <stdio.h>
#define MAX 20

int main(int argc, char *argv[]){

    unsigned short Fn[MAX + 1], n, highest = 1;
    FILE *fp = fopen(argv[1],"r");

    Fn[0] = 0;
    Fn[1] = 1;

    //  read a number n from the file, print Fn.
    while(EOF != fscanf(fp, "%hu\n", &n)){

        //  calculate F(n) if it doesn't exist.
        if(n > highest)
            for(; highest < n; highest++) Fn[highest + 1] = Fn[highest] + Fn[highest-1];

        //  print F(n).
        printf("%hu\n", Fn[n]);
    }
}
