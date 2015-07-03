/*
    Another attempt at CodeEval's DNA Alignment
    problem. This time, I'm using the alignment
    matrix approach, which should be much faster
    than the brute force method I tried before.

    2015.6.29.20:30     Took about 1-2 hours to code, because I have a headache.  Also a couple
                        of hours working it out on paper.
    2015.6.29.20:36     CodeEval failed me again.  I've no idea why.  Really tired of this shit.
    2015.6.29.22:43     I think the problem might be that I'm spitting out the numbers on the
                        bottom right of the grid, which is the equivalent of global alignment, and maybe
                        CodeEval wants the highest value in the entire grid, which is local alignment.
                        So let's try that.
    2015.6.29.22:52     NOPE!  That didn't help.  I'M OUT OF FUCKING IDEAS.
    2015.6.29.23:25     My next idea is this.  I'm considering a gap in either word to be an
                        extension of a gap in either word. Maybe that's not the case.  Maybe
                        the beginning of a gap in one word should be treated separately from
                        gaps in the other word.  So I'll try that.
    2015.6.30.00:23     So I tried a branch of this code, DBA2eTwoGapFlags.c, which was a version
                        that would subtract 8 if a gap started in either of the words, instead of
                        counting gaps in both words as part of the same gap. It gave me the same answers
                        for the test problems, as did the code before I tried this, but it also failed
                        the evaluation. I've tried both of these options with printing out the highest
                        value in the grid instead of the last value, but that fails the test questions.
                        I've tried not printing a newline after the end of output (which was the stupid
                        reason that my code was only partially accepted one time) but that made no
                        difference. I've no idea why it's no good. So yeah. I'm really out of ideas now.
                        I think it works, unless there's something in the problem I don't get.

                        I think I might be able to use this code for another problem on
                        the site, so that's next. I (probably accidentally) got partial
                        credit for one of my submissions of this code, so that's better
                        than nothing.
    2015.7.1.21:46      So I emailed the guys on the site and they said that gaps in each word should be
                        considered independent. So I should be doing the two gap thing.
                        So I'll at least switch back to that, and then who knows.
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
    char str1[401], str2[401];
    unsigned width, height, gridsize, i, j;
    cell *grid;
    int highest;

    //  If program isn't called with 2 arguments, explain usage.
    if(argc!=2){ printf("\nUSAGE: %s <filename>", argv[0]); exit(0); }

    //  open file in text mode.
    if((fp=fopen(argv[1],"r")) == NULL){ puts("\ncan't open file."); exit(1);}

    //  if empty file, exit.
    if(fgetc(fp)==EOF) { puts("\nempty file."); exit(1); }
    rewind(fp);

    //  read string pairs into str1 and str2.
    while(EOF != fscanf(fp, "%s %*c %s", str1, str2)){


//        printf("\nI read '%s' and '%s'", str1, str2);


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
            }
        }   //  end of for.

        //  print score: number in bottom right corner.
        printf("%d\n", grid[gridsize-1].mainnum);
        free(grid);

    }// end of while
    fclose(fp);
}
