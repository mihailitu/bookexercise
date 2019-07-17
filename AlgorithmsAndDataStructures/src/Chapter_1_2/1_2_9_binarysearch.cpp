#include "fundamentals.h"

/* 1.2.9 Instrument BinarySearch (page 47) to use a Counter to count the total number
 * of keys examined during all searches and then print the total after all searches are complete.
 * Hint : Create a Counter in main() and pass it as an argument to rank().
 */

int _1_2_9_recursive_binary_search(int key, const std::vector<int> &arr, unsigned long lo, unsigned long hi)
{
    if(lo > hi)
        return -1;

    unsigned long mid = lo + (hi - lo)/2;

    if(key < arr[mid])
        return _1_2_9_recursive_binary_search(key, arr, lo, mid - 1);
    else
        if(key >arr[mid])
            return _1_2_9_recursive_binary_search(key, arr, mid + 1, hi);
    return static_cast<int>(mid);
}

int _1_2_9_binary_search(int key, const std::vector<int> &arr, unsigned long lo, unsigned long hi)
{
    while(lo < hi) {
        unsigned long mid = lo + (hi - lo) / 2;
        if(key == arr[mid])
            return static_cast<int>(mid);
        if (key < arr[mid]) {
            hi = mid - 1;
        } else if(key > arr[mid]) {
            lo = mid + 1;
        }
    }
    return -1;
}

TEST(Fundamentals, _1_2_9_BinarySearch)
{
    std::vector<int> v = {84, 48, 68, 10, 18, 98, 12, 23, 54, 57, 48, 33, 16, 77, 11, 29};
    std::sort(v.begin(), v.end());

    std::vector<int> keys = {23, 50, 10, 99, 18, 23, 98, 84, 11, 10, 48, 77, 13, 54, 98, 77, 77, 68};

    for(auto i : keys) {
        int r = _1_2_9_binary_search(i, v, 0, v.size() - 1);
        int r1 = _1_2_9_recursive_binary_search(i, v, 0, v.size() - 1);

        EXPECT_EQ(r, r1) << " failed for " << i << std::endl;

        if(r < 0 || r1 < 0)
            std::cout << i << " not found!" << "\n";
    }
}
