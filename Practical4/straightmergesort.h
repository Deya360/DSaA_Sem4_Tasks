#ifndef STRAIGHTMERGESORT_H
#define STRAIGHTMERGESORT_H

#include <iostream>
#include <vector>

void merge(std::vector<int> &arr, int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    std::vector<int> L, R;

    /* Copy data */
    for (i = 0; i < n1; i++) {
        if (l+i < arr.size()) {
            L.push_back(arr.at(l + i));
        }
    }

    for (j = 0; j < n2; j++) {
        R.push_back(arr.at(m + 1+ j));
    }

    /* Merge the temp arrays back into arr[l..r]*/
    i = j = 0;
    k = l;

    while (i < n1 && j < n2) {
        if (L.at(i) <= R.at(j)) {
            arr.at(k) = L.at(i);
            i++;

        } else {
            arr.at(k) = R.at(j);
            j++;
        }
        k++;
    }

    while (i < n1) {
        if (k < arr.size()) {
            arr.at(k) = L.at(i);
        }
        i++;
        k++;
    }

    while (j < n2) {
        arr.at(k) = R.at(j);
        j++;
        k++;
    }
}

void straightMergeSort(std::vector<int> &arr) {
   int n = arr.size();

   for (int curr_size=1; curr_size<=n-1; curr_size *= 2) {

       for (int left_start=0; left_start<n-1; left_start += 2*curr_size) {

           int mid = left_start + curr_size - 1;
           int right_end = std::min(left_start + 2*curr_size - 1, n-1);

           merge(arr, left_start, mid, right_end);
       }
   }
}

#endif // STRAIGHTMERGESORT_H
