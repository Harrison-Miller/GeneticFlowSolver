#include "Creature.h"
#include <cstdlib> //rand
#include <iostream> //cout

Creature::Creature() :
    fitness(0)
{
}

Creature::Creature(int length,
    int pairs) :
    fitness(0)
{
    for(int i = 0; i < length; i++)
    {
        bool gene = (rand()%2 == 0);
        genes.push_back(gene);

    }

    //order needs exactly one index for each pair
    for(int i = 0; i < pairs; i++)
    {
        order.push_back(i);

    }

    //mix the order up
    for(int i = 0; i < order.size(); i++)
    {
        int x = rand()%order.size();
        int y = rand()%order.size();

        int o = order[x];
        order[x] = order[y];
        order[y] = o;

    }

    //this is pretty much the same as
    //order just used in a differnet place
    for(int i = 0; i < pairs; i++)
    {
        resolveOrder.push_back(i);

    }

    for(int i = 0; i < resolveOrder.size(); i++)
    {
        int x = rand()%resolveOrder.size();
        int y = rand()%resolveOrder.size();

        int o = resolveOrder[x];
        resolveOrder[x] = resolveOrder[y];
        resolveOrder[y] = o;

    }

}

Creature::Creature(Creature& a,
    Creature& b) :
    fitness(0)
{
    for(int i = 0; i < a.genes.size(); i++)
    {
        //get a gene from either a or b
        bool gene = rand()%2 == 0 ? a.genes[i] : b.genes[i];
        genes.push_back(gene);

    }

    //order/resolveOrder are treated as 1 gene
    order = rand()%2 == 0 ? a.order : b.order;
    resolveOrder = rand()%2 == 0 ? a.resolveOrder : b.resolveOrder;

}

void Creature::mutate(float rate)
{
    for(int i = 0; i < genes.size(); i++)
    {
        //this has some statistical issues but it's mostly ok in this scenario
        bool m = ((float)(rand()%1000)/1000.0f) <= rate;
        //since the gene is boolean inverting it is sufficient for mutation
        genes[i] = m ? !genes[i] : genes[i];

    }

    bool m = false;

    m = ((float)(rand()%1000)/1000.0f) <= rate;
    if(m)
    {
        //swap two elements in the order
        int x = rand()%order.size();
        int y = rand()%order.size();
        int o = order[x];
        order[x] = order[y];
        order[y] = o;

    }

    m = ((float)(rand()%1000)/1000.0f) <= rate;
    if(m)
    {
        //swap two elements for the resolveOrder
        int x = rand()%resolveOrder.size();
        int y = rand()%resolveOrder.size();
        int o = resolveOrder[x];
        resolveOrder[x] = resolveOrder[y];
        resolveOrder[y] = o;

    }

}

void Creature::print()
{
    //print out the genes
    //we don't care about the order/resolveOrder here since they are just for this problem
    for(int i = 0; i < genes.size(); i++)
    {
        std::cout << genes[i];

    }

    std::cout << "\n";

}
