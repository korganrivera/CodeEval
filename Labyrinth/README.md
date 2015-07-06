# Labyrinth

Given a text file with a map schema in it, find the shortest path through the maze.

I used a recursive solution to find the shortest path, and then a non-recursive 
backtracking loop to mark the path back to the start. I could have used A* but 
I didn't.  THe algorithm fills the whole grid with distance values.  A* might 
save a little time, if the extra comparisons don't make it pointless.