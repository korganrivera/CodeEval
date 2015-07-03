/*
    CodeEval's Closest Pair problem.
    Given sets of coordinates from a file, spit out the distance of the two closest points.
    If distance is over 10000, spit out 'INFINITY'.

    2015.6.15.14:12 I'm reopening this because I think I thought of a smarter, faster way to do this.
                    Instead of calling sqrt every time I compare coords, I just won't.  All I need is the magnitude
                    of the size, not the exact size, to determine the shortest distance.  Only at the end do I need
                    the square root.  So just save the best magnitude and calculate the sqrt at the end.
    @author: Korgan Rivera (korganrivera@gmail.com)
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main(int argc, char *argv[]){
    FILE *fp;
    unsigned n, i, j;
    unsigned coords[10000][2];
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
        //  printf("\n\nSet has %u elements.", n);
        //    read in this set of coords.
        for(i=0; i<n; i++) fscanf(fp, "%u %u\n", &coords[i][0], &coords[i][1]);
        //for(i=0; i<n; i++) printf("\n%u %u", coords[i][0], coords[i][1]);

        bestdistance = 10000*10000;

        //  generate pairs of combos.
        for(i=0; i<n-1; i++){
            for(j=i+1; j<n; j++){

                //  calculate distance between point i and point j.
                distance = ((coords[j][0]-coords[i][0])*(coords[j][0]-coords[i][0])) + ((coords[j][1]-coords[i][1])*(coords[j][1]-coords[i][1]));
                if(distance<bestdistance) bestdistance=distance;
                // printf("\n%u %u, distance=%.4f, bestdistance=%.4f", i,j, distance, bestdistance);
            }
        }
        if(bestdistance>=10000*10000) puts("\nINFINITY");
        else printf("\n%.4f", sqrt(bestdistance));
    }
    fclose(fp);
}
