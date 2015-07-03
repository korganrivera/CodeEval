/*
    CodeEval's Read More challenge.
    start:  2015.7.1.13:52
    end:    2015.7.1.14:24  Totally works but again CodeEval gave me partial credit.  I'm getting really fucking tired of CodeEval.
    end:    2015.7.2.02:24  FINALLY got it to work.  I tripped up on getting input, because I switched to fgets and forgot about it's
                            weird newline handling.  Works now.  Passed.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
    FILE *fp;
    char str[301], spaceflag=0, newlineflag=0;
    unsigned slen;
    int i, j;
    char ch;

    //  open file in text mode.
    if((fp=fopen(argv[1],"r")) == NULL){ puts("\ncan't open file."); exit(1);}

    //  read a string.
    while(NULL != fgets(str, 301, fp)){
        if(newlineflag) { putchar('\n'); newlineflag=0; }

        //  This will include a newline that fgets keeps.
        slen = strlen(str);

        //  overwrite the newline with a null terminator. reduce string length to reflect this.
        if(str[slen-1]=='\n'){ str[slen-1] = '\0'; slen--; }

        if(slen<=55) printf("%s\n", str);

        else{
            //  move backwards from 40th character until you hit a space.
            for(i=39; str[i]!=' ' && i; i--);

            //  if there are no spaces to backtrack to, then this is the stopping point.
            if(!i) j=39;

            //  else, keep moving backwards until you pass all the spaces (if more than 1).
            else for(j=i; str[j]==' '; j--);

            //  print the string up to that point.
            for(i=0; i<j+1; i++) putchar(str[i]);
            printf("... <Read More>");
            newlineflag=1;
        }
    }
    fclose(fp);
}
