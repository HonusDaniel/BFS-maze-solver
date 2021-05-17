#include "maze.h"
#include "spot.h"
/// constuctor for Spot used for spots other than the start and finish
/// @param parent a pointer to the parent of the Spot
Spot::Spot(int x, int y, Spot* parent)
{
    this->x = x;
    this->y = y;
    this->parent = parent;
}

/// opens the maze input file from filename and loads its contents into two new 2D arrays
/// @param filename the file name passed from the main.cpp file as an argument to Maze::solve()
/// \sa themaze \sa visited \sa filename
Maze::Maze(const char* filename)
{
    // if can't load file, exit
    maze.open(filename);
    if (!(maze.is_open()))
    {
        printf("could not find '%s' file with maze, exiting...\n", filename);
        maze.close();
        exit(EXIT_FAILURE);
    }
    
    //maze dimensions
    maze >> this->width;
    maze >> this->height;

    this->themaze = new int* [this->width];
    this->visited = new bool* [this->width];
    if (this->themaze && this->visited)  //checks if allocated
    {
        for (int i = 0; i < this->width; i++)
        {
            this->themaze[i] = new int[this->height];
            this->visited[i] = new bool[this->height];
            assert(this->themaze[i]);
            assert(this->visited[i]);
        }
    }
}

Maze::~Maze()
{
    //free memory in queue
    if(que.size() > 0)
        for (long unsigned int i = 0; i <= que.size(); i++)
        {
            Spot* del = this->que.front();
            this->que.pop();
            delete del;
        }
    // delete the rest
    if (old.size() > 0)
        for (long unsigned int i = 0; i <= old.size(); i++)
        {
            Spot* del = this->old.front();
            this->old.pop();
            delete del;
        }

    for (int i = 0; i < width; i++)
    {
        delete[] this->themaze[i];
        delete[] this->visited[i];
    }

    delete[] this->themaze;
    delete[] this->visited;
}

///  optional printing method
void Maze::printer() {
    for (int i = 0; i < this->height; i++)
    {
        for (int j = 0; j < this->width; j++)
        {
            if (themaze[i][j] == 1)
                printf("#");
            else if (themaze[i][j] == 2 || themaze[i][j] == 3)
                printf("X");
            else if (themaze[i][j] == 4)
                printf("*");
            else printf(" ");
        }
        printf("\n");
    }
}

/// recusively goes through parents of the successful path to the end and marks their coordinates as the path for the output
void Maze::aMaze()
{
    Spot* temp = this->current;
    if (temp->retParent() != nullptr)
    {
        do {
            themaze[temp->getX()][temp->getY()] = 4;
            temp = temp->retParent();
        } while (temp->retParent() != nullptr);
    }
}

bool Maze::check(int X, int Y)
{
    if (X < 0 || X >= this->width || Y < 0 || Y >= this->height)
        return false;
    else 
        if (!this->visited[X][Y])
        {
            if ((this->themaze[X][Y] == 0 || this->themaze[X][Y] == 3) && (this->themaze[X][Y] != 2))
                return true;
        }
    return false;
}

/// main method for the bfs algorithm
/// 
/// loads data from file, checks the maze for errors, solves it and calls cleanup methods
void Maze::theSolver()
{
    output.open("output.txt");
    if (!(output.is_open()))
    {
        printf("could not create the output file, exiting...\n");
        output.close();
        exit(EXIT_FAILURE);
    }

    output << this->width << "\n";
    output << this->height << "\n";

    // load the maze from file into array
    char c;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            maze.get(c);
            if (c == '\n')
                maze.get(c);
            this->themaze[i][j] = c - '0';
            this->visited[i][j] = false;
            if (themaze[i][j] == 2)
            {
                this->start = new Spot(i, j, nullptr);
                visited[i][j] = true;
            }
            if (themaze[i][j] == 3)
                this->finish = new Spot(i, j, nullptr);
        }
    }

    if (!start || !finish)
    {
        std::cout << "Can't find start or finish in the maze!" << std::endl;
        exit(EXIT_FAILURE);
    }

    visited[start->getX()][start->getY()] = true;

    this->que.push(start);
    while (!this->que.empty())
    {
        this->current = this->que.front();
        this->que.pop();
        int curX = this->current->getX();
        int curY = this->current->getY();
        visited[curX][curY] = true;

        if ((curX == finish->getX()) && (curY == finish->getY()))
        {
            std::cout << "Found the exit at: " << current->getX() << ";" << current->getY() << std::endl;
            break;
        }

        if (check(curX + 1, curY))
        {
            Spot* next = new Spot(curX + 1, curY, this->current);
            que.push(next);
            visited[curX + 1][curY] = true;
        }
        if (check(curX, curY + 1))
        {
            Spot* next = new Spot(curX, curY + 1, this->current);
            que.push(next);
            visited[curX][curY + 1] = true;
        }
        if (check(curX - 1, curY))
        {
            Spot* next = new Spot(curX - 1, curY, this->current);
            que.push(next);
            visited[curX - 1][curY] = true;
        }
        if (check(curX, curY - 1))
        {
            Spot* next = new Spot(curX, curY - 1, this->current);
            que.push(next);
            visited[curX][curY - 1] = true;
        }
        //store pointer of the unused spot to delete
        this->old.push(current);
    }

    //que will be empty if there is no path
    if (que.size() == 0)
    {
        std::cout << "The maze seems to be unsolvable. Exiting..." << std::endl;
        delete finish;
        maze.close();
        output.close();
        return;
    }

    Spot* rem = this->current;
    this->current = this->current->retParent();
    delete rem;
    aMaze();

    //write to file
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            this->output << this->themaze[i][j];
        }
        this->output << "\n";
    }

    delete finish;

    maze.close();
    output.close();
}

int solve(const char* filename)
{
    Maze* themaze = new Maze(filename);

    themaze->theSolver();
    themaze->printer();

    delete themaze;
    return 4;
}

