//  printing combos of two numbers. testing out my recursive function.

#include <stdio.h>

void func(unsigned n, unsigned level);

int main(void){
    unsigned i,j,n=5;


    for(i=0; i<n-1; i++){
        for(j=i+1; j<n; j++){
            printf("\n%u %u", i,j);


        }


    }



}

void func(unsigned n, unsigned level){
    unsigned i;

    for(i=level; i<n; i++){
        printf("%u ", i);
        func(n,level+1);
        putchar('\n');
    }






}
