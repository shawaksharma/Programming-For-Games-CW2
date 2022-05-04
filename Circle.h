#ifndef _CIRCLE_H_
#define _CIRCLE_H_
#include "Shape.h"
#include <iostream>

using namespace std;

class Circle : public Shape {
    
    private:
        double radius;
        double x;
        double y;

    public:
        Circle(double radius = 1, double x = 0, double y = 0);
        Point centre;
        double getRadiusOrLength();
        void printShape();
};

#endif