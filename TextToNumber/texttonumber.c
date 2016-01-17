/*
    CodeEval's Text To Number challenge.
    Given some number in words, convert it to digits.
    How I'll do this: I'll work it backwards.  If I get two million one hundred seven,
    I'll add 7 to my number, I'll add hundred * one to my number, I'll add million * two.
    And so on.  If the last word is 'negative', I'll multiply it all by -1.  Easy.
    The hardest part will be reading in the word.
    The most words it could possible contain is 15:
    negative seven hundred seventy seven million seven hundred seventy seven thousand seven hundred seventy seven
    So I'll just use an array of char pointers.  Also, the longest string is 109 chars, so I can use fgets.
    trying looking up the string tokenising shit later.
    NOt going to fuck with strtok.  Just read in one word at a time using fscanf or something,
    start with a value of zero.  and run a bunch of ifs on it.
*/

int main(int argc, char *argv[]){
    FILE *fp;
    char str[110];
    unsigned slen;
    int i, j;
    char ch, newlineflag=0;
    long int number=1;
    char match;

    //  open file in text mode.
    if((fp=fopen(argv[1],"r")) == NULL){ puts("\ncan't open file."); exit(1);}

    //  read a string.
    while(NULL != fgets(str, 110, fp)){

        //  prints newline if requested.
        if(newlineflag) { putchar('\n'); newlineflag=0; }

        //  This will include a newline that fgets keeps.
        slen = strlen(str);

        //  overwrite the newline with a null terminator. reduce string length to reflect this.
        if(str[slen-1]=='\n'){ str[slen-1] = '\0'; slen--; }

        if(strstr(str, "negative")) number*=-1;
        else if(strstr(str, "zero")) number*=0;
        else if(strstr(str, "negative")) number*=-1;
        else if(strstr(str, "negative")


}


