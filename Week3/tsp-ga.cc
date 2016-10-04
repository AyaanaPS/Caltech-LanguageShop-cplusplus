#include "tsp-ga.hh"
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <set>

using namespace std;

/* This file contains the definitions for the member functions of the 
 * TSPGenome class, as well as for a few non-member functions.
 */

 /* This constructor takes in a number of points and fills the order with
  * the number 0 to num-1. It then randomly shuffles the order. It also sets
  * the circuitLength to a dummy variable.
  */
TSPGenome::TSPGenome(int numPoints)
{
    for(int i = 0; i < numPoints; i++)
    {
        order.push_back(i);
    }

    random_shuffle(order.begin(), order.end());
    circuitLength = 1e9;
}

/* This constructor takes in an order vector and intializes the data based
 * on the inputted order.
 */
TSPGenome::TSPGenome(const vector<int> &order)
{
    this->order = order;
    circuitLength = 1e9;
}

/* This function simply returns the order for that object. */
vector<int> TSPGenome::getOrder() const
{
    return order;
}

/* This function computes the circuitLength given a vector of points. */
void TSPGenome::computeCircuitLength(const vector<Point> &points)
{
    double totalDistance = 0;
    for(int i = 0; i < order.size() - 1; i++) {
        Point p1 = points[order[i]];
        Point p2 = points[order[i+1]];
        totalDistance += p1.distanceTo(p2);
    }

    totalDistance += points[order[order.size() - 1]].distanceTo(
        points[order[0]]);
    circuitLength = totalDistance;
}

/* This function just returns the circuitLength for that object */
double TSPGenome::getCircuitLength() const
{
    return circuitLength;
}

/* This function mutates the order by swapping two randomly selected values
 * in the order vector. */
void TSPGenome::mutate()
{
    int index1 = rand() % order.size();
    int index2 = rand() % order.size();
    while(index1 == index2)
    {
        index2 = rand() % order.size();
    }

    int temp = order[index1];
    order[index1] = order[index2];
    order[index2] = temp;
}

/* This function merges two 'genomes' together and returns the 
 * resulting TSPGenome */
TSPGenome* crosslink(const TSPGenome &g1, const TSPGenome &g2)
{
    vector<int> newOrder;
    vector<int> firstOrder = g1.getOrder();
    vector<int> secondOrder = g2.getOrder();
    int i = rand() % g1.getOrder().size();
    for (int m = 0; m < i; m++)
    {
        newOrder.push_back(firstOrder[m]);
    }

    for (int k = 0; k < secondOrder.size(); k ++)
    {
        if (find(newOrder.begin(), newOrder.end(), 
            secondOrder[k]) == newOrder.end())
        {
            newOrder.push_back(secondOrder[k]);
        }
    }

    TSPGenome* child = new TSPGenome(newOrder);
    return child;

}

/* This function compares two genomes. It returns true if the circuitLength
 * of the first is less than that of the second. Else, it returns false.
 */
bool isShorterPath(const TSPGenome &g1, const TSPGenome &g2)
{
    double circLen1 = g1.getCircuitLength();
    double circLen2 = g2.getCircuitLength();

    return circLen1 < circLen2;
}

/* This function finds a short path using the TSPGenomes.
 * It takes in a vector indicating the poitns being looked at, a population
 * size, the number of generations to run for, the number of genomes to 
 * keep each generation and the number of mutations. 
 */

TSPGenome findAShortPath(const vector<Point> &points, int populationSize, 
    int numGenerations, int keepPopulation, int numMutations)
{
    int genomeSize = points.size();
    int i = 0;
    vector<TSPGenome> population;

    /* This first generates genomes and adds them to the population vector. */
    while (i < populationSize)
    {
        TSPGenome *newTSP = new TSPGenome(genomeSize);
        population.push_back(*newTSP);
        i++;
    }

    /* This runs for the number of generations inputted */
    int y = 0;
    while(y < numGenerations)
    {
        for(int x = 0; x < populationSize; x++)
        {
            population[x].computeCircuitLength(points);
        }
        /* The current population vector is sorted using the isShorterPath
         * comparison function.
         */
        sort(population.begin(), population.end(), isShorterPath);

        /* Every 10 generations, the fitness of the best solution is printed
         * out.
         */
        if (y % 10 == 0) 
        {
            cout << "Generation " << y << ": shortest path is " << 
                population[0].getCircuitLength() << endl;
        }

        /* This replaces the less fit genomes in the population (genomes that
         * are not withing the keepPopulation limit.
         */
        for(int m = keepPopulation; m < populationSize; m++)
        {
            int g1 = rand() % keepPopulation;
            int g2 = rand() % keepPopulation;
            while(g1 == g2) 
            {
                g2 = rand() % keepPopulation;
            }

            population[m] = *crosslink(population[g1], population[g2]);
        }

        /* This applies mutations to the population. It runs while there are 
         * still mutations to be made. It never mutates the first genome, as 
         * that is the most fit genome found so far. */
        int z = 0;
        while (z < numMutations)
        {
            int mutateIndex = 1 + rand() % (populationSize - 1);
            population[mutateIndex].mutate();
            z++;
        }

        y++;
    }

    /* After all the generations have been run through, return the first 
     * genome in the population as that is the most fit genome encountered
     * in all the generations.
     */
    return population[0];
}
