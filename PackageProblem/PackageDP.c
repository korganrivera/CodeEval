/*
    CodeEval's Package Problem.
    This time I'm solving using the dynamic programming approach.
    Given the weight limit of a package, and a list of items which each have a weight and a value,
    figure out which things to put in the package so that the weight is less than or equal to the limit
    and the total value of items is as high as possible.

    THIS CODE DOESN'T WORK!  The reason is that the weights are floats, not ints.
    I tried multiplying them by 100 to use them as unsigneds, BUT that introduced retarded rounding errors,
    which made it unworkable.  So that's the end of that.
    One solution might be to read the floats as strings, and do the conversion by hand, but
    I don't want to do that right now.

    "CONSTRAINTS:

    Max weight that a package can take is = 100
    There might be up to 15 items you need to choose from
    Max weight and cost of an item is = 100"

    So this code can only handle up to 15 items.

    @author: Korgan Rivera (korganrivera@gmail.com)
    finished: 2015.6.12.23:01
*/

#include <stdio.h>
#include <stdlib.h>

#define MAXWEIGHT (100*100)
#define MAXITEMS 15

unsigned main (unsigned argc, char *argv[]) {
    unsigned i, j;
    unsigned numberofobjects;
    unsigned itemprices[MAXITEMS], maxweight;
    double itemweights[MAXITEMS];
    double pickvalue;
    double array[MAXITEMS][MAXWEIGHT+1];
    FILE *fp;
    unsigned u_itemweights[MAXITEMS];

    if (argc != 2) { printf ("Usage: %s <filename>\n", argv[0]); exit (1); }

    //  open file in text mode.
    if((fp=fopen(argv[1],"r")) == NULL){ puts("\ncan't open file."); exit(1);}

    //  if empty file, exit.
    if(fgetc(fp)==EOF) { puts("\nempty file."); exit(1); }
    rewind(fp);

    //  set first column to zeroes.
    for(i=0; i<MAXITEMS; i++) array[i][0] = 0;

    //  read the maxweight from file.
    while(EOF!=fscanf(fp, "%u :", &maxweight)){

        printf("\nI read maxweight=%u\n", maxweight);

        //  read in sets of brackets until a newline is encountered.
        numberofobjects=0;
        do{
            fscanf(fp, " (%*u,%lf,$%u)", &itemweights[numberofobjects], &itemprices[numberofobjects]);
            numberofobjects++;
            if(fgetc(fp)==' ') continue;
            else break;
        }while(1);

        printf("\nthere are %u objects", numberofobjects);

        //  convert itemweights to unsigneds.
        for(i=0; i<numberofobjects; i++) u_itemweights[i] = itemweights[i] * 100.0 + 0.1;

        maxweight *= 100;
        printf("\nnew max weight is %u\n", maxweight);


        //  set first row.
        for(i=1; i<=maxweight; i++) {
            if(u_itemweights[0] <= i) array[0][i] = itemprices[0];
            else array[0][i] = 0;
        }

        //  the rest.
        for(i=1; i<numberofobjects; i++){
            for(j=1; j<=maxweight; j++){
                if(u_itemweights[i] <= j) {
                    pickvalue = itemprices[i] + array[i-1][j-u_itemweights[i]];
                    if(pickvalue > array[i-1][j]) array[i][j] = pickvalue;
                    else array[i][j] = array[i-1][j];
                }
                else array[i][j] = array[i-1][j];
            }
        }

        //  display solution.
        //if(array[numberofobjects-1][maxweight]>0){

            //  figure the backtrack.
            i = numberofobjects-1;
            j = maxweight;

            while(i>=0 && j>0){
                if(!array[i][j]) break;


                if(array[i][j] == array[i-1][j]) i--;
                else{
                    printf("%u,", i+1);
                    j -= u_itemweights[i];
                    i--;
                }
            }
        //}
        //else putchar('-');
        putchar('\n');
        }
}
