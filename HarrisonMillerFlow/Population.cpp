#include "Population.h"
#include <cstdlib> //rand

Population::Population() :
    elitism(false)
{
}

Population::Population(int size,
    int geneLength,
    int pairs) :
    elitism(false)
{
    //generate all a random set of creatures
    for(int i = 0; i < size; i++)
    {
        Creature c(geneLength, pairs);
        creatures.push_back(c);

    }

}

Creature& Population::getFittest()
{
    int index = 0;
    for(int i = 1; i < creatures.size(); i++)
    {
        if(creatures[i].fitness > creatures[index].fitness)
        {
            index = i;

        }

    }

    return creatures[index];

}

Creature& Population::select(int tournySize)
{
    //tournament select function.
    int index = -1;
    for(int i = 0; i < tournySize; i++) //test tournySize random creatures
    {
        int j = rand()%creatures.size();
        if(index == -1)
        {
            //this is kind of a poor way of doing this
            //but I wanted to be consistent with above (using an index).
            index = j;

        }
        else if(creatures[j].fitness > creatures[index].fitness)
        {
            index = j;

        }

    }

    return creatures[index];

}

Population Population::evolve(int tournySize,
    float rate)
{
    Population p;
    p.elitism = elitism; //pass on important information

    int offset = 0;

    if(elitism)
    {
        //keep the fittest creature in tact for the next population
        Creature e = getFittest();
        p.creatures.push_back(e);
        offset = 1;

    }

    for(int i = offset; i < creatures.size(); i++)
    {
        Creature& a = select(tournySize);
        Creature& b = select(tournySize);

        //creates a creature that randomly selects genes from either a or b
        p.creatures.push_back(Creature(a, b));

    }

    //mutate all the creatures (low percentage chance).
    for(int i = offset; i < p.creatures.size(); i++)
    {
        p.creatures[i].mutate(rate);

    }

    return p;

}
