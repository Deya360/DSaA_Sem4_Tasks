#ifndef QCPSUBCLASS_H
#define QCPSUBCLASS_H

#include "qcustomplot.h"
#include "triangle.h"
#include <QWidget>

namespace Ui {
    class Form;
}

class qcpSubClass : public QCustomPlot {
    Q_OBJECT

public:
    qcpSubClass(QWidget*);

    void setMousePosition(double, double);
    void plotPoints(QVector<double> xData, QVector<double> yData);
    void plotTriangle(QVector<Triangle> tri, int index);

    void mousePressEvent(QMouseEvent *event);
    void curveTri_vis(bool visible) {curveTri->setVisible(visible); replot();}

private:
    QPointer<QCPItemStraightLine> mouseMarkerX;
    QPointer<QCPItemStraightLine> mouseMarkerY;
    QPen crosshairpen;

    QCPCurve *curve, *curveTri;
};

#endif // QCPSUBCLASS_H
