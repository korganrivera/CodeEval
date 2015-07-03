/*
    Spiral Printing problem for CodeEval.
    @author: Korgan Rivera (korganrivera@gmail.com)
    finished: 2015.6.14.11:15

    Okay, now it works with strings.
*/

#include <stdio.h>
#include <stdlib.h>

#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3

int main(int argc, char *argv[]){
    FILE *fp;
    unsigned rows, cols, sz, i;
    char *str, c;
    char grid[100][100][10];
    unsigned direction;
    int leftlimit, rightlimit, toplimit, bottomlimit;
    unsigned count;

    //  If program isn't called with 2 arguments, explain usage.
    if(argc!=2){ printf("\nUSAGE: %s <filename>", argv[0]); exit(0); }

    //  open file in text mode.
    if((fp=fopen(argv[1],"r")) == NULL){ puts("\ncan't open file."); exit(1);}

    //  if empty file, exit.
    if(fgetc(fp)==EOF) { puts("\nempty file."); exit(1); }
    rewind(fp);

    //  get dimensions of grid from file.
    while((EOF != fscanf(fp, "%u;%u;", &rows, &cols))){

        sz = rows*cols;

        //  read numbers into string, ignoring whitespace. Read numbers as characters.
        i=0; do { fscanf(fp, " %s ", &grid[i/cols][i%cols]); i++; } while (i<sz);

        //  initialise limits.
        leftlimit = 0;
        rightlimit = cols-1;
        bottomlimit = rows-1;
        toplimit = 1;

        //  start at origin (0,0) and move left as far as possible.
        direction = RIGHT;
        i = count = 0;
        do{
            //  print the number.
            printf("%s ", grid[i/cols][i%cols]);
            count++;

            //  move in the correct direction.
            if(direction==RIGHT) i++;
            else if(direction==DOWN)  i+=cols;
            else if(direction==LEFT)  i--;
            else if(direction==UP)    i-=cols;

            //  check for limit, and if so change direction.
            if(i%cols==rightlimit && direction==RIGHT) { direction=DOWN; rightlimit--; }
            else if(i/cols==bottomlimit && direction==DOWN) { direction=LEFT; bottomlimit--; }
            else if(i%cols==leftlimit && direction==LEFT) { direction=UP; leftlimit++; }
            else if(i/cols==toplimit && direction==UP) { direction=RIGHT; toplimit++; }

        }while(count<sz);
        putchar('\n');
//        free(str);    //  for some reason, code eval didn't like this function this time.  No idea.
    }
    fclose(fp);
}
