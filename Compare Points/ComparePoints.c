/*
    CodeEval's Compare Points problem.
    start:  2015.7.1.13:34
    end:    2015.7.1.13:38
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    FILE *fp;
    int a,b,c,d;

    //  open file in text mode.
    if((fp=fopen(argv[1],"r")) == NULL){ puts("\ncan't open file."); exit(1);}

    //  read 4 ints.
    while(EOF != fscanf(fp, "%d %d %d %d\n", &a,&b,&c,&d)){
        if(a==c && b==d) puts("here");
        else if(a==c && b>d) puts("S");
        else if(a==c && b<d) puts("N");
        else if(a<c && b==d) puts("E");
        else if(a>c && b==d) puts("W");
        else if(a<c && b<d) puts("NE");
        else if(a>c && b<d) puts("NW");
        else if(a<c && b>d) puts("SE");
        else if(a>c && b>d) puts("SW");
    }
    fclose(fp);
}
