#ifndef SPOT_H_INCLUDED
#define SPOT_H_INCLUDED
#pragma once

//! The class for the individual spots in the maze
//! gets created whenever an empty spot has been found in the maze. Contains a pointer to its parent and some basic information.
class Spot
{
private:
    int x, y;
    Spot* parent = nullptr;
public:
    Spot(int x, int y, Spot* parent);
    int getX()
    {
        return this->x;
    }
    int getY()
    {
        return this->y;
    }
    /// Returns pointer to Spot parent
    Spot* retParent()
    {
        return this->parent;
    }
};

#endif // SPOT_H_INCLUDED

