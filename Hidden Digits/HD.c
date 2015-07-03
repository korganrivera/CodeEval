/*  CodeEval's Hidden Digits challenge.
    @author: Korgan Rivera (korganrivera@gmail.com)
    started:    2015.7.1.12:49
    ended:      2015.7.1.13:02
    improved:   2015.7.1.13:08  Replaced all printfs with putchar, and one with puts: less expensive.
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[]){
    char ch;
    FILE *fp;
    char digitflag=0;

    //  If program isn't called with 2 arguments, explain usage.
    if(argc!=2){ printf("\nUSAGE: %s <filename>", argv[0]); exit(0); }

    //  open file.
    if((fp=fopen(argv[1],"r")) == NULL){ puts("\ncan't open file."); exit(1);}

    //  read character from the file, do the thing.
    while(EOF!=fscanf(fp, "%c", &ch)){
        if(isdigit(ch)){  putchar(ch);  digitflag=1; }
        else if(ch=='a'){ putchar('0'); digitflag=1; }
        else if(ch=='b'){ putchar('1'); digitflag=1; }
        else if(ch=='c'){ putchar('2'); digitflag=1; }
        else if(ch=='d'){ putchar('3'); digitflag=1; }
        else if(ch=='e'){ putchar('4'); digitflag=1; }
        else if(ch=='f'){ putchar('5'); digitflag=1; }
        else if(ch=='g'){ putchar('6'); digitflag=1; }
        else if(ch=='h'){ putchar('7'); digitflag=1; }
        else if(ch=='i'){ putchar('8'); digitflag=1; }
        else if(ch=='j'){ putchar('9'); digitflag=1; }
        else if(ch=='\n'){
            if(!digitflag) puts("NONE");
            else putchar('\n');
            digitflag=0;
        }
    }
    fclose(fp);
}
