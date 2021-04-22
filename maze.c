#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "maze.h"
#include <assert.h>
#include <stdbool.h>

// https://stackoverflow.com/questions/60656309/how-could-i-optimize-my-breadth-search-algorithm-for-solving-bigger-mazes


int solve(char* filename)
{
  FILE* maze;

  // if can't load file, exit
  if (!(maze = fopen(filename, "r"))){
    printf("could not find '%s' file with maze, exiting...\n", filename);
    assert(!fclose(maze));
    exit(EXIT_FAILURE);
  }

  //if okay continue to solve
  FILE* output = fopen("output", "w+");

  int width, height;
  fscanf(maze, "%d %d", &width, &height);
  
  int maze_array[width][height];
  bool visited[width][height];

  //read and print
  for (int i = 0; i < height; i++)
  {
    for(int j = 0; j < width; j++)
    {
      fscanf(maze, "%1d", &maze_array[i][j]);
      visited[i][j] = false;
    }
  }

  

  assert(!fclose(maze));
  assert(!fclose(output));
  return 0;
}


//optional function to print a maze file using special characters
void printmaze(char* filename){
  int width, height = 0;
  FILE* maze;

  // if can't load file, exit
  if (!(maze = fopen(filename, "r"))){
    printf("could not find '%s' file with maze, exiting...\n", filename);
    assert(!fclose(maze));
    exit(EXIT_FAILURE);
  }


  //get size of maze
  fscanf(maze, "%d %d", &width, &height);
  int maze_array[width][height];

  //read and print
  for (int i = 0; i < height; i++)
  {
    for(int j = 0; j < width; j++)
    {
      fscanf(maze, "%1d", &maze_array[i][j]);
      if (maze_array[i][j] == 1)
        printf("#");
      else if (maze_array[i][j] == 2 || maze_array[i][j] == 3) 
          printf("X");
        else printf(" ");
    }
    printf("\n");
  }

  assert(!fclose(maze));
}
