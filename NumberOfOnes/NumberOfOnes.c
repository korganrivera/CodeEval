/*
    CodeEval's Number Of Ones problem.
    started:    2015.6.16.14:23
    finished:   2015.6.16.14:26 lol
*/


#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    FILE *fp;
    unsigned number, count;

    //  If program isn't called with 2 arguments, explain usage.
    if(argc!=2){ printf("\nUSAGE: %s <filename>", argv[0]); exit(0); }

    //  open file in text mode.
    if((fp=fopen(argv[1],"r")) == NULL){ puts("\ncan't open file."); exit(1);}

    //  if empty file, exit.
    if(fgetc(fp)==EOF) { puts("\nempty file."); exit(1); }
    rewind(fp);

    while(EOF != fscanf(fp, "%u\n", &number)){

        count=0;
        while(number){
            if(number&1) count++;
            number = number>>1;
        }
        printf("%u\n", count);
    }
    fclose(fp);
}
