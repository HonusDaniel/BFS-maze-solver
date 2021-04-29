#include "maze.hpp"

// https://stackoverflow.com/questions/60656309/how-could-i-optimize-my-breadth-search-algorithm-for-solving-bigger-mazes

Spot::Spot(int x, int y, Spot* parent)
{
    this->x = x;
    this->y = y;
    this->parent = parent;
}
Spot::Spot()
{
    this->parent = nullptr;
}

Spot* Spot::getParents()
{
    if (this->parent != nullptr)
    {
        do
        {
            std::cout << this->parent->getX() << ";" << this->parent->getY() << std::endl;
        }         while (this->parent->getParents() != nullptr);
    }
    return nullptr;
}

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
    
    maze >> this->width;
    maze >> this->height;
    this->themaze = new int* [this->width];
    this->visited = new bool* [this->width];
    if (this->themaze && this->visited)  //kontrola alokace
    {
        for (int i = 0; i < this->width; i++)
        {
            this->themaze[i] = new int[this->height];
            this->visited[i] = new bool[this->height];
            assert(this->themaze[i]); //kontrola alokace
            assert(this->visited[i]);
        }
    }
}
Maze::~Maze()
{
    for (int i = 0; i < width; i++)
    {
        delete[] this->themaze[i];
        delete[] this->visited[i];
    }
    delete[] this->themaze;
    delete[] this->visited;
}
void Maze::aMaze()
{
    if (this->current->retParent() != nullptr)
    {
        do
        {
            this->themaze[current->getX()][current->getY()] = 4;
            this->current = this->current->retParent();
            aMaze();
        }         while (this->current->retParent() != nullptr);    delete this->current->retParent();
    }
    delete this->current->retParent();
}

bool Maze::check(int X, int Y)
{
    if (!this->visited[X][Y])
    {
        if ((this->themaze[X][Y] == 0 || this->themaze[X][Y] == 3) && !(X == this->start->getX() && Y == this->start->getY()))
            return true;
    }
    return false;
}
void Maze::theSolver()
{
    output.open("output");
    if (!(output.is_open()))
    {
        printf("could not create the output file, exiting...\n");
        output.close();
        exit(EXIT_FAILURE);
    }


    output << this->width << " ";
    output << this->height << "\n";

    char c;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            maze.get(c);
            if (c == '\n')
                maze.get(c);
            this->themaze[i][j] = c - '0';
            //fscanf(this->maze, "%1d", &this->themaze[i][j]);
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

    this->visited[start->getX()][start->getY()] = true;

    this->que.push(start);
    while (!this->que.empty())
    {
        this->current = this->que.front();
        this->que.pop();
        int curX = this->current->getX();
        int curY = this->current->getY();

        this->visited[this->current->getX()][this->current->getY()] = true;
        if ((curX == finish->getX()) && (curY == finish->getY()))
        {
            std::cout << "Found the exit at: " << current->getX() << ";" << current->getY() << std::endl;
            break;
        }

        if (check(curX + 1, curY))
        {
            visited[curX + 1][curY] = true;
            Spot* next = new Spot(curX + 1, curY, this->current);
            que.push(next);
        }
        if (check(curX, curY + 1))
        {
            visited[curX][curY + 1] = true;
            Spot* next = new Spot(curX, curY + 1, this->current);
            que.push(next);
        }
        if (check(curX - 1, curY))
        {
            visited[curX - 1][curY] = true;
            Spot* next = new Spot(curX - 1, curY, this->current);
            que.push(next);
        }
        if (check(curX, curY - 1))
        {
            visited[curX][curY - 1] = true;
            Spot* next = new Spot(curX, curY - 1, this->current);
            que.push(next);
        }
    }

    //posunout ukazatel na aktualni
    this->current = this->current->retParent();
    //zapsat do souboru
    aMaze();

    //read and print
    /* */
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            output << this->themaze[i][j];
            if (themaze[i][j] == 1)
                printf("#");
            else if (themaze[i][j] == 2 || themaze[i][j] == 3)
                printf("X");
            else if (themaze[i][j] == 4)
                printf("*");
            else printf(" ");
        }
        output << "\n";
        printf("\n");
    }

    delete start;
    delete finish;
    maze.close();
    output.close();
}

int solve(const char* filename)
{
    Maze* themaze = new Maze(filename);
    themaze->theSolver();

    delete themaze;
    return 0;
}

