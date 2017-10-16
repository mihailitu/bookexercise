#include "_2_maximum.h"
#include <vector>

#include <iostream>

void maxDiff(std::vector<int> v)
{
    int maxd = -1;
    int maxi = -1;
    int maxj = -1;
    int vSize = v.size();
    for(int i = 0; i < vSize; ++i)
        for(int j = 0; j < vSize; ++j)
            if((j - i > maxd) && v[j] > v[i]) {
                maxd = j - i;
                maxi = i;
                maxj = j;
            }
    std::cout << maxd << " " << maxj << " " << maxi << " ";
    for(auto i : v)
        std::cout << " " << i;
    std::cout << std::endl;
}

/* Given an array,find the maximum j – i such that arr[j] > arr[i] */
void _2_maximum()
{
/*
  Input: {34, 8, 10, 3, 2, 80, 30, 33, 1}
  Output: 6  (j = 7, i = 1)

  Input: {9, 2, 3, 4, 5, 6, 7, 8, 18, 0}
  Output: 8 ( j = 8, i = 0)

  Input:  {1, 2, 3, 4, 5, 6}
  Output: 5  (j = 5, i = 0)

  Input:  {6, 5, 4, 3, 2, 1}
  Output: -1 */

    std::vector<std::vector<int>> vlist = {
        {34, 8, 10, 3, 2, 80, 30, 33, 1},
        {9, 2, 3, 4, 5, 6, 7, 8, 18, 0},
        {1, 2, 3, 4, 5, 6},
        {6, 5, 4, 3, 2, 1}
    };

    for(auto v : vlist)
        maxDiff(v);
}
