/*
        CodeEval's Closest Pair problem.
        Given sets of coordinates from a file, spit out the
        distance of the two closest points.  If distance is
        over 10000, spit out 'INFINITY'.

        This version uses malloc calls. Perhaps slower,
        didn't use.

        Idea for improvement, maybe a better square root function.

        @author: Korgan Rivera (korganrivera@gmail.com)
        finished: 2015.6.15.01:22
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[]){
    FILE *fp;
    unsigned n, i, j;
    unsigned *coords;               //    use this to point to 2d array.
    double distance, bestdistance;

    //  If program isn't called with 2 arguments, explain usage.
    if(argc!=2){ printf("\nUSAGE: %s <filename>", argv[0]); exit(0); }

    //  open file in text mode.
    if((fp=fopen(argv[1],"r")) == NULL){ puts("\ncan't open file."); exit(1);}

    //  if empty file, exit.
    if(fgetc(fp)==EOF) { puts("\nempty file."); exit(1); }
    rewind(fp);

    //  read n.
    while(EOF != fscanf(fp, "%u\n", &n)){
        if(!n) break;

        //  malloc space for the buffers. exit on fail.
        if((coords = malloc(sizeof(unsigned)*n*2)) == NULL){ puts("\nmalloc failed."); exit(1); }

        //  read in this set of coords.
        for(i=0; i<n; i++) fscanf(fp, "%u %u\n", coords+2*i, coords+2*i+1);

        bestdistance = 10000;

        //  generate pairs of combos, calculate distance for each, save best.
        for(i=0; i<n-1; i++){
            for(j=i+1; j<n; j++){
                distance = sqrt(((*(coords+2*j)-*(coords+2*i))*(*(coords+2*j)-*(coords+2*i))) + ((*(coords+2*j+1)-*(coords+2*i+1))*(*(coords+2*j+1)-*(coords+2*i+1))));
                if(distance<bestdistance) bestdistance=distance;
            }
        }
        if(bestdistance>=10000) puts("\nINFINITY");
        else printf("\n%.4f", bestdistance);
        free(coords);
    }
    fclose(fp);
}
