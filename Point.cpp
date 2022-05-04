#include "Point.h"
#include <iostream>

using std::cout;


// Point Constructor
Point::Point(double x, double y) {
    this->x = x;
    this->y = y;
}


// Sets a point X and Y value
void Point::setPoint(double x, double y) {
    this->x = x;    // Sets the x value
    this->y = y;    // Sets the y value
}


// Returns the point's X value
double Point::getX() { return x; }


// Returns the point's Y value
double Point::getY() { return y; }


// Prints a point's X and Y coordinates
void Point::printPoint() {
    cout << "(" << x << ", " << y << ") ";
}