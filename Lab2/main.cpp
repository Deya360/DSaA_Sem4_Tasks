#include <QApplication>

#include "form.h"

void display(KeyedItem &someItem) {
    std::cout << someItem.getKey() << std::endl;
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    Form w;
    w.show();
    w.generate();

    return a.exec();
}


