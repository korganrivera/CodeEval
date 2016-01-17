/*
    CodeEval's Labyrinth problem.
    Read a maze from a textfile, solve the maze.  The maze can
    be up to 101x101 cells. Output will be the same map with
    the solution marked out with '+'.
    I'm going to do a recursive breadth first search to set distance
    markers outward from the start point until I hit the goal, then
    follow the path back.  Not sure if that will work yet.
    The maze has an upper opening where I start, and an lower opening
    where I end.
    If the maze is not solvable, the program will be stuck in a loop.
    I could put a check in there to see if the map is filled with numbers
    but that would slow stuff down.

    start:  2015.7.3.21:57
    end:    2015.7.3.22:45  This seat is uncomfortable.  Do more tomorrow.
    start:  2015.7.6.13:00
    end:    2015.7.6.15:05  seems to be working.
*/

#include <stdio.h>
#include <stdlib.h>

int func(unsigned start, unsigned end, unsigned h, unsigned len, unsigned *grid);   //  returns a victory condition of 1, so I can head back to root as soon as I find exit. might work.

int main(int argc, char *argv[]){
    FILE *fp;
    unsigned i,h,w,sz,*maze,start,end;
    char c;

    //  open file in text mode.
    if((fp=fopen(argv[1],"r")) == NULL){ puts("can't open file."); exit(1);}

    //  calculate line length.  add 2 for edge.
    for(w=0, rewind(fp); (c=fgetc(fp))!=EOF && c!='\n'; w++); w = w+2;

    //  calculate height of grid. add 2 for edge.
    rewind(fp); h=0;
    while((c=fgetc(fp))!=EOF) if(c=='\n') h++; h+=2;

    //  malloc space for the maze, exit on fail.
    if((maze = malloc((sz=h*w)*sizeof(unsigned))) == NULL){ puts("malloc failed."); exit(1); }

    //  read file into buffer, discarding newlines along the way. close file.
    rewind(fp); i=w+1;
    while((c=fgetc(fp))!=EOF){
        if(c=='\n') i+=2;
        else *(maze+i++) = c+sz;
    }
    fclose(fp);

    //  put blocks all around the edge.
    for(i=0; i<sz; i++) if(!(i/w) || i/w==h-1 || !(i%w) || i%w==w-1) *(maze+i) = '*'+sz;

    //  scan top edge for opening.
    for(i=w+1, start=0; i<2*w-1; i++){ if(*(maze+i)==' '+sz){ start=i; break; } }
    if(i==2*w-1) { puts("can't find entrance! abandon ship!"); exit(1); }

    //  scan bottom edge for exit.
    for(i=(h-2)*w+1, end=0; i<(h-1)*w-1; i++){ if(*(maze+i)==' '+sz){ end=i; break; } }
    if(i==(h-1)*w-1) { puts("\ncan't find exit! abandon ship!"); exit(1); }

    //  put value zero into the start.
    *(maze+start) = 0;

    //  call the recursive function to populate the rest of the map with numbers.
    func(start, end, h, w, maze);

    //  Now backtrack from end, following the best path. replace path with '+'+sz, along the way.
    while(start!=end){
        if(*(maze+end-1) == *(maze+end)-1){ *(maze+end) = '+'+sz; end -= 1; }
        else if(*(maze+end+1) == *(maze+end)-1){ *(maze+end) = '+'+sz; end += 1; }
        else if(*(maze+end-w) == *(maze+end)-1){ *(maze+end) = '+'+sz; end -= w; }
        else if(*(maze+end+w) == *(maze+end)-1){ *(maze+end) = '+'+sz; end += w; }
    }

    //  put asterisk in start position.
    *(maze+start) = '+'+sz;

    //  print it.
    for(i=w+1; i<(h-1)*w-1; i++){
        if(i%w==w-1){ i+=2; putchar('\n'); }
        if(*(maze+i) == '*'+sz) printf("*");
        else if(*(maze+i) == '+'+sz) printf("+");
        else printf(" ");
    }
    free(maze);
}

//  for each square around start, that holds a value higher than current cell, put a value one higher than current cell.
//  then run func on each of them.  if all viable cells contain a value one higher, then return.
int func(unsigned start, unsigned end, unsigned h, unsigned w, unsigned *grid){
    unsigned sz=h*w;

    if(start==end) return 1;

    //  set cell on the left if required.
    if(*(grid+start-1) != ('*'+sz) && *(grid+start-1)>(*(grid+start)+1)){
        *(grid+start-1) = *(grid+start)+1;
        func(start-1, end, h, w, grid);
    }

    //  set cell on the right if required.
    if(*(grid+start+1) != ('*'+sz) && *(grid+start+1)>(*(grid+start)+1)){
        *(grid+start+1) = *(grid+start)+1;
        func(start+1, end, h, w, grid);
    }

    //  set cell above if required.
    if(*(grid+start-w) != ('*'+sz) && *(grid+start-w)>(*(grid+start)+1)){
        *(grid+start-w) = *(grid+start)+1;
        func(start-w, end, h, w, grid);
    }

    //  set cell below if required.
    if(*(grid+start+w) != ('*'+sz) && *(grid+start+w)>(*(grid+start)+1)){
        *(grid+start+w) = *(grid+start)+1;
        func(start+w, end, h, w, grid);
    }
    return 0;
}
