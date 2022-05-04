#include "Shape.h"
#include <iostream>


// Shape Constructor
Shape::Shape() { }


// Sets the shape's number that it can be referenced to
void Shape::setShapeNumber(int i) {
    this->shapeNumber = i;
}


// Returns the shape's number
int Shape::getShapeNumber() { return shapeNumber; }


// Prints the shape's points
void Shape::printShape() { }


// Moves the shape by the X and Y value in the parameters
void Shape::move(double x, double y) {
    for (Point* point : points) {
        point->setPoint(point->getX()+x,point->getY()+y);
    }
}


// Returns the shape's radius
double Shape::getRadiusOrLength() { return 0; }