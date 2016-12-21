#ifndef PAIR_H_
#define PAIR_H_

#include "Point.h"
#include <vector>

/*
The main data for representing the state of the game.
each pair has a name (A-Za-z), start/end point and a path.
*/
class Pair
{
public:
    Pair();

    //sets members
    Pair(char name,
        Point a,
        Point b);

    //returns wether or not the path connects a to b
    bool isConnected();

    //returns the number of grid spaces filled by the
    //pair and it's path
    int getFilled();

    //prints the name and path of the pair, points printed in y,x order.
    //e.g) A - (0, 0) (0, 1) (0, 2) (0, 3) (1, 3) (2, 3) (3, 3)
    void print();

    //only checks name
    bool operator==(const Pair& o);

    bool operator!=(const Pair& o);

    char name;

    Point a;
    Point b;

    std::vector<Point> path;

};

#endif /*PAIR*/
