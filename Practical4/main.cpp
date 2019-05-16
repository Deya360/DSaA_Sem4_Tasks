#include <QCoreApplication>
#include <iostream>
#include <windows.h>

#include "straightmergesort.h"
#include "naturalmergesort.h"
#include "multitrackmergesort.h"
#include "externalmergesort.h"

void printInColor(QString msg, unsigned short color = 7, bool cyrillic = false, bool endline = true) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

    if (cyrillic) {
        SetConsoleCP(866);
        SetConsoleOutputCP(866);
        setlocale(LC_CTYPE, "rus");
    }

    std::wcout << msg.toStdWString();
    if (endline) std::cout << std::endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

//TODO: Delete naturalmergesort2.h file from project directory
void printArray(std::vector<int> arr) {
    for (const int &c : arr) {
        std::cout << c << " ";
    }
    std::cout << std::endl;
}


int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    std::vector<int> arr = {2,8,7,4,4,8,7,4,12,1,1,4,8,7,4,12,4,12,45,1,1,4,8,74,5};
    std::vector<int> workArr = arr;

    //Tasks:
    std::cout << "Task1:\n";
    printArray(workArr);
    straightMergeSort(workArr);
    printArray(workArr);
    std::cout << "\n\n";


    std::cout << "Task2:\n";
    workArr = arr;
    printArray(workArr);
    std::cout << "Pass Count: " << naturalMergeSort(workArr,2) << "\n";
    printArray(workArr);
    std::cout << "\n\n";

    std::cout << "Task3:\n";
    workArr = arr;
    printArray(workArr);
    std::cout << "Pass Count: " << naturalMergeSort(workArr,4) << "\n";
    printArray(workArr);
    std::cout << "\n\n";

    std::cout << "Task4:\n";
    workArr = arr;
    printArray(workArr);
    std::cout << "Pass Count: " << multiTrackMergeSort(workArr)  << "\n";
    printArray(workArr);
    std::cout << "\n\n";

    return a.exec();
}
