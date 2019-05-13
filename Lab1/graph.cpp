#include "graph.h"

Graph::Graph(int pC_MIN, int pC_MAX, double rX_MIN, double rX_MAX, double rY_MIN, double rY_MAX) {
    pointCount_MIN = (pC_MIN<4)? 4 : pC_MIN;
    pointCount_MAX = (pC_MAX<pC_MIN)? pC_MIN+1 : pC_MAX;
    rangeX_MIN = rX_MIN;
    rangeX_MAX = (rX_MAX<rX_MIN)? rX_MIN+1 : rX_MAX;;
    rangeY_MIN = rY_MIN;
    rangeY_MAX = (rY_MAX<rY_MIN)? rY_MIN+1 : rY_MAX;;
}

void Graph::generateRandomPoints() {
    std::random_device r;
    std::mt19937 eng{static_cast<long unsigned int>(time(nullptr))};;

    std::uniform_int_distribution<int> distPnt(pointCount_MIN, pointCount_MAX);
    std::uniform_real_distribution<double> distX(rangeX_MIN, rangeX_MAX);
    std::uniform_real_distribution<double> distY(rangeY_MIN, rangeY_MAX);

    int n = distPnt(eng);

    points.clear();
    for(int i = 0; i < n*1.5; i++) {
        double x = round(distX(eng)*2)/2;
        double y = round(distY(eng)*2)/2;

        PointXY p(x,y);
        if (!points.contains(p)) {
            points.push_back(p);
        }
        if (points.size()==n) break;
    }
}

void Graph::printPoints() {
    std::cout << "\n\nGenerating new graph...\n";

    for (auto const& p : points)
        std::cout << "X: " << std::left << std::setw(8) << std::fixed << std::setprecision(1)
                  << p.x() << " Y: " << p.y() << std::endl;
}

void Graph::findLargestTriangle_BruteForce() {
    double perimeter_MAX = 0;

    resT.clear();
    for (int k = 0; k < points.size(); k++) {
        for (int l = k+1; l < points.size(); l++) {
            for (int m = l+1; m < points.size(); m++) {
                double currentPerimeter = getPerimeter(points.at(k),points.at(l),points.at(m));
                if (currentPerimeter > perimeter_MAX) {
                    Triangle t(points.at(k),points.at(l),points.at(m), currentPerimeter);
                    resT.push_back(t);
                }
            }
        }
    }
    std::sort(resT.rbegin(),resT.rend());
}

double Graph::getPerimeter(PointXY p1, PointXY p2, PointXY p3) {
    double sideA = sqrt(pow(p2.x()-p1.x(),2) + pow(p2.y()-p1.y(),2));
    double sideB = sqrt(pow(p2.x()-p3.x(),2) + pow(p2.y()-p3.y(),2));
    double sideC = sqrt(pow(p1.x()-p3.x(),2) + pow(p1.y()-p3.y(),2));
    return checkValidity(sideA,sideB,sideC)? (sideA+sideB+sideC) : -1;
}

bool Graph::checkValidity(double a, double b, double c) {
    if (a + b <= c || a + c <= b || b + c <= a) return false;
    return true;
}

void Graph::plotPoints(qcpSubClass &w) {
    w.xAxis->setRange(rangeX_MIN-0.5,rangeX_MAX+0.5);
    w.yAxis->setRange(rangeY_MIN-0.5,rangeY_MAX+0.5);

    QVector<double> tempX, tempY;

    for(auto const& p : points) {
        tempX.push_back(p.x());
        tempY.push_back(p.y());
    }
    w.plotPoints(tempX,tempY);

}
