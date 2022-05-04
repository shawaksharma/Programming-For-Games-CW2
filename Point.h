#ifndef _POINT_H_
#define _POINT_H_

class Point {
    
    private:
        double x;
        double y;
        
    public:
        Point(double x = 0, double y = 0);
        void setPoint(double x, double y);
        double getX();
        double getY();
        void printPoint();
};

#endif
