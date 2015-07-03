//  display numbers given in words, for CodeEval's TextDollar problem.

#include <stdio.h>

void word(unsigned n);

int main(void){
    unsigned rank, number=1234567890;

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
