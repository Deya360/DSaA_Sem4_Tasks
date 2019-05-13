#include <QCoreApplication>
#include <bits/stdc++.h>
#include <windows.h>

#include "kmpsearch.h"
#include "bmsearch.h"
#include "naivesearch.h"
#include "fjssearch.h"

void printInColor(QString msg, unsigned short color = 7, bool cyrillic = false) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

    if (cyrillic) {
        SetConsoleCP(866);
        SetConsoleOutputCP(866);
        setlocale(LC_CTYPE, "rus");
    }

    std::wcout << msg.toStdWString() << std::endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    char string[] = "Society excited by cottage private an it esteems. Fully begin on by wound an. Girl rich in do up or both. At declared in as rejoiced of together. He impression collecting delightful unpleasant by prosperous as on. End too talent she object mrs wanted remove giving. Far concluded not his something extremity. Want four we face an he gate. On he of played he ladies answer little though nature. Blessing oh do pleasure as so formerly. Took four spot soon led size you. Outlived it received he material. Him yourself joy moderate off repeated laughter outweigh screened. Delightful remarkably mr on announcing themselves entreaties favourable.";
//    char string[] = "Ветровое стекло не будет служить лишь для защиты от атмосферных осадков и ветра.";
//    char pattern[] = "не";
    printInColor(QString("String:   \"%1\" \n").arg(string),15,true);
    printInColor(QString("Pattern:  "),15,true);

    std::string strtmp;
    std::getline(std::cin, strtmp);
    char* pattern = (char*)strtmp.data();

    int KMP_IterCount, BM_IterCount, N_IterCount;
    printInColor("\n\nTask 1 - Knuth-Morris-Pratt algorithm:",11);
    KMP_IterCount = KMPSearch(pattern, string);

    printInColor("\nTask 2 - Boyer Moore algorithm:",11);
    BM_IterCount = BMSearch(pattern, string);

    printInColor("\nTask 3 - Naive algorithm",11);
    N_IterCount = NaiveSearch(pattern, string);

    printInColor("\nTask 4 - Efficiency - Iterations (Naive, Knuth-Morris-Pratt)",11);
    std::cout << std::left << std::setw(20) << "Naive:" << N_IterCount << std::endl;
    std::cout << std::left << std::setw(20) << "Knuth-Morris-Pratt:" << KMP_IterCount << std::endl;

    printInColor("\nTask 5 - Efficiency - Iterations (Naive, Boyer Moore)",11);
    std::cout << std::left << std::setw(20) << "Naive:" << N_IterCount << std::endl;
    std::cout << std::left << std::setw(20) << "Boyer Moore:" << BM_IterCount << std::endl;

    printInColor("\nTask 6 - FJS algorithm (Combination of KMP and BM)",11);
    FJSSearch(pattern, string);


    return a.exec();
}
