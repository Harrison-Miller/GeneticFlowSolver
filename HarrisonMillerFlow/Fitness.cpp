#include "Fitness.h"

int getGoalFitness(int width,
    int height,
    int pairs)
{
    int size = width*height;
    return size + pairs*size;

}

int getFitness(int width,
    int height,
    std::vector<Pair> pairs)
{
    int size = getSize(width, height);

    int filled = 0;
    int connections = 0;

    //do this all in one loop
    for(int i = 0; i < pairs.size(); i++)
    {
        Pair& pair = pairs[i];
        filled += pair.getFilled();
        if(pair.isConnected())
        {
            connections++;

        }

    }

    return filled + connections*size;

}

int getConnections(std::vector<Pair> pairs)
{
    int connections = 0;
    for(int i = 0; i < pairs.size(); i++)
    {
        if(pairs[i].isConnected())
        {
            connections++;

        }

    }

    return connections;

}

int getSize(int width, int height)
{
    return width*height;

}

int getFillFitness(std::vector<Pair> pairs)
{
    int filled = 0;
    for(int i = 0; i < pairs.size(); i++)
    {
        filled += pairs[i].getFilled();

    }

    return filled;

}

