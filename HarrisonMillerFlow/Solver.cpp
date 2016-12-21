#include "Solver.h"
#include "Fitness.h"
#include "AdjMatrix.h"
#include <iostream>
#include <thread>

Solver::Solver() :
    goal(0),
    width(0),
    height(0),
    debug(false)
{
}

Solver::Solver(int width,
    int height,
    std::vector<Pair> pairs) :
    width(width),
    height(height),
    pairs(pairs),
    debug(false)
{
    goal = getGoalFitness(width, height, pairs.size());

}

int Solver::getGeneLength()
{
    //this assumes the minimum grid size is 2x2
    //the gene length is the number of valid connections between nodes in a 2d grid
    int wm2 = width-2;
    int hm2 = height-2;

    //nodes in the middle have 4 connections
    //nodes in the sides have 3 connections * 2 for each side
    //8 is the number of connections for the 4 corners
    //width/height have to subtracted from them so we aren't accounting for the corners
    return wm2*hm2*4 + wm2*6 + hm2*6 + 8;

}

//gcd function used in one place below
int gcd(int a,
    int b)
{
    if(a == 0) return b;
    return gcd(b%a, a);

}

bool Solver::solve(int size,
    int gen,
    int tournySize,
    float rate)
{
    int geneLength = getGeneLength();

    //used to determine how many checkers to run at a time
    //we don't want to go above the number of threads
    //because you'll start to lose performance if you go over
    int nthreads = std::thread::hardware_concurrency();

    //I do this because I don't have a remainder loop below
    if(size%nthreads != 0)
    {
        nthreads = gcd(size, nthreads);

    }

    //print some nice debug info if applicable
    if(debug)
    {
        std::cout << "starting solver\n\n";

        std::cout << "threads available: " << nthreads << "\n\n";

        std::cout << "gene length: " << geneLength << "\n";
        std::cout << "population: " << size << "\n";
        std::cout << "generations: " << gen << "\n";
        std::cout << "tournament size: " << tournySize << "\n";
        std::cout << "mutation rate: " << (int)(rate*100.0f) << "%\n\n";

        std::cout << "goal fitness: " << goal << "\n\n";

    }

    //create initial population
    pop = Population(size, geneLength, pairs.size());

    for(int i = 0; i < gen; i++)
    {
        Creature best;
        best.fitness = -1000000;

        //create all the checkers
        //increment by the number of threads available
        for(int j = 0; j < pop.creatures.size(); j+= nthreads)
        {

            std::vector<std::thread> threads;
            std::vector<Checker> checkers;

            threads.reserve(nthreads);
            checkers.reserve(nthreads);

            //create nthreads checkers
            for(int k = 0; k < nthreads; k++)
            {
                Checker checker(width, height, pairs, pop.creatures[j+k]);
                checkers.push_back(checker);

            }

            //run all the checkers in threads
            for(int k = 0; k < checkers.size(); k++)
            {
                threads.push_back(std::thread(&Checker::run, &checkers[k]));

            }

            //join all the threads and get the info back
            //purely using joining isn't the most efficient
            //if I had time I could use asyncs and futures to fully
            //utilize the threads so they are always doing work
            for(int k = 0; k < threads.size(); k++)
            {
                threads[k].join();

                //update the creature associated with the checker
                pop.creatures[j+k] = checkers[k].creature;

                //check if this a better solution in the current generation
                if(checkers[k].fitness > best.fitness)
                {
                    best = checkers[k].creature;

                }

                //check if this a better overall solution
                if(checkers[k].fitness > bestSolution.fitness)
                {
                    bestSolution = checkers[k];

                }

            }

            //if this solution is succesfull lets stop!
            if(bestSolution.fitness >= goal) //I use >= for debug purposes
            {
                return true;

            }

        }

        //print info about the generation
        if(debug)
        {
            std::cout << "generation #" << (i+1) << " best fitness: " << best.fitness << "\n";

        }

        pop = pop.evolve(tournySize, rate);

    }

    return false;

}

void Solver::print()
{
    if(bestSolution.fitness >= goal)
    {
        //prints all the pairs if the solution to the problem was found
        for(int i = 0; i < bestSolution.pairs.size(); i++)
        {
            Pair& pair = bestSolution.pairs[i];
            pair.print();

        }

    }
    else
    {
        //print unsolvable if no full solution was found
        std::cout << "unsolvable\n";

        //if debug is turned out print a partial solution
        if(debug)
        {
            std::cout << "\n";
            for(int i = 0; i < bestSolution.pairs.size(); i++)
            {
                Pair& pair = bestSolution.pairs[i];
                pair.print();

            }

        }

    }

}

