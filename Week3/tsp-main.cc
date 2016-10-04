#include "tsp-ga.hh"
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

/* This function is used in the main function. It serves to print out a 
 * usage statement in case of any errors with the command line arguments.
 */

void printUsage(char *name)
{
    cerr << "Usage: " << name << "POPULATION [positive int] "
        "GENERATION [positive int] KEEP [floating-point 0-1] "
        "MUTATE [positive floating-point]" << endl;
}

/* This is the main function of the program */
int main(int argc, char **argv)
{
    /* First, the command line arguments are parsed and checked */
    if(argc != 5)
    {
        printUsage(argv[0]);
    }

    if(atoi(argv[1]) < 0 || atoi(argv[2]) < 0)
    {
        printUsage(argv[0]);
    }
    int popSize = atoi(argv[1]);
    int generations = atoi(argv[2]);

    if(atoi(argv[3]) < 0 || atoi(argv[3]) > 1 || atoi(argv[4]) < 0)
    {
        printUsage(argv[0]);
    }

    int keepPopulation = int(atof(argv[3]) * popSize);
    int numMutations = int(atof(argv[4]) * popSize);

    /* The number of points is found and a points vector is generated
     * using user input.
     */
    int numPoints;
    double coord1; 
    double coord2;
    double coord3;
    vector<Point> points;
    vector<int> bestOrder;

    cout  << "How many points? ";
    cin >> numPoints;

    for(int i = 0; i < numPoints; i++) {
        cout << "Point " << i << ": ";
        cin >> coord1 >> coord2 >> coord3;
        cout << "" << endl;
        Point p = Point(coord1, coord2, coord3);
        points.push_back(p);
    }

    srand(time(nullptr));
    /* The findAShortPath function is then called and it's result is stored. */
    TSPGenome bestGenome = findAShortPath(points, popSize, generations, 
        keepPopulation, numMutations);
    
    /* The results are then printed out */

    bestOrder = bestGenome.getOrder();
    bestGenome.computeCircuitLength(points);
    double circuitLength = bestGenome.getCircuitLength();
    
    cout << "Best Order: [";
    for(int i = 0; i < bestOrder.size(); i++) {
        cout << bestOrder[i] << " ";
    }
    cout << "]" << endl;
    cout << "Shortest distance: " << circuitLength << endl;

}
