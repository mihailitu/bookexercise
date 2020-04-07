#include "gtest/gtest.h"
#include "logger.h"

#include "unionfind.h"

#include <fstream>

/* data file format:
 * N - number of elements
 * p1 q1 - connection (p1, q1 < N)
 * p2 q2
 * ....
 */

void readUFDataFile(const std::string &fName, int &N, std::vector<std::pair<int, int>> &connections)
{
    std::ifstream testFile(fName);
    if (!testFile.is_open()) {
        FAIL() << fName << " not found";
        return;
    }

    testFile >> N;
    connections.reserve(N);
    int p, q;
    while (testFile >> p >> q) {
        connections.push_back({p, q});
    }
}

TEST(Test_Chapter_01, QuickFind)
{
    std::vector<std::pair<int, int>> connections;
    int N;
    readUFDataFile("", N, connections);
    log_debug("Creating UnionFind with %d elements and %d connections", N, connections.size());
    QuickFind<int> f(N);
}
