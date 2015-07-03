/*
    Robot Movements problem on CodeEval.
    pseudo:
    A recursive function that does the following:
        if you are at destination, increment path count and return.
        if you can't go anywhere, return.

        if you can go up, mark current block as visited and go up.
        if you can go down,  mark current block as visited and go down.
        if you can go left,  mark current block as visited and go left.
        if you can go right,  mark current block as visited and go right.

    2015.19.2015    Finished.  I get a crash if I use numbers that are too big and
                    I think it's because I'm doing recursive branches dependent on local variables.
                    If I malloced something instead, I could control for that. But yeah, the number
                    of paths possible in just a 6x6 grid is insane.  Over a million. :O
*/

#include <stdio.h>

#define ROWS 14
#define COLS 4

void func(unsigned x, unsigned y, unsigned *grid, unsigned gx, unsigned gy);

unsigned brows = ROWS+2;    //  height of grid with an edge.
unsigned bcols = COLS+2;    //  width of grid with an edge.
unsigned count=0;           //  number of paths from start to end.

int main(void){
    unsigned i,j, grid[ROWS+2][COLS+2];

    //  initialise grid. 1s on the edge, zeroes elsewhere.
    for(i=0; i<brows*bcols; i++) grid[i/bcols][i%bcols] = !(i%bcols) || (i%bcols==bcols-1) || !(i/bcols) || (i/bcols==brows-1);
    func(1,1, &grid[0][0], 1+ROWS-1, 1+COLS-1);
    printf("%u", count);
}


void func(unsigned x, unsigned y, unsigned *grid, unsigned gx, unsigned gy){
    unsigned mygrid[ROWS+2][COLS+2], i, j;

    //  if deadend, return.
    if(!(*(grid+x*bcols+y-bcols)) && !(*(grid+x*bcols+y+bcols)) && !(*(grid+x*bcols+y-1)) && !(*(grid+x*bcols+y+1))){ return; }

    //  if you're at the goal, increment solution count and return.
    if(x==gx && y==gy) { count++; return; }

    //  copy the map.
    for(i=0; i<brows*bcols; i++) mygrid[i/(COLS+2)][i%(COLS+2)] = *(grid+i);

    //  mark current position as visited.
    mygrid[x][y] = 1;

    //  if you can move up, do it.
    if(!mygrid[x-1][y]){ func(x-1, y, &mygrid[0][0], gx, gy); }

    //  if you can move right, do it.
    if(!mygrid[x][y+1]){ func(x, y+1, &mygrid[0][0], gx, gy); }

    //  if you can move left, do it.
    if(!mygrid[x][y-1]){ func(x, y-1, &mygrid[0][0], gx, gy); }

    //  if you can move down, do it.
    if(!mygrid[x+1][y]){ func(x+1, y, &mygrid[0][0], gx, gy); }
}
