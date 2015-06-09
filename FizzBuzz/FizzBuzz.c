/*  CodeEval's Fizz Buzz challenge.
    @author: Korgan Rivera (korganrivera@gmail.com)
    started:    2015.6.8.17:32
    ended:      2015.6.8.18:21
    what took so long?: couldn't remember the best way to deal with EOFs.
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

    FILE *fp;
    int x, y, n, i;

    //  If program isn't called with 2 arguments, explain usage.
    if(argc!=2){
        printf("\nUSAGE: %s <filename>", argv[0]);
        exit(0);
    }

    //  open file.
    if((fp=fopen(argv[1],"r")) == NULL){ puts("\ncan't open file."); exit(1);}

    //  read 3 ints from file, do the thing. repeat until EOF.
    while(fscanf(fp, "%d %d %d \n", &x, &y, &n) == 3) {
        for(i=1; i<=n; i++){
            if(!(i%x) || !(i%y)){
                if(!(i%x)) putchar('F');
                if(!(i%y)) putchar('B');
            }
            else  printf("%d", i);
            if(i!=n) putchar(' ');
        }
        puts("");
    }
    fclose(fp);
}
