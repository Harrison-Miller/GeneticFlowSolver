#ifndef CREATURE_H_
#define CREATURE_H_

#include <vector>

/*
Represents a *solution* to a problem.
allows for mutation of solution and cross over operations
*/
class Creature
{
public:
    Creature();

    //creates a random creature with genes of length
    Creature(int length,
        int pairs); //used for order/resolveOrder (non-modular).

    //crossover constructor
    //creates a new creature with genes from a and b
    Creature(Creature& a,
        Creature& b);

    //goes through each element and mutates it if the chance is met
    void mutate(float rate = 0.015);

    //prints genes (ignoring order/resolveOrder since they aren't part of the modular code).
    void print();

    int fitness; //fitness must be manually set from outside the class

    //if these two were taken out + pairs in population
    //the code for creature/population would be modular
    //for use in other code.
    std::vector<int> order; //used to reorder pairs when solving for initial paths
    std::vector<int> resolveOrder; //used to reorder pairs when resolving overlapping paths

    std::vector<bool> genes;

};

#endif /*CREATURE*/
