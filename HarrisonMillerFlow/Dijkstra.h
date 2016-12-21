#ifndef DIJKSTRA_H_
#define DIJKSTRA_H_

#include "AdjMatrix.h"
#include <vector>

/*
Simple class for getting a path between
two points given an adjacency matrix
using dijkstra's algorithm
*/
class Dijkstra
{
public:
    Dijkstra();

    //just stores the values
    Dijkstra(AdjMatrix adj,
        Point a,
        Point b);

    //solves for the shortes path between a and b
    //then returns the distance of the shortest path
    int solve();

    //used internally in the pathfinding algorithm
    typedef struct Node
    {
        Node();

        bool visited;
        int distance;
        int previous;

    } Node;

    AdjMatrix adj; //adjacency matrix defining weights between connections

    Point a; //starting point
    Point b; //end point

    //if you called solve this path will contain the nodes for the shrotest
    //path between a and b. if the size of this vector is 1 and a != b then
    //then b was unreachable. TODO: add a valid boolean for clariaty.
    std::vector<Point> path;

};

#endif /*DIJKSTRA_H_*/
