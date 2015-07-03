/*
    Need to add words from pernute() to some list instead of printing them.
    when i get back to main, sort the list and print it. then this program
    is done.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>




/* Function to swap values at two pointers */
void swap (char *x, char *y)
{
     char temp;
     temp = *x;
     *x = *y;
     *y = temp;
}

/* Function to print permutations of string
    This function takes three parameters:
    1. String
    2. Starting index of the string
    3. Ending index of the string. */
void permute(char *a, int i, int n)
{
    int j;
    if (i == n)
      printf("%s\n", a);
    else
    {
          for (j = i; j <= n; j++)
         {
             swap((a+i), (a+j));
             permute(a, i+1, n);
             swap((a+i), (a+j)); //backtrack
         }
    }
}

/* Driver program to test above functions */
int main(int argc, char *argv[]){
    FILE *fp;
    char a[500];

    //  If program isn't called with 2 arguments, explain usage.
    if(argc!=2){ printf("\nUSAGE: %s <filename>", argv[0]); exit(0); }

    //  open file in text mode.
    if((fp=fopen(argv[1],"r")) == NULL){ puts("\ncan't open file."); exit(1);}

    //  if empty file, exit.
    if(fgetc(fp)==EOF) { puts("\nempty file."); exit(1); }
    rewind(fp);

    //  read str.
    while(EOF != fscanf(fp, "%s", a)){

            permute(a, 0, strlen(a)-1);



    }













}
