#include "gtest/gtest.h"
#include "logger.h"
#include "percolationthreshold.h"

/// xx___xxx            xx__x_xx              x <- blocked site
/// _xx_____            _____xxx              _ <- open site
/// ___xx__x            __xx__xx
/// xx__x___            xx_____x
/// x___x__x            _xxxxx__
/// x_xxxx__           x_x___xx
/// _x_x____            x__x__x_
/// ____x_xx            _x_xxx_x

TEST(Test_Percolation, TestPercolationClass)
{
    std::vector<std::vector<int>> doesPercolateExample = {
        {0, 0, 1, 1, 1, 0, 0, 0},
        {1, 0, 0, 1, 1, 1, 1, 1},
        {1, 1, 1, 0, 0, 1, 1, 0},
        {0, 0, 1, 1, 0, 1, 1, 1},
        {0, 1, 1, 1, 0, 1, 1, 0},
        {0, 1, 0, 0, 0, 0, 1, 1},
        {1, 0, 1, 0, 1, 1, 1, 1},
        {1, 1, 1, 1, 0, 1, 0, 0},
    };

    unsigned N = doesPercolateExample.size();
    Percolation test1(N);
    for(unsigned i = 0; i < N; ++i)
        for(unsigned j = 1; j < N; ++i)
            if (doesPercolateExample[i][j] == 1)
                test1.open(i + 1, j + 1);
    test1.print();
    ASSERT_TRUE(test1.percolates());

    std::vector<std::vector<int>> doesPNOTercolateExample = {
        {0, 0, 1, 1, 0, 1, 0, 0},
        {1, 1, 1, 1, 1, 0, 0, 0},
        {1, 1, 0, 0, 1, 1, 0, 0},
        {0, 0, 1, 1, 1, 1, 1, 0},
        {1, 0, 0, 0, 0, 0, 1, 1},
        {0, 1, 0, 1, 1, 1, 0, 0},
        {0, 1, 1, 0, 1, 1, 0, 1},
        {1, 0, 1, 0, 0, 0, 1, 0},
    };

    ASSERT_TRUE(false);
}
