/*
    Another attempt at CodeEval's DNA Alignment problem.
    This time, I'm using the alignment matrix
    approach, which should be much faster than
    the brute force method I tried before.

    Took about 1-2 hours to code, because I have a headache.  Also a couple of hours working it out on paper.
    2015.6.29.20:36     CodeEval failed me again.  I've no idea why.  Really tired of this shit.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MATCH 3
#define MISMATCH (-3)
#define GAPSTART (-8)
#define GAPEXT (-1)

typedef struct _cell {
    int topnum;
    int leftnum;
    int diagnum;
    int mainnum;
    char gapflag;       //  gapflag=0 means that a gap hasn't started.
}cell;


int main(int argc, char *argv[]){
    FILE *fp;
    char str1[400], str2[400];
    unsigned width, height, gridsize, i, j;
    cell *grid;

    unsigned answers[1000], index=0;    //  this is used to avoid printing a newline at end of my answers.

    //  If program isn't called with 2 arguments, explain usage.
    if(argc!=2){ printf("\nUSAGE: %s <filename>", argv[0]); exit(0); }

    //  open file in text mode.
    if((fp=fopen(argv[1],"r")) == NULL){ puts("\ncan't open file."); exit(1);}

    //  if empty file, exit.
    if(fgetc(fp)==EOF) { puts("\nempty file."); exit(1); }
    rewind(fp);

    //  read string pairs into str1 and str2.
    while(EOF != fscanf(fp, "%s %*c %s", str1, str2)){

        //  get string lengths.
        height = strlen(str1)+1;
        width = strlen(str2)+1;
        gridsize = height*width;

        //  malloc space for the grid.
        if((grid = malloc(gridsize*sizeof(cell))) == NULL){ puts("\nmalloc failed."); exit(1); }

        //  initialise top left cell.
        grid[0].mainnum=0;

        //  initialise left edge.
        for(i=1; i<height; i++) {
            grid[i*(width)].mainnum = GAPSTART+(i-1)*GAPEXT;
            grid[i*(width)].gapflag = 1;
        }

        //  initialise top edge.
        for(i=1; i<width; i++) {
            grid[i].mainnum = GAPSTART+(i-1)*GAPEXT;
            grid[i].gapflag = 1;
        }

        //  set all the values in the grid.
        for(i=1; i<height; i++){
            for(j=1; j<width; j++){

                //  set topnum.
                if(grid[(i-1)*width+j].gapflag) grid[i*(width)+j].topnum = grid[(i-1)*width+j].mainnum + GAPEXT;
                else grid[i*(width)+j].topnum = grid[(i-1)*width+j].mainnum + GAPSTART;

                //  set leftnum.
                if(grid[i*width+j-1].gapflag) grid[i*(width)+j].leftnum = grid[i*width+j-1].mainnum + GAPEXT;
                else grid[i*(width)+j].leftnum = grid[i*width+j-1].mainnum + GAPSTART;

                //  set diagnum.
                if(*(str1+i-1) == *(str2+j-1)) grid[i*(width)+j].diagnum = grid[(i-1)*width+j-1].mainnum + MATCH;
                else grid[i*(width)+j].diagnum = grid[(i-1)*width+j-1].mainnum + MISMATCH;

                //  set mainnum. if topnum is biggest, use that. set gapflag.
                if(grid[i*(width)+j].topnum >= grid[i*(width)+j].diagnum && grid[i*(width)+j].topnum >= grid[i*(width)+j].leftnum) {
                    grid[i*(width)+j].mainnum = grid[i*(width)+j].topnum;
                    grid[i*(width)+j].gapflag = 1;
                }

                //  else if leftnum is biggest, use that. set gapflag.
                else if (grid[i*(width)+j].leftnum >= grid[i*(width)+j].diagnum && grid[i*(width)+j].leftnum >= grid[i*(width)+j].topnum) {
                    grid[i*(width)+j].mainnum = grid[i*(width)+j].leftnum;
                       grid[i*(width)+j].gapflag = 1;
                }

                //  otherwise use diagnum, and reset gapflag.
                else {
                    grid[i*(width)+j].mainnum = grid[i*(width)+j].diagnum;
                    grid[i*(width)+j].gapflag = 0;
                }

                printf("\ncell [%u][%u]:", i, j);
                printf("\ntopnum=%d\t leftnum=%d, diagnum=%d", grid[i*(width)+j].topnum, grid[i*(width)+j].leftnum, grid[i*(width)+j].diagnum);
                printf("\nmainnum =%d", grid[i*(width)+j].mainnum);
                getchar();

            }
        }   //  end of for.


        //  print the grid to check.
        for(i=0; i<height; i++){
            for(j=0; j<width; j++){
                printf("%d\t", grid[i*width+j].mainnum);
            }
            putchar('\n');
        }

        //  print score, number in bottom right corner.
        printf("\nanswer: %d\n", grid[gridsize-1].mainnum);
        //answers[index++]=grid[gridsize-1].mainnum;





        free(grid);

    }// end of while

    //  in case codeeval is balking at an extra newline at the end of my output, this makes sure it doesn't print.
//    for(i=0; i<index; i++) {
//        printf("%d", answers[i]);
//        if(i!=index-1) putchar('\n');
//    }

    fclose(fp);
}
