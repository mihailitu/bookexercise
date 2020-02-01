#include "gtest.h"
#include "util.h"
#include <unordered_map>

// Given unsorted a, count all pairs that a[i]+a[j] = x
std::vector<std::pair<int, int>> count_all_pairs(const std::vector<int> &a, int x)
{
    std::unordered_map<int, int> hash;
    std::vector<std::pair<int, int>> result;
    for(unsigned i = 0; i < a.size(); ++i) {
        int numberToFind = x - a[i];
        if(hash.find(numberToFind) != hash.end()) {
            result.push_back({a[i], numberToFind});
            continue;
        }
        hash[a[i]] = a[i];

    }
    return result;
}

TEST(Chapter_1_4, TwoSum)
{
    std::vector<int> data;
    // readInts("data/1Kints.txt", data);
    data = {4, 5, 1, 8, 2, 3, 3};
    auto r = count_all_pairs(data, 6);
    for(auto e : r) {
        std::cout << "{" << e.first << ", " << e.second << "}\n";
    }
    // printv(r);
}
