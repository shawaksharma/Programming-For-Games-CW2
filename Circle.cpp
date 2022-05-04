#include "Circle.h"


// Circle Constructor
Circle::Circle(double radius, double x, double y) {
    this->radius = radius;  // Sets radius of circle
    shapeType = ShapeType::CIRCLE;  // Sets the type of shape
    centre.setPoint(x, y);  // Sets the centre of the circle
    points = {&centre}; // Adds the centre to the shape's points
}


// Returns the radius of the circle
double Circle::getRadiusOrLength() { return radius; }


// Prints the centre and radius of the circle
void Circle::printShape() {
    cout << "| Circle | Centre = ";
    centre.printPoint();
    cout << "| Radius = " << getRadiusOrLength() << " |";
}