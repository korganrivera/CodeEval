/*
    CodeEval's Rollercoaster problem.
    finished: 2015.6.16.19:22
    @author: Korgan Rivera (korganrivera@gmail.com)
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[]){
    FILE *fp;
    char str[1001], c;
    unsigned i, j, toggle;

    //  If program isn't called with 2 arguments, explain usage.
    if(argc!=2){ printf("\nUSAGE: %s <filename>", argv[0]); exit(0); }

    //  open file in text mode.
    if((fp=fopen(argv[1],"r")) == NULL){ puts("\ncan't open file."); exit(1);}

    //  if empty file, exit.
    if(fgetc(fp)==EOF) { puts("\nempty file."); exit(1); }
    rewind(fp);

    do {
        i=0;
        toggle=1;
        while (((c=fgetc(fp)) != '\n') && (c!=EOF)){ str[i] = c; i++; }
        str[i] = '\0';

        //  move to first letter in sentence, in case first is punctuation.
        for(j=0; j<i; j++) if(isalpha(str[j])) break;

        for(; j<i; j++){
            if(isalpha(str[j])){
                if(toggle){ str[j] = toupper(str[j]); toggle=0; }
                else{ str[j] = tolower(str[j]); toggle=1; }
            }
        }

        printf("%s\n", str);
    }while(c != EOF);
    fclose(fp);
}
