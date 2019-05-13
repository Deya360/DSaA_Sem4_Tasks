#ifndef FORM_H
#define FORM_H

#include "graph.h"
#include "qcpsubclass.h"

#include <QWidget>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();

    void populateGraph();
    void populateCmb();

private slots:
    void on_showCurveChk_toggled(bool checked);
    void on_resCb_currentIndexChanged(int index);

    void on_regenPointsBtn_clicked();

private:
    Ui::Form *ui;
    Graph *g;
};

#endif // FORM_H
