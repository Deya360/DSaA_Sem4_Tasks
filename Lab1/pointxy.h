#ifndef POINTXY_H
#define POINTXY_H

#include <QtMath>

class PointXY {
public:
    PointXY() {}
    PointXY(double x, double y): xCoord(x), yCoord(y) {}
    PointXY(const PointXY &p2) {xCoord = p2.x(); yCoord = p2.y();}
    ~PointXY() {}

    bool operator== (const PointXY &rhs) const
                {return qFuzzyCompare(xCoord,rhs.x()) && qFuzzyCompare(yCoord,rhs.y());}

    double x() const {return xCoord;}
    double y() const {return yCoord;}


private:
    double xCoord;
    double yCoord;
};

#endif // POINTXY_H
