#ifndef NATURALMERGESORT_H
#define NATURALMERGESORT_H

#include <iostream>
#include <vector>
#include <queue>

typedef std::pair<int, std::pair<int, int>> ppi;

void sortMerge(std::vector<std::vector<int>> &arr, std::vector<int> &workArr) {

    std::priority_queue<ppi, std::vector<ppi>, std::greater<ppi> > pq;

    for (int i = 0; i < arr.size(); i++)
        pq.push({ arr[i][0], { i, 0 } });

    while (!pq.empty()) {
        ppi curr = pq.top();
        pq.pop();

        int i = curr.second.first;
        int j = curr.second.second;

        workArr.push_back(curr.first);

        if (j + 1 < arr[i].size())
            pq.push({ arr[i][j + 1], { i, j + 1 } });
    }
}

int naturalMergeSort(std::vector<int> &arr, int subArrCount) {
    int size = arr.size();
    int passCount = 0;
    if (size < subArrCount) return -1;

    std::vector<int> workArr;
    std::vector<std::vector<int>> subArrVec;

    bool isSortedFlag = false;
    int subArr, idx;

    while (!isSortedFlag) {
        subArr = idx = 0;

        while ((subArr<subArrCount) && (idx < size)) {
            while (idx < size) {
                workArr.push_back(arr.at(idx));
                if ((idx+1<size) && (arr.at(idx) <= arr.at(idx + 1))) {
                    idx++;
                } else{
                    idx++;
                    subArr++;
                    break;
                }
            }
            subArrVec.push_back(workArr);
            workArr.clear();
        }

        sortMerge(subArrVec, workArr);
        std::copy(workArr.begin(), workArr.end(), arr.begin());

        if (subArrVec.size() == 1) {
            isSortedFlag = true;

        } else {
            workArr.clear();
            subArrVec.clear();
        }
        passCount++;
    }
    return passCount-1;
}


#endif // NATURALMERGESORT_H
