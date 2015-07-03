//  generate random strings of GATC so I can test my program.

#define LINES 100            //  number of lines to print.
#define MAXLENGTH 13        //  maximum length of DNA string.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void){
    unsigned i,j;
    unsigned length1, length2;
    unsigned r;

    srand(time(NULL));      //  initialize random seed.

    for(i=0; i<LINES; i++){
        //length1 = rand()%MAXLENGTH+1;
        length2 = rand()%MAXLENGTH+1;
        length1=MAXLENGTH;


        //  print first string.
        for(j=0; j<length1; j++) {
            r = rand()%100+1;
            if(r<25) putchar('C');
            else if(r<50) putchar('A');
            else if(r<75) putchar('T');
            else putchar('G');
        }

        printf(" | ");

        //  print second string.
        for(j=0; j<length2; j++) {
            r = rand()%100+1;
            if(r<25) putchar('C');
            else if(r<50) putchar('A');
            else if(r<75) putchar('T');
            else putchar('G');
        }

        putchar('\n');
    }





}
