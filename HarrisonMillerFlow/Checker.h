#ifndef CHECKER_H_
#define CHECKER_H_

#include "Pair.h"
#include "Creature.h"
#include "AdjMatrix.h"
#include <vector>

/*
Used to test and evaluate a solution generated
by the genetic algorithm
*/
class Checker
{
public:
    Checker();

    //sets members
    Checker(int width,
        int height,
        std::vector<Pair> pairs,
        Creature creature);

    //creates a new adjacenecy matrix given a base one
    //then blocks all start/end nodes of pairs
    //and optionally blocks their used paths
    AdjMatrix adjMatrixFrom(AdjMatrix adj,
        Pair& pair,
        bool block = true);

    //tries to solve using the given solution
    //then evaluates the results
    void run();

    //a sepcial step used in the run function
    //that tries to connected unconnected pairs
    //then resolves the overlaps it creates
    void resolveOverlap(AdjMatrix& adj);

    //reorders the stored pairs given an original ordering
    void reorderPairs(std::vector<Pair> orig);

    //the fitness of the solution (also the creature used in the checker).
    int fitness;

    //needed for evaluating the fitness
    int width;
    int height;

    //both the data and solution for the given problem
    std::vector<Pair> pairs;

    //the *solution* given by the genetic algorithm
    Creature creature;

};

#endif /*CHECKER*/
