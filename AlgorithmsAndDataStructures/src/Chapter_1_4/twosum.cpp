#include "gtest.h"
#include "util.h"
#include <unordered_map>

// Given unsorted a, count all pairs that a[i]+a[j] = x
int count_all_pairs(const std::vector<int> &a, int x)
{
    std::unordered_map<int, int> hash;
    for(unsigned i = 0; i < a.size(); ++i)
        hash[x-a[i]] = i;

    for(unsigned i = 0; i < a.size(); ++i) {
        int numberToFind = x - a[i];
        // if(hash.find(numberToFind))

    }
}

TEST(Chapter_1_4, TwoSum)
{
    std::vector<int> data;
    readInts("data/1Kints.txt", data);
}
