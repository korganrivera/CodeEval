/*
    CodeEval's Text Dollar problem.
    Given a list of numbers in a file, print the numbers in words.
    e.g. 1234 becomes OneThousandTwoHundredThirtyFourDollars.
    Numbers are assumed to be less than 1 billion, however my
    code can handle the maximum number an unsigned can hold.

    finished: 2015.6.16.02:11   This program only took about 20-30 mins to write.
                                Probably shouldn't be in the hard category.
    @author: Korgan Rivera (korganrivera@gmail.com)
*/

#include <stdio.h>
#include <stdlib.h>

void word(unsigned n);

int main(int argc, char *argv[]){
    FILE *fp;
    unsigned rank, number;

    //  If program isn't called with 2 arguments, explain usage.
    if(argc!=2){ printf("\nUSAGE: %s <filename>", argv[0]); exit(0); }

    //  open file in text mode.
    if((fp=fopen(argv[1],"r")) == NULL){ puts("\ncan't open file."); exit(1);}

    //  if empty file, exit.
    if(fgetc(fp)==EOF) { puts("\nempty file."); exit(1); }
    rewind(fp);

    while(EOF != fscanf(fp, "%u\n", &number)){

            //  dealing with zero dollars.
            if(!number) printf("Zero");
            else{
                //  dealing with billions.
                if(number>=1000000000){ word(rank = number/1000000000); printf("Billion"); number -= 1000000000*rank; }

                //dealing with millions.
                if(number>=1000000){ word(rank = number/1000000); printf("Million"); number -= 1000000*rank; }

                //dealing with thousands.
                if(number>=1000){ word(rank = number/1000); printf("Thousand"); number -= 1000*rank; }

                //dealing with hundreds, tens, and units.
                word(number);
            }
            puts("Dollars");
    }
    fclose(fp);
}


void word(unsigned n){
    char *zerotonineteen[20]={
        "Zero", "One", "Two", "Three", "Four", "Five", "Six", "Seven",
        "Eight", "Nine", "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen",
        "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"
    };
    char *tens[8]={
        "Twenty", "Thirty", "Forty",
        "Fifty", "Sixty", "Seventy",
        "Eighty", "Ninety"
    };

    if(!n) return;
    if(n<20){ printf("%s", zerotonineteen[n]); return; }
    if(n<100){ printf("%s", tens[n/10-2]); n-=(n/10*10); word(n); return; }
    if(n<1000){ printf("%sHundred", zerotonineteen[n/100]); n-=(n/100*100); word(n); return; }
}
