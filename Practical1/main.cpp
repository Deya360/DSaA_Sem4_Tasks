#include <QCoreApplication>
#include <iostream>
#include <iterator>
#include <fstream>
#include <vector>
#include <algorithm>
#include <windows.h>
#include <bits/stdc++.h>
#include <QElapsedTimer>
#include <QDebug>

using namespace std;

int cInt(unsigned int i) {return static_cast<int>(i);}
int cInt(double f) {return static_cast<int>(f);}
unsigned int cUInt(int i) {return static_cast<unsigned int>(i);}


static double FI_INV = 1/((sqrt(5) + 1) / 2);

int search_binary_goldenRatio(vector<int> vec, int l, int r, int query) {
    if (r >= l) {
        int mid1 = l + (r - l) * cInt(FI_INV);
        int mid2 = r - (r - l) * cInt(FI_INV);

        if (vec[cUInt(mid1)] == query) return mid1;
        if (vec[cUInt(mid2)] == query) return mid2;

        if (query < vec[cUInt(mid1)]) {
            return search_binary_goldenRatio(vec, l, mid1 - 1, query);

        } else if (query > vec[cUInt(mid2)]) {
            return search_binary_goldenRatio(vec, mid2 + 1, r, query);

        } else {
            return search_binary_goldenRatio(vec, mid1 + 1, mid2 - 1, query);
        }
    }
    return -1;
}

int search_binary(vector<int> vec, int l, int r, int query, int &cmpCount) {
    if (r >= l) {
        int mid = l + (r - l) / 2;

        if (vec[cUInt(mid)] == query) {
            cmpCount++;
            return mid;
        } else cmpCount++;

        if (vec[cUInt(mid)] > query) {
            cmpCount++;
            return search_binary(vec, l, mid - 1, query, cmpCount);
        } else cmpCount++;

        return search_binary(vec, mid + 1, r, query, cmpCount);
    }
    return -1;
}

int search_linearWSentinel(vector<int> vec, int query, int &cmpCount) {
    unsigned int N = vec.size();
    int last = vec[N-1];
    vec[N-1] = query;

    unsigned int i = 0;
    while(vec[i]!=query) i++;
    cmpCount = cInt(i);

    vec[N-1] = last;
    if((i < N-1) || (query == vec[N-1])) return cInt(i);
    return -1;
}

int search_linear(vector<int> vec, int query, int &cmpCount) {
    unsigned int i;
    for (i = 0; i < vec.size(); i++)
        if (vec[i] == query) {
            cmpCount = cInt(i*2);
            return cInt(i);
        }
    cmpCount = cInt(i*2);
    return -1;
}


void printVector(vector<int> vec) {
    copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
}

void printInColor(QString msg, unsigned short color = 7) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    cout << msg.toStdString() << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

vector<int> readFileToVec(string fileName) {
    ifstream in(fileName);
    vector<int> vec;
    int num;
    while (in >> num) vec.push_back(num);
    in.close();
    return vec;
}


int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    const string bP = qApp->applicationDirPath().toStdString(); //base path

    vector<int> ids = readFileToVec(bP + "\\medicineIDs.txt");  //Populate vector from file
    sort(ids.begin(), ids.end());

    int tempC, cmp1, cmp2, cmp3 = 0;
    printInColor("Search for '1008245' in list of medicine ID's :",6);
    printInColor("Task 1 - Linear Search: ",11);
        cout << "Element at: " << search_linear(ids, 1008245, tempC) << endl;  //Print result


    printInColor("Task 2 - Linear Search with Sentinel: ",11);
        cout << "Element at: " << search_linearWSentinel(ids, 1008245, tempC) << endl;


    printInColor("\nSearch for '1009741':",6);
    printInColor("Task 3 - Efficiency by number of Comparisons (Linear & Linear w/ Sentinel):",11);
        search_linear(ids, 1009741, cmp1);
        cout << "Linear Search: " << cmp1 << endl;

        search_linearWSentinel(ids,1009741, cmp2);
        cout << "Linear Search w/ Sentinel: " << cmp2 << endl;


    printInColor("\nSearch for '1005571':",6);
    printInColor("Task 4 - Binary Search:",11);
        cout << "Element at: " << search_binary(ids, 0, cInt(ids.size()), 1005571, tempC) << endl;


    printInColor("\nSearch for '1002651':",6);
    printInColor("Task 5 - Binary Search w/ Golden Ratio:",11);
        cout << "Element at: " << search_binary_goldenRatio(ids, 0, cInt(ids.size()), 1002651) << endl;


    printInColor("\nSearch for '1008860':",6);
    printInColor("Task 6 - Efficiency (Linear, Linear w/ Sentinel & Binary)): ",11);
        cmp1 = 0;
        cmp2 = 0;

        QElapsedTimer myTimer1;
        myTimer1.start();
        search_linear(ids, 1008860, cmp1);

        cout << "Linear Search: " << cmp1 << endl;
        qDebug() << "\t" << myTimer1.nsecsElapsed();


        QElapsedTimer myTimer2;
        myTimer2.start();
        search_linearWSentinel(ids,1008860, cmp2);

        cout << "Linear Search w/ Sentinel: "<< cmp2 << endl;
        qDebug() << "\t" << myTimer2.nsecsElapsed();


        QElapsedTimer myTimer3;
        myTimer3.start();
        search_binary(ids, 0, static_cast<int>(ids.size()), 1008860, cmp3);

        cout << "Binary Search: " << cmp3 << endl;
        qDebug() << "\t" << myTimer3.nsecsElapsed();

    //printVector(ids);
    return a.exec();
}
