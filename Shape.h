#ifndef _SHAPE_H_
#define _SHAPE_H_
#include "Point.h"
#include <vector>

using namespace std;

enum class ShapeType {

    SQUARE, 
    CIRCLE
};

class Shape {

    private:
        int shapeNumber;
        
    public:
        Shape();
        int getShapeNumber();
        void setShapeNumber(int i);
        void move(double x, double y);
        virtual void printShape();
        vector<Point*> points;
        ShapeType shapeType;
        virtual double getRadiusOrLength();
};

#endif