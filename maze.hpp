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
#pragma once

int solve(const char* filename);

class Spot
{
private:
    int x, y;
    Spot* parent = nullptr;
public:
    Spot();
    Spot(int x, int y, Spot* parent);
    int getX()
    {
        return this->x;
    }
    int getY()
    {
        return this->y;
    }
    Spot* getParents();
    Spot* retParent()
    {
        return this->parent;
    }
};

class Maze
{
private:
    int width;
    int height;
    int** themaze;
    bool** visited;
    std::queue<Spot*> que;
    Spot* current = nullptr;
    Spot* start = nullptr;
    Spot* finish = nullptr;
    std::ifstream maze;
    std::ofstream output;
public:
    Maze(const char* filename);
    ~Maze();
    void theSolver();
    void aMaze(); // zapisuje do souboru
    bool check(int X, int Y);
};
#endif // MAZE_H_INCLUDED
