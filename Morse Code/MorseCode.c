/*
    CodeEval's Morse Code problem: translate strings
    of morse code from a file. Method: follow nodes
    on a tree.  If file begins with an empty line,
    it should crash.
    Could speed it up by reading more than one char
    at a time, but meh.
*/

#include <stdio.h>

struct _node {
    char ch;
    struct _node* l;
    struct _node* r;
};

int main(int argc, char *argv[]){

    struct _node morse[39], *scout;
    FILE *fp = fopen(argv[1], "r");
    char ch, f = 0;

    morse[0].ch  = 'A'; morse[0].l  = &morse[22];   morse[0].r  = &morse[17];
    morse[1].ch  = 'B'; morse[1].l  = NULL;	        morse[1].r  = &morse[31];
    morse[2].ch  = 'C'; morse[2].l  = NULL;	        morse[2].r  = NULL;
    morse[3].ch  = 'D'; morse[3].l  = &morse[23];   morse[3].r  = &morse[1];
    morse[4].ch  = 'E'; morse[4].l  = &morse[0];    morse[4].r  = &morse[8];
    morse[5].ch  = 'F'; morse[5].l  = NULL;	        morse[5].r  = NULL;
    morse[6].ch  = 'G'; morse[6].l  = &morse[16];   morse[6].r  = &morse[25];
    morse[7].ch  = 'H'; morse[7].l  = &morse[29];   morse[7].r  = &morse[30];
    morse[8].ch  = 'I'; morse[8].l  = &morse[20];   morse[8].r  = &morse[18];
    morse[9].ch  = 'J'; morse[9].l  = &morse[26];   morse[9].r  = NULL;
    morse[10].ch = 'K'; morse[10].l = &morse[24];   morse[10].r  = &morse[2];
    morse[11].ch = 'L'; morse[11].l = NULL;	        morse[11].r = NULL;
    morse[12].ch = 'M'; morse[12].l = &morse[14];   morse[12].r = &morse[6];
    morse[13].ch = 'N'; morse[13].l = &morse[10];   morse[13].r = &morse[3];
    morse[14].ch = 'O'; morse[14].l = &morse[36];   morse[14].r = &morse[37];
    morse[15].ch = 'P'; morse[15].l = NULL;	        morse[15].r = NULL;
    morse[16].ch = 'Q'; morse[16].l = NULL;	        morse[16].r = NULL;
    morse[17].ch = 'R'; morse[17].l = NULL;         morse[17].r = &morse[11];
    morse[18].ch = 'S'; morse[18].l = &morse[21];   morse[18].r = &morse[7];
    morse[19].ch = 'T'; morse[19].l = &morse[12];   morse[19].r = &morse[13];
    morse[20].ch = 'U'; morse[20].l = &morse[38];   morse[20].r = &morse[5];
    morse[21].ch = 'V'; morse[21].l = &morse[28];   morse[21].r = NULL;
    morse[22].ch = 'W'; morse[22].l = &morse[9];    morse[22].r = &morse[15];
    morse[23].ch = 'X'; morse[23].l = NULL;	        morse[23].r = NULL;
    morse[24].ch = 'Y'; morse[24].l = NULL;	        morse[24].r = NULL;
    morse[25].ch = 'Z'; morse[25].l = NULL;         morse[25].r = &morse[32];
    morse[26].ch = '1'; morse[26].l = NULL;         morse[26].r = NULL;
    morse[27].ch = '2'; morse[27].l = NULL;         morse[27].r = NULL;
    morse[28].ch = '3'; morse[28].l = NULL;         morse[28].r = NULL;
    morse[29].ch = '4'; morse[39].l = NULL;         morse[29].r = NULL;
    morse[30].ch = '5'; morse[30].l = NULL;         morse[30].r = NULL;
    morse[31].ch = '6'; morse[31].l = NULL;         morse[31].r = NULL;
    morse[32].ch = '7'; morse[32].l = NULL;         morse[32].r = NULL;
    morse[33].ch = '8'; morse[33].l = NULL;         morse[33].r = NULL;
    morse[34].ch = '9'; morse[34].l = NULL;         morse[34].r = NULL;
    morse[35].ch = '0'; morse[35].l = NULL;         morse[35].r = NULL;
    morse[36].ch = '='; morse[36].l = &morse[35];   morse[36].r = &morse[34];
    morse[37].ch = '.'; morse[37].l = NULL;         morse[37].r = &morse[33];
    morse[38].ch = '-'; morse[38].l = &morse[27];   morse[38].r = NULL;

    while(EOF != fscanf(fp, "%c", &ch)){

        if (ch == '\n'){                                //  if ch is a newline, print
            putchar(scout->ch);                         //  the current character and
            putchar('\n');                              //  a newline. Then toggle the
            f = 0;                                      //  scout to reset.
        }

        else{

            if (!f){                                        //  if this is the first letter in line
                if (ch == '.')      scout = &morse[4];      //  if . start at 'e'.
                else if (ch == '-') scout = &morse[19];     //  else if - start at 't'.
                if (ch == ' ') putchar(' ');                //  if there were two spaces in the line, then the
                else f = 1;                                 //  second one brought us here. Print a space and
                                                            //  remain reset.  Otherwise, reset.
            }

            else{
                if (ch == '.')      scout = scout->r;       //  if a dot, go to the right.
                else if (ch == '-') scout = scout->l;       //  if a dah, go to the left.
                else if (ch == ' '){                        //  if a space, print the current letter
                    putchar(scout->ch);                     //  and toggle the scout reset.
                    f = 0;
                }
            }
        }

    }

    if (f) putchar(scout->ch);                                 //  if EOF and there's a letter to be printed, print it.
    fclose(fp);
}
