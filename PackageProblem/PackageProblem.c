/*
    CodeEval's Package Problem.
    This program wasn't hard but it took me far too long,
    because I had a wicked headache all day long.
    Given the weight limit of a package, and a list of items which each have a weight and a value,
    figure out which things to put in the package so that the weight is less than or equal to the limit
    and the total value of items is as high as possible.

    "CONSTRAINTS:

    Max weight that a package can take is ≤ 100
    There might be up to 15 items you need to choose from
    Max weight and cost of an item is ≤ 100"

    So this code can only handle up to 15 items.

    @author: Korgan Rivera (korganrivera@gmail.com)
    finished: 2015.6.12.23:01
*/

#include <stdio.h>
#include <stdlib.h>

unsigned bestv[15], itemprices[15], bestprice, limit, maxweight;
float itemweights[15], bestweight;

void combinations (unsigned v[], unsigned start, unsigned n, unsigned k, unsigned maxk) {
    unsigned totalprice, i;
    float totalweight;

    if (k > maxk) {

        //  combo now sits in v[]. use it here.
        totalweight=0;
        totalprice=0;

        //  sum the weight and values of this combo.
        for (i=1; i<=maxk; i++){
            totalweight += itemweights[v[i]-1];
            totalprice += itemprices[v[i]-1];
        }

        //  if weight is inside limit and combo has the highest value found so far, save it.
        if(totalweight<=maxweight && totalprice>=bestprice){

            //  if the current best has the same price as this one, but it's heavier, don't bother saving it.
            if(totalprice==bestprice && totalweight>bestweight) return;

            bestweight = totalweight;
            bestprice = totalprice;

            //  copy v[] into bestv[].
            for(i=1; i<=maxk; i++) bestv[i] = v[i];
            limit = maxk;
        }
        return;
    }

    for (i=start; i<=n; i++){
        v[k] = i;
        combinations (v, i+1, n, k+1, maxk);
    }
}


unsigned main (unsigned argc, char *argv[]) {
    unsigned v[100], n, i;
    FILE *fp;
    unsigned numberofobjects;

    if (argc != 2) { printf ("Usage: %s <filename>\n", argv[0]); exit (1); }

    //  open file in text mode.
    if((fp=fopen(argv[1],"r")) == NULL){ puts("\ncan't open file."); exit(1);}

    //  if empty file, exit.
    if(fgetc(fp)==EOF) { puts("\nempty file."); exit(1); }
    rewind(fp);

    //  read the maxweight from file.
    while(EOF!=fscanf(fp, "%u :", &maxweight)){

        numberofobjects=0;

        //  read in sets of brackets until a newline is encountered.
        do{
            fscanf(fp, " (%*u,%f,$%u)", &itemweights[numberofobjects], &itemprices[numberofobjects]);
            numberofobjects++;
            if(fgetc(fp)==' ') continue;
            else break;
        }while(1);

        bestprice = 0;
        bestweight = maxweight+1;
        for(i=0; i<=numberofobjects; i++) combinations (v, 1, numberofobjects, 1, i);

        //  if something got saved, display it.
        if(limit){
            for (i=1; i<=limit; i++){
                printf("%u", bestv[i]);
                if(i!=limit) putchar(',');
            }
        }
        else putchar('-');
        putchar('\n');
    }
    exit (0);
}
