#ifndef POPULATION_H_
#define POPULATION_H_

#include "Creature.h"
#include <vector>

/*
Popuation of creatures, handles
creating a group of random creatures,
evolving the creatures, and selecting fittest creatures.
*/
class Population
{
public:
    Population();

    //creates a number size of creatures
    //each creature has x genes
    //and a special (problem specific set of genes defined by pairs).
    Population(int size,
        int geneLength,
        int pairs);

    Creature& getFittest();

    //uses a tournament selection method to get a
    //creature from the population
    Creature& select(int tournySize = 10);

    //creates a new population that uses crossover
    //and mutation operators to "evolve" the population
    Population evolve(int tournySize = 10,
        float rate = 0.015); //mutation rate

    bool elitism; //keep the fittest creature when evolving
    std::vector<Creature> creatures;

};

#endif /*POPULATION*/
