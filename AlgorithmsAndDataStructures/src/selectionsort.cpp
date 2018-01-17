#include "selectionsort.h"

void selectionSort(std::vector<int> &arr)
{
    for(int i = 0; i < arr.size(); ++i) {
        int min = arr[i];
        int jj = i;
        for(int j = i + 1; j < arr.size(); ++j)
            if(arr[j] < min) {
                min = arr[j];
                jj = j;
            }
        arr[jj] = arr[i];
        arr[i] = min;
    }
}
