/*  CodeEval's Minesweeper challenge.
    Given the state of a minesweeper grid in
    a text file, display that same grid with
    numbers in all the boxes to indicate the
    number of neighbouring mines. When I say
    all the boxes, that excludes those with
    mines in them.

    start:  2015.6.11.11:08
    end:    2015.6.11.12:58
    what took so long?: fscanf was fiddly,
    and I forgot to also check for newline
    in my do-while loop.
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    FILE *fp;
    unsigned m, n, sz, i, ncount, len;   //  m is rows, n is cols.
    char *str, c;

    //  If program isn't called with 2 arguments, explain usage.
    if(argc!=2){
        printf("\nUSAGE: %s <filename>", argv[0]);
        exit(0);
    }

    //  open file in text mode.
    if((fp=fopen(argv[1],"r")) == NULL){ puts("\ncan't open file."); exit(1);}

    //  if empty file, exit.
    if(fgetc(fp)==EOF) { puts("\nempty file."); exit(1); }

    rewind(fp);

    //  get dimensions of grid from file.
    while((EOF != fscanf(fp, "%u,%u;", &m, &n))){

        //  horizontal length of grid with edge is n+2.
        len = n+2;

        //  request space for str. Need space for a grid that has a 1-block edge around it. Also a null terminator.
        if((str = malloc(sz=(m+2)*len+1)) == NULL){ puts("\nmalloc failed."); exit(1); }

        //initialise str because edges need to be dead.
        for(i=0; i<sz; i++) *(str+i) = '.';

       //  get the rest of characters on the line, putting them in the grid inside the edge. This could be improved. i moves too much.
        i=n+3;
        do {
            c = fgetc (fp);
            if ((c != '\n') && (c!=EOF)){ *(str+i) = c; i++; }
            if(i%len==(n+1)) i+=2;
        } while (c != EOF && c !='\n');

        str[i] = '\0';
        fclose(fp);

        //  for each element, count its neighbours.
        for(i=n+3; i<len*(m+2)-3-n; i++){

            //  if you're in the last column, skip forward two places.
            if(i%len==n+1) i+=2;

            ncount=0;

            //  if not a mine, count the neighbouring mines.
            if(*(str+i)!='*'){
                if(*(str+i-1)=='*') ncount++;
                if(*(str+i+1)=='*') ncount++;
                if(*(str+i-len)=='*') ncount++;
                if(*(str+i+len)=='*') ncount++;
                if(*(str+i-len-1)=='*') ncount++;
                if(*(str+i-len+1)=='*') ncount++;
                if(*(str+i+len-1)=='*') ncount++;
                if(*(str+i+len+1)=='*') ncount++;

                //  change cell value to number of neighbouring mines. changing from int to character.
                *(str+i) = ncount + '0';
            }
        }

        //  print out string without the dots.
        for(i=n+3; i<len*(m+2)-3-n; i++) if(*(str+i)!='.') putchar(*(str+i));
        putchar('\n');
        free(str);
    }
}
