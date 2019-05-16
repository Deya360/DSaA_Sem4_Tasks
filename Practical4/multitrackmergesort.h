#ifndef MULTITRACKMERGESORT_H
#define MULTITRACKMERGESORT_H

#include <iostream>
#include <vector>
#include <queue>

typedef std::pair<int, std::pair<int, int>> ppi;

void sortMerge2(std::vector<std::vector<int>> &arr, std::vector<int> &workArr) {

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

int multiTrackMergeSort(std::vector<int> &arr) {
    const int fileCount = 6;
    int size = arr.size();
    int passCount = 0;

    if (size < fileCount) return -1;

    std::vector<int> workArr;
    std::vector<std::vector<std::vector<int>>> fileVec;
    fileVec.push_back(*new std::vector<std::vector<int>>);
    fileVec.push_back(*new std::vector<std::vector<int>>);
    int writeFileVecIdx = 0;
    bool fileVecSelector = false; // -> 0

    bool isSortedFlag = false;
    int fileArr, idx = 0;

    while (!isSortedFlag) {
        fileArr = 0;

        while ((fileArr<fileCount/2) && (idx < size)) {
            while (idx < size) {
                workArr.push_back(arr.at(idx));
                if ((idx+1<size) && (arr.at(idx) <= arr.at(idx + 1))) {
                    idx++;
                } else{
                    idx++;
                    fileArr++;
                    break;
                }
            }
            fileVec.at(fileVecSelector).push_back(workArr);
            workArr.clear();
        }

        sortMerge2(fileVec.at(fileVecSelector), workArr);

        if (fileVec.at(!fileVecSelector).size() < fileCount/2) {
            fileVec.at(!fileVecSelector).push_back(workArr);

        } else {
            fileVec.at(!fileVecSelector).at(writeFileVecIdx).insert(
                        fileVec.at(!fileVecSelector).at(writeFileVecIdx).end(),
                        workArr.begin(), workArr.end());
            writeFileVecIdx++;
        }

        if (writeFileVecIdx >= fileCount/2) {
            writeFileVecIdx = 0;
        }

        if (!fileVec.at(fileVecSelector).size()) {
            if (fileVec.at(!fileVecSelector).size()) {
                arr.clear();
                for(auto vec : fileVec.at(!fileVecSelector)) {
                    arr.insert(arr.end(), vec.begin(), vec.end());
                }
                fileVec.at(!fileVecSelector).clear();
                fileVecSelector = !fileVecSelector;
                writeFileVecIdx = 0;
                idx = 0;
                passCount--; //because of the way I implemented it,
                              //it will always waste an entire pass before entering this if statment
            }

        } else if (arr==fileVec.at(fileVecSelector).at(0)) {
            isSortedFlag = true;

        } else {
            workArr.clear();
            fileVec.at(fileVecSelector).clear();
        }
        passCount++;
    }
    return passCount-1;
}


#endif // MULTITRACKMERGESORT_H
