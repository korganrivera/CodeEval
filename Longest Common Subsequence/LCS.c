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
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MATCH 1
#define MISMATCH (0)
#define GAPSTART (0)
#define GAPEXT (0)

//  for debugging.
char GRIDDISPLAY = 0;
char CELLDETAIL = 0;

typedef struct _cell {
    int topnum;
    int leftnum;
    int diagnum;
    int mainnum;
    char gapflag;       //  gapflag=0 means that a gap hasn't started.
}cell;

int getfirststring(FILE *fp, char *str);

int main(int argc, char *argv[]){
    FILE *fp;
    char str1[51], str2[51], str3[51], str4[51];
    unsigned width, height, gridsize, i, j;
    cell *grid;
    char matches[50];       //  this will contain the matching letters in the end.
    unsigned matchindex=0;
    unsigned posx, posy;    //  where i'm currently focused.
    int k;
    unsigned highest;
    char newlineflag=0;
    char quitflag=0;

    //  If program isn't called with 2 arguments, explain usage.
    if(argc!=2){ printf("\nUSAGE: %s <filename>", argv[0]); exit(0); }

    //  open file in text mode.
    if((fp=fopen(argv[1],"r")) == NULL){ puts("\ncan't open file."); exit(1);}

    //  if empty file, exit.
    if(fgetc(fp)==EOF) { puts("\nempty file."); exit(1); }
    rewind(fp);

    //  read string pairs into str1 and str2.
    //while( getfirststring(fp, str1) && EOF!=fscanf(fp, "%s", str2)){
    while(1){



        //  read the first string.
        i=0;
        while(((*(str3+i)=fgetc(fp)) != ';') && (*(str3+i)!=EOF) && (*(str3+i)!='\n')){  i++; }
        if(*(str3+i)==EOF) exit(0);
        if(*(str3+i)=='\n') continue;

        //  If newline has been requested, print one.
        if(newlineflag){
            putchar('\n');
            newlineflag=0;
        }


        //  overwrite semicolon with null.
        *(str3+i)='\0';

        //  read the second string.
        fgets(str4, 51, fp);




        //  overwrite newline with null.
        str4[strlen(str4)-1]='\0';

        //  move all the characters to the left side of the string: get rid of spaces.
        //for(i=0,j=0; str3[i]; i++) if(str3[i]!=' ') str1[j++] = str3[i];
        //str1[j]='\0';
        //for(i=0,j=0; str4[i]; i++) if(str4[i]!=' ') str2[j++] = str4[i];
        //str2[j]='\0';

        //  copy strings over.
        for(i=0; str3[i]; i++) str1[i] = str3[i];
        str1[i]='\0';
        for(i=0; str4[i]; i++) str2[i] = str4[i];
        str2[i]='\0';



//        printf("\nI got strings: '%s' and '%s'\n", str1, str2);

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

                if(CELLDETAIL){
                    printf("cell[%d][%d]: topnum=%d, leftnum=%d, diagnum=%d, mainnum=%d", i,j,grid[i*(width)+j].topnum, grid[i*(width)+j].leftnum, grid[i*(width)+j].diagnum, grid[i*(width)+j].mainnum);
                    if(grid[i*(width)+j].diagnum == grid[i*(width)+j].mainnum) printf("\t***diag match.");
                    getchar();
                }


            }
        }   //  all values for grid set.


        //  print all values in the grid.
        if(GRIDDISPLAY){
            for(i=0; i<height; i++){
                for(j=0; j<width; j++){
                    printf("%4d", grid[i*(width)+j].mainnum);
                }
                putchar('\n');
            }
        }


        //  start at the bottom right cell.
        posx = height-1;
        posy = width-1;

        while(posx && posy){
//            printf("\nposx=%u, posy=%u, matchindex=%u", posx, posy, matchindex);

            //  if current mainnum came here diagonally, and letters match, save the letter.
            if( (grid[posx*(width)+posy].mainnum == grid[posx*(width)+posy].diagnum) && (*(str1+posx-1) == *(str2+posy-1))) {
                matches[matchindex++] = *(str1+posx-1);
                posx--;
                posy--;
            }

            else if(grid[posx*(width)+posy].mainnum == grid[posx*(width)+posy].diagnum) { posx--; posy--;  }
            else if(grid[posx*(width)+posy].mainnum == grid[posx*(width)+posy].topnum) posx--;
            else if(grid[posx*(width)+posy].mainnum == grid[posx*(width)+posy].leftnum) posy--;
            //else printf("fail: posx:%u posy:%u mainnum=%d diagnum=%d", posx, posy, grid[posx*(width)+posy].mainnum, grid[posx*(width)+posy].diagnum);
        }

        //  matches should now contain the most in common stuff backwards, so print it backwards.
        for(k=matchindex-1; k>=0; k--) printf("%c", matches[k]); printf("| sentence end.");
        newlineflag=1;
        //  print score, number in bottom right corner.
        //printf("\nscore=%d\n", grid[gridsize-1].mainnum);
        free(grid);
        matchindex=0;

    }// end of while
    fclose(fp);
}


int getfirststring(FILE *fp, char *str){
    unsigned i=0;
    printf("\nI read: ");
    while(*(str+i)=fgetc(fp) != ';' && *(str+i)!=EOF && *(str+i)!='\n'){ putchar(*str+i);  i++;  }
    if(*(str+i)!=EOF) return 0;
    *(str+i)='\0';
    return 1;
}
