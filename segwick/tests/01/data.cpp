#include "data.h"
#include "gtest/gtest.h"
#include "logger.h"

#include <fstream>

/* data file format:
 * N - number of elements
 * p1 q1 - connection (p1, q1 < N)
 * p2 q2
 * ....
 */

void readUFDataFile(const std::string &fName, unsigned &N, std::vector<std::pair<unsigned, unsigned>> &connections)
{
    std::ifstream testFile(fName);
    if (!testFile.is_open()) {
        FAIL() << fName << " not found";
        return;
    }
    int elems;
    testFile >> elems;
    ASSERT_TRUE(elems >= 0);
    N = static_cast<unsigned>(elems);
    connections.reserve(N);
    int p, q;
    while (testFile >> p >> q) {
        ASSERT_TRUE(p >= 0);
        ASSERT_TRUE(q >= 0);
        connections.push_back({p, q});
    }
}
