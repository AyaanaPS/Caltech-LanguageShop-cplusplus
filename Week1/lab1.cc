#include <iostream>
#include "Point.hh"
#include <cmath>
using namespace std;

/*
 * This function computes the area of the triangle generated by 3 3D points.
 * This is computed using Heron's formula. The formula is 
 * A = sqrt(s * (s - a) * (s - b) * (s - c)), where a, b and c are the side
 * lengths of the generated triangle (i.e. the distances between each pair
 * of points) and s is the semiperimeter, given by:
 * s = (a + b + c)/2. The function returns the area.
 */

double computeArea(Point &a, Point &b, Point &c)
{
    double side1 = a.distanceTo(b);
    double side2 = a.distanceTo(c);
    double side3 = b.distanceTo(c);

    double semiP = (side1 + side2 + side3) / 2;

    double mult = semiP * (semiP - side1) * (semiP - side2) * (semiP - side3);

    double area = sqrt(mult);

    return area;

}

int main()
{

    /* Variable Declarations */

    double coord1;
    double coord2;
    double coord3;

    /* Gaining the input and generating each point */

    cout << "Enter coordinates for Point 1 separated by a space: ";
    cin >> coord1 >> coord2 >> coord3;
    Point p1 = Point(coord1, coord2, coord3);

    cout << "Enter coordinates for Point 2 separated by a space: ";
    cin >> coord1 >> coord2 >> coord3;
    Point p2 = Point(coord1, coord2, coord3);

    cout << "Enter coordinates for Point 3 separated by a space: ";
    cin >> coord1 >> coord2 >> coord3;
    Point p3 = Point(coord1, coord2, coord3);

    /* This prints the information in the desired format */
    
    cout << "Point 1: " << p1.getX() << " " << p1.getY() << " " << p1.getZ() <<  
        endl;
    cout << "Point 2: " << p2.getX() << " " << p2.getY() << " " << p2.getZ() << 
        endl;
    cout << "Point 3: " << p3.getX() << " " << p3.getY() << " " << p3.getZ() << 
        endl;
    cout << "Area is: " << computeArea(p1, p2, p3) << endl;

}
