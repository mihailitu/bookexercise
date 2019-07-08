#include "selectionsort.h"

void selectionSort(std::vector<int> &arr)
{
    for(int i = 0; i < arr.size() - 1; ++i) {
        int minIdx = i;
        for(int j = i + 1; j < arr.size(); ++j)
            if(arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        std::swap(arr[minIdx], arr[i]);
    }
}
