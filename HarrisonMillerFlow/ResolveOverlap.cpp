#include "Checker.h"
#include "Dijkstra.h"
#include <iostream>

//this is a member function of Checker
//so it has access to creature/pairs
//this is the slowest part of the entire program
//because of the massive amount of looping
//I would have liked to avoid using this, but I was
//unable to get the pure genetic algorithm solve that many problems
//because the search space was too wide.
void Checker::resolveOverlap(AdjMatrix& adj)
{
    //resolve order pairs
    //reorder the pairs for resolving
    std::vector<Pair> rpairs;
    for(int i = 0; i < creature.resolveOrder.size(); i++)
    {
        rpairs.push_back(pairs[creature.resolveOrder[i]]);

    }

    pairs = rpairs;

    AdjMatrix adjb(width, height); //create an adjacency matrix that has no blocked connections

    //connect stuff that got left out
    for(int i = 0; i < pairs.size(); i++)
    {
        Pair& pair = pairs[i];

        if(!pair.isConnected())
        {
            //only block start/end nodes
            //allows for the path to overlap other stuff
            AdjMatrix adj2 = adjMatrixFrom(adj, pair, false);

            Dijkstra pather(adj2, pair.a, pair.b);
            pather.solve();

            pair.path = pather.path;

        }
    
    }

    //resolve overlaps
    //we go through the loop twice so if something gets pushed into another path that already iterated
    //that old path gets a chance to reresolve. (unfortunately this can also lead to bounce back (path switching between intersecting to paths).
    int pairs2x = pairs.size()*2;
    for(int f = 0; f < pairs2x; f++)
    {
        int i = f%pairs.size(); //get the index
        Pair& pair = pairs[i];

        //used the unmodified adj
        AdjMatrix adj2 = adjMatrixFrom(adjb, pair); //create an adj with paths/nodes blocked 

        bool found = false;
        //this quadrople for loop is where I kill the program efficiency
        for(int j = 0; j < pairs.size(); j++)
        {
            if(i != j)
            {
                Pair& pair2 = pairs[j];
                for(int k = 0; k < pair.path.size(); k++)
                {
                    for(int l = 0; l < pair2.path.size(); l++)
                    {
                        if(pair.path[k] == pair2.path[l]) //paths share a point
                        {
                            //with blocking
                            //try to see if there is a nice unblocked path, most of the time there isn't
                            Dijkstra pather(adj2, pair.a, pair.b);
                            pather.solve();

                            if(pather.path.size() > 1)
                            {
                                pair.path = pather.path;
                                found = true;
                                break;

                            }
                            else
                            {
                                //if we couldn't reroute the above path try to reroute the path around just the current conflicting one.

                                Pair& reroute = pair;//creature.strength[i] > creature.strength[j] ? pair : pair2;
                                Pair& router = pair2;//creature.strength[i] > creature.strength[j] ? pair2 : pair;

                                AdjMatrix adj3 = adjMatrixFrom(adjb, reroute, false);

                                //only block using the routers path (the conflicting path with which we share a point).
                                for(int m = 0; m < router.path.size(); m++)
                                {
                                    adj3.exclude(router.path[m]);

                                }

                                Dijkstra pather2(adj3, reroute.a, reroute.b);
                                pather2.solve();

                                if(pather2.path.size() > 1)
                                {
                                    reroute.path = pather2.path;
                                    found = true;
                                    break;

                                }

                            }

                        }

                    }

                    if(found)
                    {
                        break;

                    }

                }

            }

            if(found)
            {
                break;

            }

        }

    }

    //break any remaining overlaps
    for(int i = 0; i < pairs.size(); i++)
    {
        Pair& pair = pairs[i];

        //blocks all nodes and paths
        AdjMatrix adj2 = adjMatrixFrom(adj, pair);

        bool found = false;
        for(int j = 0; j < pairs.size(); j++)
        {
            if(i != j)
            {
                Pair& pair2 = pairs[j];

                for(int k = 0; k < pair.path.size(); k++)
                {
                    for(int l = 0; l < pair2.path.size(); l++)
                    {
                        if(pair.path[k] == pair2.path[l])
                        {
                            //if this is still overlapping it will be broken by doing this
                            //since the adj we use blocks nodes/paths
                            Dijkstra pather(adj2, pair.a, pair.b);
                            pather.solve();
                            pair.path = pather.path;
                            found = true;
                            break;

                        }

                    }

                    if(found)
                    {
                        break;

                    }

                }

            }

            if(found)
            {
                break;

            }

        }

    }

}
