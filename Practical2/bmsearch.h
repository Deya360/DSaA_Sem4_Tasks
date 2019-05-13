#ifndef BMSEARCH_H
#define BMSEARCH_H

#include <iostream>
#include <QString>

const int NO_OF_CHARS = 256;
void badCharHeuristic(std::wstring str, int size, int badchar[NO_OF_CHARS]) {
    for (int i = 0; i < NO_OF_CHARS; i++) badchar[i] = -1;
    for (int i = 0; i < size; i++) badchar[str[i]] = i;
}

int BMSearch(char* pat, char* str) {
    bool found = false;
    int m = strlen(pat);
    int n = strlen(str);

    std::wstring pat_w = std::wstring(&pat[0], &pat[m]);
    std::wstring txt_w = std::wstring(&str[0], &str[n]);

    int badchar[NO_OF_CHARS];
    badCharHeuristic(pat_w, m, badchar);

    int cntr = 0;   //Counter
    int s = 0;
    while(s <= (n - m)) {
        cntr++;
        int j = m - 1;

        int cntrIn = 0;
        while(j >= 0 && pat_w[j] == txt_w[s + j]) {
            j--;
            cntrIn++;
        }
        cntr+=cntrIn;

        if (j < 0) {
            std::cout << QString("Found pattern at index %1").arg(s).toStdString() << std::endl;
            found = true;
            s += (s + m < n)? m-badchar[txt_w[s + m]] : 1;

        } else s += std::max(1, j - badchar[txt_w[s + j]]);
    }
    if (!found) std::cout << "No pattern match found!" << std::endl;

    return cntr;
}

#endif // BMSEARCH_H
