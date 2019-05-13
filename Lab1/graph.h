#ifndef GRAPH_H
#define GRAPH_H

#include "qcpsubclass.h"
#include "customlinkedlist.h"

#include <QVector>
#include <iostream>
#include <time.h>
#include <iomanip>
#include <QWidget>


class Graph {
public:
    Graph(int pC_MIN, int pC_MAX, double rX_MIN, double rX_MAX, double rY_MIN, double rY_MAX);
    void generateRandomPoints();
    void printPoints();
    void findLargestTriangle_BruteForce();
    void plotPoints(qcpSubClass &w);
    double getPerimeter(PointXY p1, PointXY p2, PointXY p3);
    bool checkValidity(double a, double b, double c);

    int getPointCount_MIN() const {return pointCount_MIN;}
    int getPointCount_MAX() const {return pointCount_MAX;}

    double getRangeX_MIN() const {return rangeX_MIN;}
    double getRangeX_MAX() const {return rangeX_MAX;}
    double getRangeY_MIN() const {return rangeY_MIN;}
    double getRangeY_MAX() const {return rangeY_MAX;}

    CustomLinkedList<PointXY> getPoints() const {return points;}
    QVector<Triangle> getResT() const {return resT;}

private:
    CustomLinkedList<PointXY> points;
    QVector<Triangle> resT;

    int pointCount_MIN;
    int pointCount_MAX;

    double rangeX_MIN;
    double rangeX_MAX;
    double rangeY_MIN;
    double rangeY_MAX;

    QVector<PointXY> pointsA;
};

#endif // GRAPH_H
