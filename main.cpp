#include <iostream>
#include "maze.h"

int main()
{
    const char* mazefile = "input";

    if (solve(mazefile) != 4)
        std::cout << "could not solve the maze." << std::endl;
    return 0;
}

