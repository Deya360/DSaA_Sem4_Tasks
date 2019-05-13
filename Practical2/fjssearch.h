#ifndef FJSSEARCH_H
#define FJSSEARCH_H

#include <iostream>
#include <QString>

const int MAX_PATLEN = 200;
const int NO_OF_CHARS2 = 256;

int betap[ MAX_PATLEN+1 ];
int delta[ NO_OF_CHARS2 ];

void makeBetap(unsigned char* pat, int m) {
    int i = 0, j = betap[0] = -1;

    while( i < m ) {
        while( (j > -1) && (pat[i] != pat[j]) ) {
            j = betap[j];
        }
        if( pat[++i] == pat[++j] ) {
            betap[i] = betap[j];
        } else {
            betap[i] = j;
        }
    }
}

void makeDelta(unsigned char* pat, int m) {
    int i;

    for( i = 0; i < NO_OF_CHARS2; ++i ) {
        delta[i] = m + 1;
    }
    for( i = 0; i < m; ++i ) {
        delta[ pat[i] ] = m - i;
    }
}

void FJSSearch(char* pat_s, char* str_s) {
    bool found = false;
    int m = strlen(pat_s);
    int n = strlen(str_s);

    unsigned char* pat = reinterpret_cast<unsigned char*>(pat_s);
    unsigned char* str = reinterpret_cast<unsigned char*>(str_s);

    makeBetap(pat, m);
    makeDelta(pat, m);

    int i = 0, j = 0, mp = m-1, ip = mp;
    while( ip < n ) {
        if( j <= 0 ) {
            while( pat[ mp ] != str[ ip ] ) {
                ip += delta[ str[ ip+1 ] ];
                if( ip >= n ) {
                    if (!found) std::cout << "No pattern match found!" << std::endl;
                    return;
                }
            }

            j = 0;
            i = ip - mp;
            while( (j < mp) && (str[i] == pat[j]) ) {
                ++i;
                ++j;
            }

            if( j == mp ) {
                found = true;
                std::cout << QString("Found pattern at index %1").arg(i-mp).toStdString() << std::endl;
                ++i;
                ++j;
            }

            if( j <= 0 ) {
                ++i;

            } else {
                j = betap[j];
            }

        } else {
            while( (j < m) && (str[i] == pat[j]) ) {
                ++i; ++j;
            }

            if( j == m )
                found = true;
                std::cout << QString("Found pattern at index %1").arg(i-m).toStdString() << std::endl;

            j = betap[j];
        }
        ip = i + mp - j;
    }
    if (!found) std::cout << "No pattern match found!" << std::endl;
}

#endif // FJSSEARCH_H
