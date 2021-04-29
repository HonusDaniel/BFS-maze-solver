#include <iostream>
#include "maze.hpp"

int main()
{
    const char* mazefile = "input";

    if (solve(mazefile) != 0)
        std::cout << "could not solve the maze." << std::endl;
    return 0;
}

