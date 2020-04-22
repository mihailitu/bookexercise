#include "gtest/gtest.h"
#include "logger.h"
#include "data.h"

#include "unionfind.h"

TEST(Test_Chapter_01, QuickFind)
{
    std::vector<std::string> dataSets = {
        "data/tinyUF.txt",
        "data/mediumUF.txt",
        // "data/largeUF.txt"
    };

    for(const auto &dataFile : dataSets) {
        log_info("Processing file %s", dataFile.c_str());

        std::vector<std::pair<unsigned, unsigned>> connections;
        unsigned N;
        readUFDataFile(dataFile, N, connections);

        log_debug("Creating UnionFind with %d elements and %lu connections", N, connections.size());
        QuickFind qf(static_cast<unsigned>(N));
        for(unsigned i = 0; i < connections.size(); ++i)
            qf.connect(connections[i].first, connections[i].second);

        for(unsigned i = 0; i < connections.size(); ++i)
            ASSERT_TRUE(qf.connected(connections[i].first, connections[i].second));
    }
}
