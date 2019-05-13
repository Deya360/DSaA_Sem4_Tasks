#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "pointxy.h"

class Triangle {
public:
    Triangle() {}

    Triangle(PointXY pnt1, PointXY pnt2, PointXY pnt3, double permtr) {
        p1=pnt1; p2=pnt2; p3=pnt3; perimeter = permtr;
    }

    Triangle(const Triangle &t2) {
        p1 = t2.getP1(); p2 = t2.getP2(); p3 = t2.getP3(); perimeter = t2.getPerimeter();
    }

    bool operator< (const Triangle &rhs) const {return perimeter < rhs.perimeter;}

    PointXY getP1() const {return p1;}
    PointXY getP2() const {return p2;}
    PointXY getP3() const {return p3;}
    double getPerimeter() const {return perimeter;}

private:
    PointXY p1, p2, p3;
    double perimeter;
};

#endif // TRIANGLE_H








