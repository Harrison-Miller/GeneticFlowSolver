#include "Dijkstra.h"

Dijkstra::Dijkstra()
{
}

Dijkstra::Dijkstra(AdjMatrix adj,
    Point a,
    Point b) :
    adj(adj),
    a(a),
    b(b)
{
}

int Dijkstra::solve()
{
    //incase this is called multiple times
    //this might be done if the users
    //sets a new adj but keeps the same a/b points
    path.clear();

    //get the adjacency matrix index of a
    int start = adj.indexOf(a);

    //get the number of nodes in the adjacency matrix
    int size = adj.getSize();

    //create a default vector of nodes
    std::vector<Node> nodes;

    for(int i = 0; i < size; i++)
    {
        //initializes distance to 10000000 (not really infinite but wont happen in this use case)
        nodes.push_back(Node());

    }

    //initialize the start node distance to 0 so it's picked first
    nodes[start].distance = 0;

    //used as a counter to determine when to stop looking at nodes
    int visited = size;

    //run dijkstra's algorithm
    while(visited != 0)
    {
        int index = 0;
        int least = 1000000;
        //find the node with the least distance
        for(int i = 1; i < nodes.size(); i++)
        {
            if(!nodes[i].visited
                && nodes[i].distance < least)
            {
                index = i;
                least = nodes[i].distance;

            }

        }

        //update the node to be visited so it's not checked again
        nodes[index].visited = true;
        visited--;

        for(int i = 0; i < size; i++)
        {
            //get the wait from the node to all it's connections
            int w = adj.data[index][i];
            if(w >= 0)
            {
                if(nodes[index].distance + w < nodes[i].distance)
                {
                    //update the distance to the node given the weight
                    nodes[i].distance = nodes[index].distance + w;
                    nodes[i].previous = index;

                }

            }

        }

    }

    //reconstruct the path
    int end = adj.indexOf(b);

    while(nodes[end].previous != -1)
    {
        //insert the point at the beginning so the path is from a to b rather than the other way around
        path.insert(path.begin(), adj.pointFrom(end));
        end = nodes[end].previous;

    }

    path.insert(path.begin(), adj.pointFrom(end));

    //return the lenght of the shortest path
    return path.size();

}

//default constructor for the node used above.
Dijkstra::Node::Node()
{
    visited = false;
    distance = 1000000;
    previous = -1;

}
