#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QStandardItemModel>
#include <QDesktopWidget>

#include "keyeditem.h"
#include "binarytree.h"


namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();

    void draw(int maxD, int colLength, std::vector<KeyedItem> *nodeData, std::vector<KeyedItem> *pathData);
    void generate();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Form *ui;

    int seq(int n);
};

#endif // FORM_H
