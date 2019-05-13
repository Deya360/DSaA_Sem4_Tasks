#include "form.h"
#include "ui_form.h"


Form::Form(QWidget *parent) : QWidget(parent), ui(new Ui::Form) {
    ui->setupUi(this);
}

void Form::generate() {
    on_pushButton_clicked();
}

void Form::draw(int maxD, int colLength, std::vector<KeyedItem> *nodeData, std::vector<KeyedItem> *pathData) {
    ui->tableView->clearSpans();

    QStandardItemModel *model = new QStandardItemModel(this);

    for (int m = 0; m < maxD; m++) {
        int j = m+(1*m);
        int span = pow(2,maxD-(m+1));
        for (int n = 0; n < pow(2,m); n++) {
            KeyedItem currData = nodeData->at(seq(m-1)+m+n);
            QString val = QString::fromStdString(currData.getKey());

            QStandardItem *item1 = new QStandardItem(val);
            item1->setTextAlignment(Qt::AlignCenter);

            if(std::find(pathData->begin(), pathData->end(), currData) != pathData->end())
                item1->setForeground(QColor(Qt::red).darker(120));

            model->setItem(j,n*span,item1);
            if (span!=1) ui->tableView->setSpan(j,n*span,1,span); //m+(1*m)

        int i = j+1;
            if (i!=1) {
                if (currData.getKey().compare("")) {
                    QStandardItem *item2;
                    if (n%2==0) {
                        item2 = new QStandardItem(QString("/").append(QString(pow((maxD-m),1.9),' '))); //pow((maxD-m),2.3)
                        item2->setTextAlignment(Qt::AlignRight);
                    } else {
                        item2 = new QStandardItem(QString("\\").prepend(QString(pow((maxD-m),1.9),' ')));
                        item2->setTextAlignment(Qt::AlignLeft);
                    }

                    if(std::find(pathData->begin(), pathData->end(), currData) != pathData->end())
                        item2->setForeground(QColor(Qt::red).darker(120));

                    model->setItem(i-2,n*span,item2);
                    if (span!=1) ui->tableView->setSpan(i-2,n*span,1,span);
                }
            }
        }
    }

    ui->tableView->setModel(model);
    for (int c = 0; c < model->columnCount(); c++) ui->tableView->setColumnWidth(c,colLength);
    ui->label->setFocus();
}

int Form::seq(int n) { // 2*seq(n-1)+n
    if (n < 0) return 0;
    return (2*seq(n-1))+n;
}

Form::~Form() {
    delete ui;
}

void Form::on_pushButton_clicked() {
    BinaryTree bt;
    bt.generateRandomTree(22, 2,99);

    std::vector<KeyedItem> *pth = bt.getDiameterPath();
    std::cout << "Path Length: " << pth->size() << std::endl;

    std::cout << "Path: " << pth->at(0).getKey();
    for (int m = 1; m < pth->size(); m++) {std::cout  << ", " << pth->at(m).getKey();}
    std::cout << "\n\n";

    resize(pow(2,bt.getHeight())*15,(bt.getHeight()*2-1)*40);
    move(QApplication::desktop()->screenGeometry().center() - this->rect().center());
    draw(bt.getHeight(),25,bt.getBreadthFirstVector(),bt.getDiameterPath());
}
