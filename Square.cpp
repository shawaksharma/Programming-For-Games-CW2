#include "Square.h"


// Square Constructor
Square::Square(double length, double x, double y) {
    this->length = length;  // Sets length of square
    shapeType = ShapeType::SQUARE;  // Sets the type of shape

    // Sets the four points of the square
    bottomLeft.setPoint(x, y);
    topLeft.setPoint(x,y+length);
    topRight.setPoint(x+length, y+length);
    bottomRight.setPoint(x+length, y);

    // Adds the points of the square to shape's points
    points = {&bottomLeft, &topLeft, &topRight, &bottomRight};
};


//  Returns the radius of the circle
double Square::getRadiusOrLength() {
    return length;
}


// Prints the points and length of the square
void Square::printShape() {
    cout << "| Square | Points = ";
    for (Point* point : points) {
        point->printPoint();
    }
    cout << "| Length = " << getRadiusOrLength() << " |";
}