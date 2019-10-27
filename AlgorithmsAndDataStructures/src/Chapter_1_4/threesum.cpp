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


