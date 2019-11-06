#include "gtest.h"

#include <vector>
#include <string>
#include <fstream>
#include "logger.h"

long long count_brute_force(const std::vector<int> &a)
{
    long long count = 0;
    for(auto i : a)
        for(auto j : a)
            for(auto k : a)
                if (i + j + k == 0)
                    ++count;

    return count;
}

bool binarySearch(const std::vector<int> &a, int val)
{
    long lo = 0;
    long hi = a.size() - 1;

    while(lo <= hi) {
        long mid = lo + (hi - lo) / 2;
        if(val < a[mid])
            hi = mid - 1;
        else if (val > a[mid])
            lo = mid + 1;
        else
            return true;
    }
    return false;
}

// sort the data and do binary search for each a[i], a[j], do a binary search for -(a[i] + a[j])
long long count_n_sq_log_n(std::vector<int> a)
{
    std::sort(a.begin(), a.end());
    unsigned long N = a.size();

    unsigned count = 0;
    for(unsigned i = 0; i < N; ++i)
        for(unsigned j = i + 1; j < N; ++j)
            if (binarySearch(a, -(a[i] + a[j])))
                ++count;
    return count;
}

void readInts(const std::string &fName, std::vector<int> &elements)
{
    std::ifstream testFile(fName);
    if (!testFile.is_open()) {
        FAIL() << fName << " not found";
        return;
    }
    int p;
    while (testFile >> p)
        elements.push_back(p);

    log_info("Constructed %u elements from %s",  elements.size(), fName.c_str());
}


TEST(Chapter_1_4, ThreeSum)
{
    std::vector<std::string> fileData = {
        "data/1Kints.txt",
//        "data/2Kints.txt",
//        "data/4Kints.txt",
//        "data/8Kints.txt",
//        "data/16Kints.txt",
//        "data/32Kints.txt",
//        "data/1Mints.txt"
    };

    for(auto f : fileData) {
        log_info("ThreeSum using: %s", f.c_str());
        std::vector<int> data;
        readInts(f, data);
        log_info("%d  elements adds up to zero", count_brute_force(data));
    }
}

TEST(Chapter_1_4, ThreeSumNsqLogN)
{
    std::vector<std::string> fileData = {
        "data/1Kints.txt",
        "data/2Kints.txt",
        "data/4Kints.txt",
        "data/8Kints.txt",
//        "data/16Kints.txt",
//        "data/32Kints.txt",
//        "data/1Mints.txt"
    };

    for(auto f : fileData) {
        log_info("ThreeSumDeLuxe using: %s", f.c_str());
        std::vector<int> data;
        readInts(f, data);
        log_info("%d  elements adds up to zero", count_n_sq_log_n(data));
    }
}

// Hint: given an integer x and a sorted array a[] of nnn distinct integers, design a linear-time algorithm to determine if there exists two distinct indices i and j such that a[i]+a[j]==x.
unsigned long count_n_sq(std::vector<int> &data)
{
    std::sort(data.begin(), data.end());
    int N = data.size();

    unsigned long count = 0;
    for(int i = 0; i < N -2; ++i) {
        int j = i + 1;
        int k = N - 1;
        while (j < k) {
            int sum = data[i] + data[j] + data[k];
            if( 0 == sum ) {
                // log_info("%d + %d + %d = 0", data[i], data[j], data[k]);
                ++count;
                ++j;
                --k;
            } else if (sum < 0)
                ++j;
            else
                --k;
        }
    }
    return count;
}

TEST(Chapter_1_4, ThreeSumNSquare)
{
    std::vector<std::string> fileData = {
        "data/1Kints.txt",
        "data/2Kints.txt",
        "data/4Kints.txt",
        "data/8Kints.txt",
        "data/16Kints.txt",
        "data/32Kints.txt",
        "data/1Mints.txt"
    };

//    std::vector<int> data = { -25, -10, -7, 0, -3, 2, 4, 8, 10};
//    log_info("%d  elements adds up to zero", count_n_sq(data));
//    return;

    for(auto f : fileData) {
        log_info("ThreeSumDeLuxe using: %s", f.c_str());
        std::vector<int> data;
        readInts(f, data);
        log_info("%lu  elements adds up to zero", count_n_sq(data));
    }
}
