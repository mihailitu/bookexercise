#include "gtest.h"
#include <iostream>
#include <fstream>

#include "unionfind.h"
// 1. read test data from file (first line, the number of points. fter, a pair of integers
// 2. if they are not connected, connect them and print out pair
void testUnionFind(const std::string &fName)
{
    std::ifstream testFile(fName);
    if (!testFile.is_open()) {
        FAIL() << fName << " not found";
        return;
    }
    int N;
    testFile >> N;
    UnionFindQuickUnionWeighted uf(N);
    int p, q;
    while (testFile >> p >> q) {
        if (!uf.connected(p, q)) {
            uf.union_connect(p, q);
            // std::cout << p << " + " << q << "\n";
        }
    }
}

TEST(Chapter_1_5, UnionQuickWeightedFindTiny)
{
    testUnionFind("data/tinyUF.txt");
}

TEST(Chapter_1_5, UnionQuickWeightedFindMedium)
{
    testUnionFind("data/mediumUF.txt");
}

TEST(Chapter_1_5, UnionQuickWeightedFindLarge)
{
    testUnionFind("data/largeUF.txt");
}
