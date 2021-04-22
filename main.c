#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "maze.h"
#include <assert.h>

int main()
{
  //name of file to solve
  char* mazefile = "input";
  
  //optionally print the file
  //printmaze(mazefile);
  
  //solve the maze
  if (!(solve(mazefile) == 0))
    {
      printf("Could not solve the maze! There may be no solution, exiting...\n");
      return 0;
    }
    
  return 0;
}
