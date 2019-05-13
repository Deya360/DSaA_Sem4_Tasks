#ifndef NAIVESEARCH_H
#define NAIVESEARCH_H

#include <QCoreApplication>
#include <bits/stdc++.h>

int NaiveSearch(char* pat, char* str) {
    bool found = false;
    int M = strlen(pat);
    int N = strlen(str);

    int cntr = 0;   //Counter
    for (int i = 0; i <= N - M; i++) {
        cntr++;
        int j;

        int cntrIn = 0;
        for (j = 0; j < M; j++) {
            cntrIn++;
            if (str[i + j] != pat[j]) break;
        }
        cntr+=cntrIn;

        if (j == M) {
            std::cout << QString("Found pattern at index %1").arg(i).toStdString() << std::endl;
            found = true;
        }
    }
    if (!found) std::cout << "No pattern match found!" << std::endl;

    return cntr;
}

#endif // NAIVESEARCH_H
