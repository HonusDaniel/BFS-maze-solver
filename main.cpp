#include <iostream>
#include "maze.h"

/*! \mainpage Maze
 *
 * Project maze solver
 * 
 * Main algorithm a loose combination of:
 * - \subpage https://www.geeksforgeeks.org/breadth-first-search-or-bfs-for-a-graph/
 * - \subpage https://stackoverflow.com/questions/16366448/maze-solving-with-breadth-first-search
 */

int main()
{
    const char* mazefile = "input";

    if (solve(mazefile) != 4)
        std::cout << "could not solve the maze." << std::endl;
    return 0;
}

