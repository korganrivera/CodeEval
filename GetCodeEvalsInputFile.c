//  file read test thing for STRING | STRING \n

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    FILE *fp;
    char str1[400], str2[400];
    char ch;

    //  If program isn't called with 2 arguments, explain usage.
    if(argc!=2){
        printf("\nUSAGE: %s <filename>", argv[0]);
        exit(0);
    }

    //  open file in text mode.
    if((fp=fopen(argv[1],"r")) == NULL){ puts("\ncan't open file."); exit(1);}

    //  if empty file, exit.
    if(fgetc(fp)==EOF) { puts("\nempty file."); exit(1); }

    //  rewind file pointer.
    rewind(fp);

    //  display all characters from input.
    while(EOF != (ch=fgetc(fp))) putchar(ch);
    fclose(fp);
}
