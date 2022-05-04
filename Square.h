#ifndef _SQUARE_H_
#define _SQUARE_H_
#include "Shape.h"
#include <iostream>

class Square : public Shape {
    
    private:
        double length;
        double x;
        double y;

    public:
        Square(double length = 1, double x = 0, double y = 0);
            Point bottomLeft;
            Point topLeft;
            Point topRight;
            Point bottomRight;
            double getRadiusOrLength();
            void printShape();
};

#endif