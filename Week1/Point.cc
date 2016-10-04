#include "Point.hh"
#include <cmath>
#include <iostream>
using namespace std;


// Default constructor:  initializes the point to (0, 0, 0).
Point::Point() {
  x_coord = 0;
  y_coord = 0;
  z_coord = 0;
}

// Initializes the point to (x, y, z).
Point::Point(double x, double y, double z) {
  x_coord = x;
  y_coord = y;
  z_coord = z;
}

// Destructor - Point allocates no dynamic resources.
Point::~Point() {
  // no-op
}

// Mutators:

void Point::setX(double val) {
  x_coord = val;
}

void Point::setY(double val) {
  y_coord = val;
}

void Point::setZ(double val) {
  z_coord = val;
}
// Accessors:

double Point::getX() {
  return x_coord;
}

double Point::getY() {
  return y_coord;
}

double Point::getZ() {
  return z_coord;
}

/* This function calculates the distance between this point
 * and an inputted point using the formula
 * sqrt of (x2 - x1)^2 - (y2 - y1)^2 - (z2 - z`)^2
 */

double Point::distanceTo(Point &p2) {

  double x_part = (p2.getX() - x_coord) * (p2.getX() - x_coord);
  double y_part = (p2.getY() - y_coord) * (p2.getY() - y_coord);
  double z_part = (p2.getZ() - z_coord) * (p2.getZ() - z_coord);

  double result = sqrt(x_part + y_part + z_part);

  return result;
}
