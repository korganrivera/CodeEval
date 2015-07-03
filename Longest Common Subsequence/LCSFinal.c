/*
    This is for CodeEval's Longest Common Subsequence problem.
    This code is a branch of my DNA Alignment solution, (which TOTALLY works,but CodeEval refuses to acknowledge it.)
    To find a longest NON-CONTIGUOUS common subsequence between two words, I suspect it's the same as the DNA problem
    just with a simpler scoring system.  Give points for a match, and zero otherwise.  Then, start at the bottom right
    corner, and move either left, up or diagonal up-left, to the cell with the highest value.  This is the backtracking step.
    If at that step the corresponding letters of the word match, then add this letter to a list.  Repeat until you reach
    either column 1 or row 1.  Then print your list backwards because it contains the sequence.

    2015.6.30.01:28     I've scribbled some tests on paper and it seems to work rather well.  I'm surprised because it was just a hunch,
                        and I've been coding for about 5 hours now and didn't pass the DNA Alignment problem.  I might get some points after all.
                        Just need to add some code to print the letters.
    2015.6.30.03:17     Okay, it's after 3am, probably time to call it a night.
    2015.7.1.21:22      FINALLY.  So it turns out the strings in the input could include spaces, which wasn't any of the examples given.
                        The examples had only strings with no whitespaces.  Also, it could include numbers.  So I had to write a new function
                        to read the first string (all characters excluding a semicolon), and I used fgets for the second string.
                        The code could be greatly simplified, because most of this code is reused DNA Alignment code, with redundant stuff.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MATCH 1

typedef struct _cell {
    int topnum;
    int leftnum;
    int diagnum;
    int mainnum;
    char gapflag;       //  gapflag=0 means that a gap hasn't started.
}cell;

int main(int argc, char *argv[]){
    FILE *fp;
    cell *grid;
    char str1[51], str2[51], matches[50], newlineflag=0;
    unsigned width, height, gridsize, i, j, posx, posy;
    unsigned matchindex=0;
    int k;

    //  If program isn't called with 2 arguments, explain usage.
    if(argc!=2){ printf("\nUSAGE: %s <filename>", argv[0]); exit(0); }

    //  open file in text mode.
    if((fp=fopen(argv[1],"r")) == NULL){ puts("\ncan't open file."); exit(1);}

    //  if empty file, exit.
    if(fgetc(fp)==EOF) { puts("\nempty file."); exit(1); }
    rewind(fp);

    while(1){

        //  read the first string.
        i=0;
        while(((*(str1+i)=fgetc(fp)) != ';') && (*(str1+i)!=EOF) && (*(str1+i)!='\n')){  i++; }
        if(*(str1+i)==EOF) exit(0);
        if(*(str1+i)=='\n') continue;

        //  If newline has been requested, print one.
        if(newlineflag){
            putchar('\n');
            newlineflag=0;
        }

        *(str1+i)='\0';             //  overwrite semicolon with null.
        fgets(str2, 51, fp);        //  read the second string.
        str2[strlen(str2)-1]='\0';  //  overwrite newline with null.

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
            grid[i*(width)].mainnum = 0;
            grid[i*(width)].gapflag = 1;
        }

        //  initialise top edge.
        for(i=1; i<width; i++) {
            grid[i].mainnum = 0;
            grid[i].gapflag = 1;
        }

        //  set all the values in the grid.
        for(i=1; i<height; i++){
            for(j=1; j<width; j++){

                //  set topnum.
                if(grid[(i-1)*width+j].gapflag) grid[i*(width)+j].topnum = grid[(i-1)*width+j].mainnum;
                else grid[i*(width)+j].topnum = grid[(i-1)*width+j].mainnum;

                //  set leftnum.
                if(grid[i*width+j-1].gapflag) grid[i*(width)+j].leftnum = grid[i*width+j-1].mainnum;
                else grid[i*(width)+j].leftnum = grid[i*width+j-1].mainnum;

                //  set diagnum.
                if(*(str1+i-1) == *(str2+j-1)) grid[i*(width)+j].diagnum = grid[(i-1)*width+j-1].mainnum + MATCH;
                else grid[i*(width)+j].diagnum = grid[(i-1)*width+j-1].mainnum;

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
        }   //  all values for grid set.

        //  start at the bottom right cell.
        posx = height-1;
        posy = width-1;

        while(posx && posy){

            //  if current mainnum came here diagonally, and letters match, save the letter.
            if( (grid[posx*(width)+posy].mainnum == grid[posx*(width)+posy].diagnum) && (*(str1+posx-1) == *(str2+posy-1))) {
                matches[matchindex++] = *(str1+posx-1);
                posx--;
                posy--;
            }

            else if(grid[posx*(width)+posy].mainnum == grid[posx*(width)+posy].diagnum) { posx--; posy--;  }
            else if(grid[posx*(width)+posy].mainnum == grid[posx*(width)+posy].topnum) posx--;
            else if(grid[posx*(width)+posy].mainnum == grid[posx*(width)+posy].leftnum) posy--;
        }

        //  matches should now contain the most in common stuff backwards, so print it backwards.
        for(k=matchindex-1; k>=0; k--) printf("%c", matches[k]);
        newlineflag=1;
        free(grid);
        matchindex=0;

    }// end of while
    fclose(fp);
}

