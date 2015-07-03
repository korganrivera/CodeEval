/*  CodeEval's Happy Numbers problem.
    Sum the squares of the digits of each given number in a file.
    If the outcome is 1, print '1'. Else, repeat the process until
    it happens. If you get a number you've already had, that means
    the loop is infinite, so just quit and print zero. chains that
    end in 1 are called happy numbers.

    finished: 2015.6.16.2015    This program only took about 30 mins.

    @author: Korgan Rivera (korganrivera@gmail.com)
*/
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    FILE *fp;
    unsigned number, i, j;
    unsigned record[100000];
    unsigned thousands, hundreds, tens, units;


    //  If program isn't called with 2 arguments, explain usage.
    if(argc!=2){ printf("\nUSAGE: %s <filename>", argv[0]); exit(0); }

    //  open file in text mode.
    if((fp=fopen(argv[1],"r")) == NULL){ puts("\ncan't open file."); exit(1);}

    //  if empty file, exit.
    if(fgetc(fp)==EOF) { puts("\nempty file."); exit(1); }
    rewind(fp);

    while(EOF != fscanf(fp, "%u\n", &number)){

    //    printf("\noriginal number: %u", number);
        i=0;
        //  record the first number
        record[i++] = number;

        do{
            //  initialise denominations.
            thousands = hundreds = tens = units = 0;

            //  split number into its denominations.
            if(number>=1000) { thousands = number/1000; number -= number/1000*1000; }
            if(number>=100)  { hundreds  = number/100;  number -= number/100*100;   }
            if(number>=10)   { tens      = number/10;   number -= number/10*10;     }
            units = number;

            //  make number = sum of square of digits.
            number = thousands*thousands + hundreds*hundreds + tens*tens + units*units;

            if(number==1) puts("1");
            else{
                //  search records for existence of this number.  if already here, print 0 and exit loop: not a happy number.
                //  else put number in record, and repeat.
                for(j=0; j<i; j++) if(record[j]==number) { puts("0"); break; }
                if(j<i) break;
                else record[i++] = number;
            }

        }while(number!=1);
    }
    fclose(fp);
}
