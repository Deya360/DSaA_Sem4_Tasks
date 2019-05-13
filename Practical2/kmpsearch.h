#ifndef KMPSEARCH_H
#define KMPSEARCH_H

#include <QCoreApplication>
#include <bits/stdc++.h>

void computeLPSArray(char* pat, int M, int* lps) {
    // length of the previous longest prefix suffix
    int len = 0;

    lps[0] = 0; // lps[0] is always 0

    // the loop calculates lps[i] for i = 1 to M-1
    int i = 1;
    while (i < M) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;

        } else {    // (pat[i] != pat[len])
                    // This is tricky. Consider the example.
                    // AAACAAAA and i = 7. The idea is similar
                    // to search step.
            if (len != 0) {
                len = lps[len - 1];

                // Also, note that we do not increment
                // i here

            } else { // if (len == 0)
                lps[i] = 0;
                i++;
            }
        }
    }
}

int KMPSearch(char* pat, char* str) {
    bool found = false;
    int m = strlen(pat);
    int n = strlen(str);

    // create lps[] that will hold the longest prefix suffix values for pattern
    int lps[m];

    // Preprocess the pattern (calculate lps[] array)
    computeLPSArray(pat, m, lps);

    int cntr = 0;   //Counter

    int i = 0; // index for str[]
    int j = 0; // index for pat[]
    while (i < n) {
        cntr++;
        if (pat[j] == str[i]) {
            j++;
            i++;
        }

        if (j == m) {
            std::cout << QString("Found pattern at index %1").arg(i - j).toStdString() << std::endl;
            found = true;
            j = lps[j - 1];

        } else if (i < n && pat[j] != str[i]) {
            if (j != 0) j = lps[j - 1];
            else i = i + 1;
        }
    }
    if (!found) std::cout << "No pattern match found!" << std::endl;

    return cntr;
}


#endif // KMPSEARCH_H
