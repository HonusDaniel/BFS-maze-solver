#ifndef MAZE_H_INCLUDED
#define MAZE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <queue>
#include "spot.h"
#pragma once

int solve(const char* filename);

//! The maze class
//! contains the maze which it loads from a file, the dimensions of the maze, the queue used for BFS solving using its Maze::theSolver() function and other variables
class Maze
{
private:
    int width;
    int height;
    int** themaze;
    bool** visited;
    //! the queue used in theSolver() to keep track of nodes to visit
    std::queue<Spot*> que;
    //! queue used to keep track of nodes allocated in theSolver() for deletion
    std::queue<Spot*> old;
    Spot* current = nullptr;
    Spot* start = nullptr;
    Spot* finish = nullptr;
    //! Input file, used in the Maze::Maze constructor to load the maze
    std::ifstream maze;
    std::ofstream output;
public:
    Maze(const char* filename);
    ~Maze();
    void theSolver();
    void aMaze(); 
    /// Boolean function to check validity of a Spot in the maze
    /// 
    /// Checks if the Spot has been visited already, if it is not the starting point and whether and whether it is within the bounds of the maze
    bool check(int X, int Y);
    void printer();
};
#endif // MAZE_H_INCLUDED

