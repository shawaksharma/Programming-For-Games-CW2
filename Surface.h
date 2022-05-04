#ifndef _SURFACE_H_
#define _SURFACE_H_
#include <vector>
#include "Shape.h"
using namespace std;

class Surface {
    
    private:
        int height;
        int width;

    public:
        Surface(double height, double width);
        double getWidth();
        double getHeight();
        vector<Shape*> shapes;
        void addShape(Shape* shape);
        void removeShape(Shape* shape);
        bool shapeInBounds(Shape* shape);
        void printShapes();
        void playGame();
        void moveShapesRandomly();
        void checkOverlap();

};

#endif