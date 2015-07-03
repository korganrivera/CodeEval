/*  Overlapping Rectangles.
    Check to see if each corner is within
    the coords of other rectangle. If so,
    they overlap.

    finished: 2015.6.16.21:13
    @author: Korgan Rivera (korganrivera@gmail.com)
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    FILE *fp;
    int Ax1, Ay1, Ax2, Ay2, Bx1, By1, Bx2, By2;

    //  If program isn't called with 2 arguments, explain usage.
    if(argc!=2){ printf("\nUSAGE: %s <filename>", argv[0]); exit(0); }

    //  open file in text mode.
    if((fp=fopen(argv[1],"r")) == NULL){ puts("\ncan't open file."); exit(1);}

    //  if empty file, exit.
    if(fgetc(fp)==EOF) { puts("\nempty file."); exit(1); }
    rewind(fp);

    //  read 8 numbers from file.
    while(EOF != fscanf(fp, "%d,%d,%d,%d,%d,%d,%d,%d\n", &Ax1,&Ay1,&Ax2,&Ay2,&Bx1,&By1,&Bx2,&By2)){

        //  if first rectangle is to the left or right of second rectangle, then they don't overlap.
        //  if first rectangle is above or below the second rectangle, then they don't overlap.
        if( ((Ax1>Bx1 && Ax1>Bx2 && Ax2>Bx1 && Ax2>Bx2) || (Ax1<Bx1 && Ax1<Bx2 && Ax2<Bx1 && Ax2<Bx2)) || ((Ay1>By1 && Ay1>By2 && Ay2>By1 && Ay2>By2) || (Ay1<By1 && Ay1<By2 && Ay2<By1 && Ay2<By2))) puts("False");
        else puts("True");
    }
    fclose(fp);
}
