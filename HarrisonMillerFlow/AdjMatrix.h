#ifndef ADJMATRIX_H_
#define ADJMATRIX_H_

#include "Point.h"
#include <vector>

/*
Represents an adjacency matrix data structure for path finding
really just a nice wrapper around a 2d vector
NOTE: this adjacency matrix is only meant for 2d grids where
the only valid connections are between adjacent tiles (up, down, left, right).
*/
class AdjMatrix
{
public:
    AdjMatrix();

    //initializes all the connection weights
    //the sets all valid connections between tiles to 1
    AdjMatrix(int width,
        int height);

    //returns the number of nodes width*height
    int getSize();

    //gets the flattned index of the point
    //(doesn't check if the point is within the grid).
    int indexOf(Point p);

    //returns the point given and index
    //useful for reconstructing the path in a human readable way
    Point pointFrom(int index);

    //if both from and to are in the grid it will set the
    //weight of their connections. if w == 0 the connection will be uneffected
    //but may still return true or false, depending on from/to lying withing the grid.
    bool set(Point from,
        Point to,
        int w);

    //sets all connections going into the point to -1 (unreachable).
    void exclude(Point p);

    //prints a lot of numbers -1 (unreachable is replaced with '.' to make it more readable).
    void print();

    int width;
    int height;

    std::vector<std::vector<int> > data;

};

#endif /*ADJMATRIX*/
