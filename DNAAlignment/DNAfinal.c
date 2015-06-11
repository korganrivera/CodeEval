/*
    This is the hardest problem on CodeEval, according to the success rates on
    the site.  After 12 hours, I had pseudo-code for it. Let's see if it works.
    The premise is basically using the merits of a bad bubble sort recursively.

    start:  2015.6.10.00:09
    break:  2015.6.10.02:07 Almost works, but some glitch preventing it from
                            printing out all solutions.  probably just a loop
                            variable. finish tomorrow.
    start:  2015.6.10.12:00
    note:   2015.6.10.16:13 After 4 hours of running everything by hand, I
                            finally figured it out.  I think...
    END:    2015.6.10.18:58 Okay this time I'm really done.  21 hours of work. O_O
    <sigh>  2015.6.10.19:45 Code works but it's too slow with massive strings.  FUCK.
    @author: Korgan Rivera (korganrivera@gmail.com)
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void func(char *str, unsigned level);

int bestscore;                              //  holds bestscore found so far for each group of words.
unsigned length;                            //  length of the longest word from each pair of words read from file.
char *longword;                             //  this will store the longest word.
unsigned count=0;                           //  number of perms.

int main(int argc, char *argv[]){
    FILE *fp;
    char tmp;
    unsigned i;
    char str1[400], str2[400];              //  this stores the two strings I read from the file.  Specs say strings won't be longer than 400 chars.
    char *shortword;                        //  this will store the shortest word from each pair of words read from file.
    unsigned length1, length2;              //  lengths of each word read from file.
    unsigned shortestlength;                //  length of the shortest word.

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

    //  read string pairs into str1 and str2.
    while(EOF != fscanf(fp, "%s %*c %s", str1, str2)){

        //  measure length of strings and put length in length1 and length2.
        length1 = strlen(str1);
        length2 = strlen(str2);

        //  make 'length' = longest length. make shortestlength = the other value.
        if(length1 > length2){ length = length1; shortestlength = length2; }
        else { length = length2; shortestlength = length1; }

        //  set bestscore to a fairly sensible bad score.
        bestscore=-8*length;

        //  malloc space for shortword and longword using the longest length. +1 is for the null terminator.
        if((shortword = malloc(length+1)) == NULL){ puts("\nmalloc failed."); exit(1); }
        if((longword = malloc(length+1)) == NULL){ puts("\nmalloc failed."); exit(1); }

        //  put the longest word into longword, and shortest word into shortword.
        if(length1 > length2){ strcpy(longword, str1); strcpy(shortword, str2); }
        else { strcpy(longword, str2); strcpy(shortword, str1); }

        //  null terminate the long word.
        longword[length] = '\0';

        //  put the gaps into shortword and null terminate it.
        for(i=shortestlength; i<length; i++) shortword[i] = '-';
        shortword[i] = '\0';

        //  call recursive function func() with shortword, level 0.
        func(shortword, 0);
        printf("\n%d", bestscore);
        printf("\ncount: %d", count);
    }

    free(shortword);
    free(longword);
}


/*
Recursive function that generates all the permutations of the given string, but
at the same time keeps the non-gap elements in order. "Wow, that's amazing! How
did you do that Korgan!? There are factorial(400) permutations in the string, so
surely you don't generate all of them, that would be insane!" -- I hear you say.
And you'd be correct. I did something clever. The trick I noticed was that I can
move a gap up through the string one at a time by exploiting the merits of a
terrible one-loop bubble sort. Whaaat?! No wai! Yes way, my friend. I go through
a complete iteration of a bubble sort, giving the sort the worst case scenario
of the string. In the sort, gap symbols are valued less than any of the DNA
letters G,A,T,C, so only the gap symbols get picked up and moved by the sort.
Then I recursively call this function with each of those iterations in the sort.
This generates only those permutations that have the elements in the same order
they started with. For each generated 'permutation', I score the word pairs, and
save the score if it's better than the best score.
*/

void func(char *str, unsigned level){
    char tmp;
    unsigned i, newgapflag=1;
    char mystr[length];
    int score;

    //  make a copy of the string for this instance of func().
    for(i=0; str[i]; i++) mystr[i] = str[i];
    mystr[i]='\0';

    count++;

    //  score the string.
    for(i=0, score=0; i<length; i++){                                                       //  for each member in the string
        if(*(mystr+i)=='G' || *(mystr+i)=='A' || *(mystr+i)=='T' || *(mystr+i)=='C'){       //  if member of short word is a letter
            newgapflag=1;                                                                   //  reset the newgapflag
            if(*(mystr+i)==longword[i]) score+=3;                                           //  if letters match, increase score by 3 points
            else score-=3;                                                                  //  if letters don't match, decrease score by 3 points.
        }
        else if(newgapflag) { score-=8; newgapflag=0; }                                     //  else if this is start of a new gap, decrease score by 8.
        else score-=1;                                                                      //  else if not a new gap, decrease score by 1.
    }

    //  compare score to current best. if better, save it.
    if(score>bestscore) bestscore = score;

    //  This is one half of a bubble sort that moves
    //  a gap up through the string.  I re-call this
    //  function with each iteration.
    for(i=length-1; i>level; i--){
        if(mystr[i]=='-' && mystr[i-1]!='-'){
            tmp = mystr[i];
            mystr[i] = mystr[i-1];
            mystr[i-1] = tmp;
            func(mystr, level+1);
        }
    }
}
