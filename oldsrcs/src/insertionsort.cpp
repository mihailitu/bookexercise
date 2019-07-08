#include "insertionsort.h"
#include <iostream>

void insertionSort(std::vector<int> &arr)
{
    int j;
    for(unsigned i = 1; i < arr.size(); ++i) {
        int key = arr[i];
        j = i - 1;
        while(j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j+1] = key;
    }
}
