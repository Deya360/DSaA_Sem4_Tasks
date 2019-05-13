#include"qcpSubClass.h"

qcpSubClass::qcpSubClass(QWidget *parent):QCustomPlot(parent) {
    if(!mouseMarkerX) mouseMarkerX = new QCPItemStraightLine(this);
    if(!mouseMarkerY) mouseMarkerY = new QCPItemStraightLine(this);

    crosshairpen.setColor(Qt::darkGray);
    mouseMarkerX->setPen(crosshairpen);
    mouseMarkerY->setPen(crosshairpen);
    setMousePosition(0, 0);
}


void qcpSubClass::setMousePosition(double positionX, double positionY) {
    if(mouseMarkerX && mouseMarkerY) {
        mouseMarkerX->point1->setCoords(positionX, 0);
        mouseMarkerX->point2->setCoords(positionX, 1);
        mouseMarkerY->point1->setCoords(0, positionY);
        mouseMarkerY->point2->setCoords(1, positionY);
    }
    replot();
}

void qcpSubClass::mousePressEvent(QMouseEvent *event) {
    double x = xAxis->pixelToCoord(event->pos().x());
    double y = yAxis->pixelToCoord(event->pos().y());
    setMousePosition(x,y);

    double key = 0;
    double value = 0;
    bool ok = false;
    double maxx = std::numeric_limits<double>::max();
    double maxy = std::numeric_limits<double>::max();

    QCPDataRange dataRange = curve->data()->dataRange();
    QCPCurveDataContainer::const_iterator begin = curve->data()->at(dataRange.begin());
    QCPCurveDataContainer::const_iterator end = curve->data()->at(dataRange.end());

    int n = end-begin;
    if (n>0) {
        double *dx = new double[n];
        double *dy = new double[n];

        int index =0;
        for (QCPCurveDataContainer::const_iterator it=begin; it<end; it++) {
            dx[index] = qAbs(x - it->key);
            dy[index] = qAbs(y - it->value);
            if ((dx[index] < 0.5) && (dx[index] < maxx) && (dy[index] < 0.5) && (dx[index] < maxy)) {
                key = it->key;
                value = it->value;
                ok = true;
                maxx = dx[index];
                maxy = dy[index];
            }
            index++;
        }

        delete[] dy;
        delete[] dx;

        if (ok) {
            QToolTip::showText(event->globalPos(),
            tr("<table><tr><td><b>X:</b></td> <td><b>%L1</b></td></tr>"
                 "<tr><td><b>Y:</b></td> <td><b>%L2</b></td></tr></table>").arg(key).arg(value));

        } else {
            QToolTip::showText(event->globalPos(),
            tr("<table><tr><td>X:</td> <td>%L1</td></tr>"
                "<tr><td>Y:</td> <td>%L2</td></tr></table>").arg(x).arg(y));
        }
    }
}

void qcpSubClass::plotPoints(QVector<double> xData, QVector<double> yData) {
    if(!curve) {
        xAxis->setLabel("x");
        yAxis->setLabel("y");

        curve = new QCPCurve(xAxis,yAxis);
        curve->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc,Qt::red,8));
        curve->setLineStyle(QCPCurve::lsLine);
    }

    curve->data().data()->clear();
    curve->setData(xData,yData);
    replot();
}

void qcpSubClass::plotTriangle(QVector<Triangle> tri, int index) {
    if(!curveTri) {
        curveTri = new QCPCurve(xAxis,yAxis);
        curveTri->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc,Qt::magenta,10));
        curveTri->setLineStyle(QCPCurve::lsLine);
        curveTri->setBrush(QBrush(QColor(255,255,224,128)));
        curveTri->setPen(QPen(Qt::green,4));
    }

    curveTri->data().data()->clear();
    curveTri->addData(tri.at(index).getP1().x(),tri.at(index).getP1().y());
    curveTri->addData(tri.at(index).getP2().x(),tri.at(index).getP2().y());
    curveTri->addData(tri.at(index).getP3().x(),tri.at(index).getP3().y());
    curveTri->addData(tri.at(index).getP1().x(),tri.at(index).getP1().y());

    replot();
}

