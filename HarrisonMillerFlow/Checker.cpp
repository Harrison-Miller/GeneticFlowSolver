#include "Checker.h"
#include "Dijkstra.h"
#include "Fitness.h"
#include <iostream>

Checker::Checker() :
    fitness(0),
    width(0),
    height(0)
{
}

Checker::Checker(int width,
    int height,
    std::vector<Pair> pairs,
    Creature creature) :
    fitness(0),
    width(width),
    height(height),
    pairs(pairs),
    creature(creature)
{
}

AdjMatrix Checker::adjMatrixFrom(AdjMatrix adj, Pair& pair, bool block)
{
    for(int i = 0; i < pairs.size(); i++)
    {
        Pair& pair2 = pairs[i];
        if(pair.a != pair2.a && pair.b != pair2.b)
        {
            //blocks all connections to and from a point (using a -1 weight)
            adj.exclude(pair2.a);
            adj.exclude(pair2.b);

            if(block)
            {
                //blocks all used path points
                for(int j = 0; j < pair2.path.size(); j++)
                {
                    adj.exclude(pair2.path[j]);

                }

            }

        }

    }

    return adj;

}

void Checker::run()
{
    //reorder pairs
    std::vector<Pair> npairs;
    for(int i = 0; i < creature.order.size(); i++) //this is where the special gene order is used
    {
        npairs.push_back(pairs[creature.order[i]]);

    }

    std::vector<Pair> orig = pairs; //store the original ordering for later
    pairs = npairs;

    AdjMatrix adj(width, height);

    int geneIndex = 0;

    //setup the initial adjacency matrix using the
    //creature's genes to make connections between adjacent nodes
    //the creature's gene length must be the length of valid connections
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            Point p(j, i);

            Point up(p.x, p.y-1);
            Point down(p.x, p.y+1);
            Point left(p.x-1, p.y);
            Point right(p.x+1, p.y);

            //abuses boolean to integer to use -1 for blocking or 0 for unchanged
            //we do geneIndex += 1/0 to go through the genes, there will always be the correct number of
            //genes given the adjmatrix is the correct size. adj.set returns true (1) if it was succesfully set
            geneIndex += adj.set(p, up, creature.genes[geneIndex]-1);
            geneIndex += adj.set(p, down, creature.genes[geneIndex]-1);
            geneIndex += adj.set(p, left, creature.genes[geneIndex]-1);
            geneIndex += adj.set(p, right, creature.genes[geneIndex]-1);

        }

    }

    //try and run the solution
    for(int i = 0; i < pairs.size(); i++)
    {
        Pair& pair = pairs[i];

        //make a custom adjmatrix that blocks other pairs start/end points
        //aswell as their paths
        AdjMatrix adj2 = adjMatrixFrom(adj, pair);

        //solve for the shortest path between a and b
        Dijkstra pather(adj2, pair.a, pair.b);
        pather.solve();

        pair.path = pather.path;

    }

    //reorder so the resolveOverlap can reorder correctly
    reorderPairs(orig);

    //this is the slowest part of the algorithm
    resolveOverlap(adj); //creates unconnected connections, then resolves the overlaps the create

    //reorder the pairs for so it's easier to read :)
    reorderPairs(orig);

    //get the fitness of the solution
    fitness = getFitness(width, height, pairs);
    creature.fitness = fitness;

}

void Checker::reorderPairs(std::vector<Pair> orig)
{
    //reorders the pairs to the original order but keeping the new data
    for(int i = 0; i < orig.size(); i++)
    {
        for(int j = 0; j < pairs.size(); j++)
        {
            if(orig[i].name == pairs[j].name)
            {
                orig[i] = pairs[j];
                break;

            }

        }

    }

    pairs = orig;

}
