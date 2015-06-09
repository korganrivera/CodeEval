/*  CodeEval's Game of Life challenge.
    Given an initial game state, displays game state after a given number of iterations.
    CodeEval requires this to work with a 100x100 array, but this code will work for any size of array.
    Code assumes file is formatted correctly as the specs said.
    @author: Korgan Rivera (korganrivera@gmail.com)
    started:    2015.6.8.18:53
    ended:      2015.6.8.22:02
    fiddled:    2015.6.9.01:08  Made some functions inline, made stdout writes much faster.  Decreased code's line count by 83 lines.
                CodeEval still doesn't accept my code even though it totally works.  Oh well.
    done:       2015.6.9.11:47  Okay solved it.  I had ncount=0 inside my for loop, and so it wasn't initialising until AFTER the first loop
                                and so it was getting the first element wrong.  Stupid mistake and frustrating to find. :)
    really done:         12:14  So it turns out CodeEval's problem wasn't stated correctly.  Their sample problem had a newline on the end of every line
                                except the last line.  However, their test problem had a newline on the last line too.  My program relies on a newline count
                                so I wasted 3 hours looking for a bug that doesn't exist.  INPUT FILE MUST END WITH A NEWLINE OR CRASH!
*/

#include <stdio.h>
#include <stdlib.h>

#define ITERATIONS  10

int display(char *ch, unsigned size, unsigned line);
void livedie(char *s1, char *s2, unsigned i, unsigned n);

int main(int argc, char *argv[]){
    FILE *fp;
    int sz, len, c, i;
    char *str, *str2, *tmp;
    unsigned j, h, ncount;

    //  If program isn't called with 2 arguments, explain usage.
    if(argc!=2){
        printf("\nUSAGE: %s <filename>", argv[0]);
        exit(0);
    }

    //  open file in text mode.
    if((fp=fopen(argv[1],"r")) == NULL){ puts("\ncan't open file."); exit(1);}

    //  if empty file, exit.
    if(fgetc(fp)==EOF) { puts("\nempty file."); exit(1); }

    //  calculate line length.
    for(len=0, rewind(fp); (c=fgetc(fp))!=EOF && c!='\n'; len++);

    //  calculate height of grid.
    for(i=0,h=0,rewind(fp); (c=fgetc(fp))!=EOF; i++) if(c=='\n') h++;

    //  malloc space for the buffers. exit on fail.
    if((str = malloc(sz=len*h)) == NULL){ puts("\nmalloc failed."); exit(1); }
    if((str2 = malloc(sz)) == NULL){ puts("\nmalloc failed."); exit(1); }

    //  read file into buffer, discarding newlines along the way. close file.
    //  consider replacing with fread and a newline skipper, or fscanf.
    i=0;
    rewind(fp);
    do {
      c = fgetc (fp);
      if ((c != '\n') && (c!=EOF)){ *(str+i) = c; i++; }
    } while (c != EOF);
    fclose(fp);

    //  run game of life sequence for required iterations.
    for(j=0; j<ITERATIONS; j++){
        for(i=0; i<sz; i++){

            ncount=0;

            //  if on left edge, excluding corners.
            if(!(i%len) && (i/len) && (h-((i/len)+1))){
                if(*(str+i-len)=='*') ncount++;
                if(*(str+i+len)=='*') ncount++;
                if(*(str+i+1)=='*') ncount++;
                if(*(str+i+len+1)=='*') ncount++;
                if(*(str+i-len+1)=='*') ncount++;
            }

            //  if on right edge, excluding corners.
            else if(((i%len)==(len-1)) && (i/len) && ((h-((i/len)+1)))) {
                if(*(str+i-len)=='*') ncount++;
                if(*(str+i+len)=='*') ncount++;
                if(*(str+i-len-1)=='*') ncount++;
                if(*(str+i+len-1)=='*') ncount++;
                if(*(str+i-1)=='*') ncount++;
            }

            //  if on top edge, excluding corners.
            else if(!(i/len) && (i%len) && (i+1)%len){
                if(*(str+i+len)=='*') ncount++;
                if(*(str+i+1)=='*') ncount++;
                if(*(str+i-1)=='*') ncount++;
                if(*(str+i+len-1)=='*') ncount++;
                if(*(str+i+len+1)=='*') ncount++;
            }

            //  if on bottom edge, excluding corners.
            else if((i/len==(h-1)) && (i%len) && ((i+1)%len)){
                if(*(str+i-len)=='*') ncount++;
                if(*(str+i+1)=='*') ncount++;
                if(*(str+i-1)=='*') ncount++;
                if(*(str+i-len-1)=='*') ncount++;
                if(*(str+i-len+1)=='*') ncount++;
            }

            //  if on top-left corner.
            else if(!(i/len) && !(i%len)){
                if(*(str+1)=='*') ncount++;
                if(*(str+len)=='*') ncount++;
                if(*(str+len+1)=='*') ncount++;
            }

            //  if on bottom-left corner.
            else if((i/len==(h-1)) && !(i%len)){
                if(*(str+i+1)=='*') ncount++;
                if(*(str+i-len)=='*') ncount++;
                if(*(str+i-len+1)=='*') ncount++;
            }

            //  if on top-right corner.
            else if( !((i+1)%len) && !(i/len)){
                if(*(str+i+len)=='*') ncount++;
                if(*(str+i-1)=='*') ncount++;
                if(*(str+i+len-1)=='*') ncount++;
            }

            //  if on bottom-right corner.
            else if((i/len==(h-1)) && !((i+1)%len)){
                if(*(str+i-len)=='*') ncount++;
                if(*(str+i-1)=='*') ncount++;
                if(*(str+i-len-1)=='*') ncount++;
            }

            else{
                if(*(str+i-1)=='*') ncount++;
                if(*(str+i+1)=='*') ncount++;
                if(*(str+i-len)=='*') ncount++;
                if(*(str+i+len)=='*') ncount++;
                if(*(str+i-len-1)=='*') ncount++;
                if(*(str+i-len+1)=='*') ncount++;
                if(*(str+i+len-1)=='*') ncount++;
                if(*(str+i+len+1)=='*') ncount++;
            }

            livedie(str, str2, i, ncount);      //  apply the rules to current element.
        }

        tmp = str; str = str2; str2 = tmp;      //  swap string pointers to avoid expensive array copy.
    }

    for(i=0; i<sz; i+=len){ fwrite (str+i , sizeof(char), len, stdout); if((h-1) != (i/len)) putchar('\n'); }
    free(str); free(str2);
}

//  displays the array.
int display(char *ch, unsigned size, unsigned line){
    unsigned i;
    for(i=0; i<size; i+=line){ fwrite (ch+i , sizeof(char), line, stdout); if((size/line-1) != (i/line)) putchar('\n'); }
}

//  decides whether the cell will live or die based on number of neighbours and current state.
void livedie(char *s1, char *s2, unsigned i, unsigned n){
    if(*(s1+i)=='.' && n==3) *(s2+i) = '*';                     //  if cell is dead, and it has 3 neighbours, it will live.
    else if(*(s1+i)=='*' && ((n==2) || (n==3))) *(s2+i) = '*';  //  if cell lives and has 2 or 3 neighbours, it will stay alive.
    else *(s2+i) = '.';                                         //  in any other case, cell will stay dead.
}
