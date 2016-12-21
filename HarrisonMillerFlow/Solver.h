#ifndef SOLVER_H_
#define SOLVER_H_

#include "Pair.h"
#include "Population.h"
#include "Checker.h"

/*
Uses a genetic algorithm and dijkstras algorithm
to try and solve a numblerlink/flow puzzle
*/
class Solver
{
public:
    Solver();

    //sets members
    Solver(int width,
        int height,
        std::vector<Pair> pairs);

    //returns the number of valid connections in the grid
    int getGeneLength();

    //runs the genetic algorithm and uses checkers
    //to evaluate solution fitness
    //this is done in threading to improve performance
    bool solve(int size = 200, //population size
        int gen = 20, //number of generations
        int tournySize = 10, //tournament size
        float rate = 0.03); //mutation rate

    //prints the found solution or "unsolvable"
    void print();

    //the goal fitness given width, height, pairs
    int goal;

    int width;
    int height;

    //the initial data for the numblerlink/flow puzzle
    std::vector<Pair> pairs;

    //the creature/individual population for the genetic algorithm
    Population pop;

    //the best solution found for the problem
    Checker bestSolution;

    //print extra information besides the solution or "unsolvable".
    bool debug;

};

#endif /*SOLVER*/
