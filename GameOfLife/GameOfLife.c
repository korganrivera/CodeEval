/*  CodeEval's Game of Life challenge.
    Given an initial game state, displays game state after a given number of iterations.
    CodeEval requires this to work with a 100x100 array, but this code will work for any size of array.
    Code assumes file is formatted correctly as the specs said.
    @author: Korgan Rivera (korganrivera@gmail.com)
    started:    2015.6.8.18:53
    ended:      2015.6.8.22:02
*/

#include <stdio.h>
#include <stdlib.h>

#define ITERATIONS  10

int filesize(FILE *fp);
int linelength(FILE *fp);
int display(char *ch, unsigned size, unsigned line);
int newlinecount(FILE *fp);
void livedie(char *s1, char *s2, unsigned i, unsigned n);


int main(int argc, char *argv[]){

    FILE *fp;
    int sz, len, c;
    char *str, *str2, *tmp;

    unsigned i, j, h, ncount;

    //  If program isn't called with 2 arguments, explain usage.
    if(argc!=2){
        printf("\nUSAGE: %s <filename>", argv[0]);
        exit(0);
    }

    //  open file in text mode.
    if((fp=fopen(argv[1],"r")) == NULL){ puts("\ncan't open file."); exit(1);}

    //  get size of file.  if empty file, exit.
    if(!(sz=filesize(fp))) { puts("\nempty file."); exit(1); }
    len = linelength(fp);
    h = newlinecount(fp)+1;
    sz = len*h;

    //  malloc space for the buffer. exit on fail.
    if((str = malloc(sz)) == NULL){
        puts("\nmalloc failed.");
        exit(1);
    }

    //  malloc space for copy of the buffer. exit on fail.
    if((str2 = malloc(sz)) == NULL){
        puts("\nmalloc failed.");
        exit(1);
    }

    //  read file into buffer, discarding newlines along the way. close file.
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

            //  reset neighbour count.
            ncount=0;

            //  if on left edge, excluding corners.
            if(!(i%len) && (i/len) && (h-((i/len)+1))){
                if(*(str+i-len)=='*') ncount++;
                if(*(str+i+len)=='*') ncount++;
                if(*(str+i+1)=='*') ncount++;
                if(*(str+i+len+1)=='*') ncount++;
                if(*(str+i-len+1)=='*') ncount++;

                livedie(str, str2, i, ncount);
            }

            //  if on right edge, excluding corners.
            else if(((i%len)==(len-1)) && (i/len) && ((h-((i/len)+1)))) {
                if(*(str+i-len)=='*') ncount++;
                if(*(str+i+len)=='*') ncount++;
                if(*(str+i-len-1)=='*') ncount++;
                if(*(str+i+len-1)=='*') ncount++;
                if(*(str+i-1)=='*') ncount++;

                livedie(str, str2, i, ncount);
            }

            //  if on top edge, excluding corners.
            else if(!(i/len) && (i%len) && (i+1)%len){
                if(*(str+i+len)=='*') ncount++;
                if(*(str+i+1)=='*') ncount++;
                if(*(str+i-1)=='*') ncount++;
                if(*(str+i+len-1)=='*') ncount++;
                if(*(str+i+len+1)=='*') ncount++;

                livedie(str, str2, i, ncount);
            }

            //  if on bottom edge, excluding corners.
            else if((i/len==(h-1)) && (i%len) && ((i+1)%len)){
                if(*(str+i-len)=='*') ncount++;
                if(*(str+i+1)=='*') ncount++;
                if(*(str+i-1)=='*') ncount++;
                if(*(str+i-len-1)=='*') ncount++;
                if(*(str+i-len+1)=='*') ncount++;

                livedie(str, str2, i, ncount);
            }

            //  if on top-left corner.
            else if(!(i/len) && !(i%len)){
                if(*(str+1)=='*') ncount++;
                if(*(str+len)=='*') ncount++;
                if(*(str+len+1)=='*') ncount++;

                livedie(str, str2, i, ncount);
            }

            //  if on bottom-left corner.
            else if((i/len==(h-1)) && !(i%len)){
                if(*(str+i+1)=='*') ncount++;
                if(*(str+i-len)=='*') ncount++;
                if(*(str+i-len+1)=='*') ncount++;

                livedie(str, str2, i, ncount);
            }

            //  if on top-right corner.
            else if( !((i+1)%len) && !(i/len)){
                if(*(str+i+len)=='*') ncount++;
                if(*(str+i-1)=='*') ncount++;
                if(*(str+i+len-1)=='*') ncount++;

                livedie(str, str2, i, ncount);
            }

            //  if on bottom-right corner.
            else if((i/len==(h-1)) && !((i+1)%len)){
                if(*(str+i-len)=='*') ncount++;
                if(*(str+i-1)=='*') ncount++;
                if(*(str+i-len-1)=='*') ncount++;

                livedie(str, str2, i, ncount);
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

                livedie(str, str2, i, ncount);
            }
        }

        //  copy str2 over str.
        //for(i=0; i<sz; i++) *(str+i) = *(str2+i);

        //  swap string pointers to avoid expensive array copy.
        tmp = str;
        str = str2;
        str2 = tmp;
    }

    display(str, sz, len);
    free(str);
    free(str2);
    return 0;
}


//  given a file pointer, returns size of file in bytes.
//  Resets file pointer to start of file after use.
int filesize(FILE *fp){
    int sz;
    fseek(fp, 0L, SEEK_END);
    sz=ftell(fp);
    rewind(fp);
    return sz;
}


//  give a file pointer, returns length of first line in file, excluding the newline.
int linelength(FILE *fp){
    int len, c;

    rewind(fp);
    for(len=0; (c=fgetc(fp))!=EOF && c!='\n'; len++);
    rewind(fp);
    return len;
}


//  displays the array.
int display(char *ch, unsigned size, unsigned line){
    unsigned i;

//        for(i=0; i<size; i++){
//            putchar(*(ch+i));
//            if(!((i+1)%line) && i<(size-1)) putchar('\n');
//        }

    //  faster way.
    for(i=0; i<size; i+=line){
            fwrite (ch+i , sizeof(char), line, stdout);
            putchar('\n');
    }
}


//  counts number of newlines in the file.
int newlinecount(FILE *fp){
    int i, c, n;

    rewind(fp);
    for(i=0,n=0; (c=fgetc(fp))!=EOF; i++) if(c=='\n') n++;
    rewind(fp);
    return n;
}


//  decides whether the cell will live or die based on number of neighbours and current state.
void livedie(char *s1, char *s2, unsigned i, unsigned n){
    if(*(s1+i)=='.' && n==3) *(s2+i) = '*';                     //  if cell is dead, and it has 3 neighbours, it will live.
    else if(*(s1+i)=='*' && ((n==2) || (n==3))) *(s2+i) = '*';  //  if cell lives and has 2 or 3 neighbours, it will stay alive.
    else *(s2+i) = '.';                                         //  in any other case, cell will stay dead.
}
