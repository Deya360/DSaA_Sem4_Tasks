#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) : QWidget(parent), ui(new Ui::Form) {
    ui->setupUi(this);

    g = new Graph(4,9,0,15,0,15);
    populateGraph();
    populateCmb();
    ui->plot->curveTri_vis(false);
}

Form::~Form() {
    delete ui;
}

void Form::populateGraph() {
    g->generateRandomPoints();
    g->printPoints();
    g->plotPoints(*ui->plot);
    g->findLargestTriangle_BruteForce();
}

void Form::populateCmb() {
    QVector<Triangle> data = g->getResT();
    if(ui->resCb->count()>1) ui->resCb->clear();
    int n = (data.size() > 10)? 10 : data.size();
    for (int j = 0; j < n; j++) {
        ui->resCb->addItem(QString("Triangle#%1 P:%2").arg(j+1).arg(data.at(j).getPerimeter()));
    }
}



//UI Events
void Form::on_showCurveChk_toggled(bool checked) {
    ui->plot->curveTri_vis(checked);
}

void Form::on_resCb_currentIndexChanged(int index) {
    if (ui->resCb->count()>0) {
        QVector<Triangle> data = g->getResT();

        ui->plot->plotTriangle(data,index);
        ui->triangleDesLbl->setText(tr("<html><head/><body><p><span style=\" font-size:9pt; font-weight:600;\">Triangle #%1:</span></p>"
                                       "<p><span style=\" font-size:9pt; text-decoration: underline;\">Perimeter:</span><span style=\" font-size:11pt;\"> %2</span></p>"
                                       "<p><span style=\" font-size:9pt; text-decoration: underline;\">P1:</span><span style=\" font-size:11pt;\"> (%3, %4)</span></p>"
                                       "<p><span style=\" font-size:9pt; text-decoration: underline;\">P2:</span><span style=\" font-size:11pt;\"> (%5, %6)</span></p>"
                                       "<p><span style=\" font-size:9pt; text-decoration: underline;\">P3:</span><span style=\" font-size:11pt;\"> (%7, %8)</span></p>"
                                       "</body></html>").arg(index+1).arg(data.at(index).getPerimeter())
                                                        .arg(data.at(index).getP1().x()).arg(data.at(index).getP1().y())
                                                        .arg(data.at(index).getP2().x()).arg(data.at(index).getP2().y())
                                                        .arg(data.at(index).getP3().x()).arg(data.at(index).getP3().y()));

        ui->curntPntNumLbl->setText(tr("<html><head/><body><p><span style=\" text-decoration: underline;\">Current:</span>"
                                       "<span style=\" font-size:11pt;\"> %1</span></p></body></html>").arg(g->getPoints().size()));
    }
}

void Form::on_regenPointsBtn_clicked() {
    g = new Graph(ui->pntNumMinSb->value(),ui->pntNumMaxSb->value(),
                  ui->xfromSb->value(),ui->xtoSb->value(),ui->yfromSb->value(),ui->ytoSb->value());
    populateGraph();
    populateCmb();
    on_resCb_currentIndexChanged(0);
}
