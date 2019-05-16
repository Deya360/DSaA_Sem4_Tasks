#ifndef NATURALMERGESORT2_H
#define NATURALMERGESORT2_H

#include <iostream>
#include <vector>
#include <QDebug>

void merge2(std::vector<int> &arr, std::vector<int> &workArr, int begin1, int end1, int begin2, int end2) {
    int counter1 = begin1;
    int counter2 = begin2;

    for (int i = begin1; i <= end2; i++) {
        if ((counter1 <= end1) && ((counter2 > end2) || arr.at(counter1) <= arr.at(counter2))) {
            workArr.at(i) = arr.at(counter1);
            counter1++;

        } else {
            workArr.at(i) = arr.at(counter2);
            counter2++;
        }
    }
}

void naturalMergeSort2(std::vector<int> &arr) {
    int size = arr.size();
    if (size < 2) return;

    std::vector<int> workArr(size);
    int isSortedFlag = 0;
    while (isSortedFlag == 0) {
        int begin1, end1, begin2, end2;
        begin1 = end1 = begin2 = end2 = 0;

        while (end1 < (size - 1)) {
            if (arr.at(end1) <= arr.at(end1 + 1)) {
                end1++;

            } else{
                for (begin2 = end2 = (end1 + 1); end2 < (size - 1); end2++) {
                    if (arr.at(end2) <= arr.at(end2 + 1)){
                        continue;

                    } else {
                        break;
                    }
                }

                merge2(arr, workArr, begin1, end1, begin2, end2);

                for (int c = begin1; c <= end2; c++) {
                    arr.at(c) = workArr.at(c);
                }

                begin1 = end1 = (end2 + 1);
            }

        }
        if ((begin2 == 0) && (end2 == 0)) {
            isSortedFlag = 1;
        }
    }
}


#endif // NATURALMERGESORT2_H
