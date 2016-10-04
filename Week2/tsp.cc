#include <algorithm>
#include <iostream>
#include <vector>
#include "Point.hh"
using namespace std;

/* 
 * This function computes the length of the circuit. The circuit is given by
 * the points inputted in the points vector in the order specified by the 
 * inputted order vector. This uses the distanceTo function from the Point
 * class written last week. It includes the distance from the last point back
 * to the first.
 * The function returns a double representing the total distance.
 */

double circuitLength(const vector<Point> &points, const vector<int> &order) {
    double totalDistance = 0;
    for(int i = 0; i < order.size() - 1; i++) {
        Point p1 = points[order[i]];
        Point p2 = points[order[i+1]];
        totalDistance += p1.distanceTo(p2);
    }

    totalDistance += points[order[order.size() - 1]].distanceTo(
        points[order[0]]);
    return totalDistance;
}

/* 
 * This function computes the shortestPath of the given points. 
 * This is done by running through every possible permutation of the points 
 * and checking if the circuitLength of that particular order is the minimum.
 * If it is, the order is saved and returned.
 */

vector<int> findShortestPath(const vector<Point> &points) {
    double minLength = 100000000;
    double tempLength = 0;
    vector<int> savedOrder;

    vector<int> order;

    for(int i = 0; i < points.size(); i++) {
        order.push_back(i);
    }

    do {
        tempLength = circuitLength(points, order);
        if (tempLength < minLength) {
            minLength = tempLength;
            savedOrder = order;
        }
    } while(next_permutation(order.begin(), order.end()));

    return savedOrder;

}

/* 
 * The main function fills the points vector with inputted points.
 * It then calls the findShortestPath function to get the bestOrder.
 * It then uses this order and the vector of points to get the circuit
 * Length of the best Order. This information is printed in the format
 * designated in the problem set.
 */
 
int main()
{
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
        Point p = Point(coord1, coord2, coord3);
        points.push_back(p);
    }
    
    bestOrder = findShortestPath(points);
    cout << "Best Order: [";
    for(int i = 0; i < bestOrder.size(); i++) {
        cout << bestOrder[i] << " ";
    }
    cout << "]" << endl;

    cout << "Shortest distance: " << circuitLength(points, bestOrder) << endl;

}
