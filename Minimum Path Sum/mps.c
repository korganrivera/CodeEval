/*
    CodeEval's Minimum Path Sum problem. Finding the least cost path from top-left to bottom-right of a given matrix.
    start:  2015.7.2.15:13
    end:    2015 7.2.15:54  Sweet! Only took 41 minutes!
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    FILE *fp;
    unsigned width, gridsize, i, j;
    char newlineflag=0;
    int *grid;

    //  If program isn't called with 2 arguments, explain usage.
    if(argc!=2){ printf("\nUSAGE: %s <filename>", argv[0]); exit(0); }

    //  open file in text mode.
    if((fp=fopen(argv[1],"r")) == NULL){ puts("\ncan't open file."); exit(1);}

    //  if empty file, exit.
    if(fgetc(fp)==EOF) { puts("\nempty file."); exit(1); }
    rewind(fp);

    //  read size of matrix first.
    while(EOF != fscanf(fp, "%u ", &width)){

        //  print newline if one was requested.
        if(newlineflag){ putchar('\n'); newlineflag=0;}

        //  malloc space for the grid.
        if((grid = malloc((gridsize=width*width)*sizeof(int))) == NULL){ puts("\nmalloc failed."); exit(1); }

        //  read in the array, avoiding the commas and the newline.
        for(i=0; i<width; i++){
            for(j=0; j<width-1; j++) fscanf(fp, "%d,", &(*(grid+width*i+j)));
            fscanf(fp, "%d ", &(*(grid+width*i+j)));
        }

        //  initialise left and top edge.
        for(i=1; i<width; i++){
            *(grid+i*width) += *(grid+(i-1)*width);
            *(grid+i) += *(grid+i-1);
        }

        //  set all the values in the grid.
        for(i=1; i<width; i++){
            for(j=1; j<width; j++){

                //  add cost to the lowest-valued adjacent cell.
                if(*(grid+i*width+j-1) <= *(grid+(i-1)*width+j)) *(grid+i*width+j) += *(grid+i*width+j-1);
                else *(grid+i*width+j) += *(grid+(i-1)*width+j);
            }
        }

        //  print score: number in bottom right corner.
        printf("%d", grid[gridsize-1]);
        newlineflag=1;
        free(grid);

    }// end of while
    fclose(fp);
}
