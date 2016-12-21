#ifndef FITNESS_H_
#define FITNESS_H_

#include "Pair.h"

/*
Helper functions for evaluating solutions
*/

//returns width*height + pairs*width*height
int getGoalFitness(int width,
    int height,
    int pairs);

//evaluates the fitness of a given solution
//gets the number filled squares + connections*width*height
int getFitness(int width,
    int height,
    std::vector<Pair> pairs);

//returns the number of succesfull connections in the set of pairs
int getConnections(std::vector<Pair> pairs);

//returns width*height
int getSize(int width,
    int height);

//returns the number of squares filled by the pairs
int getFillFitness(std::vector<Pair> pairs);

#endif /*FITNESS*/
