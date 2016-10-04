#include <vector>
#include "Point.hh"
using namespace std;

/* This is the header fille for the traveling salesman, genetic algorithm
 * problem. It contains the class, member function and other function header.
 */


/* This is the header for the TSPGenome class */

class TSPGenome
{
    /* The class has two private data members. The first is a vector of
     * integers, representing the order that the points are visited. The second
     * is a double that holds the total circuit length.
     */

    private:
        vector<int> order;
        double circuitLength;

    /* These are the various operations that the class can perform */
    public:

        /* The class has two constructors. The first simply takes the number
         * of points that need to be considered. The second, takes an initial
         * order. 
         */

        TSPGenome(int numPoints);
        TSPGenome(const vector<int> &order);

        /* These are the accessor functions to return the data members */
        vector<int> getOrder() const;
        double getCircuitLength() const;

        /* These are the mutator functions, which change the value of order
         * and circuitLength respectively.
         */
        void computeCircuitLength(const vector<Point> &points);
        void mutate();

};


TSPGenome* crosslink(const TSPGenome &g1, const TSPGenome &g2);

bool isShorterPath(const TSPGenome &g1, const TSPGenome &g2);

TSPGenome findAShortPath(const vector<Point> &points, int populationSize, 
    int numGenerations, int keepPopulation, int numMutations);
