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
    {
        std::vector<std::vector<int>> doesPercolateExampleSmall = {
            {0, 1, 1},
            {1, 1, 0},
            {1, 1, 1},
        };

        unsigned N = doesPercolateExampleSmall.size();
        Percolation test0(N);
        for(unsigned i = 0; i < N; ++i)
            for(unsigned j = 0; j < N; ++j)
                if (doesPercolateExampleSmall[i][j] == 1)
                    test0.open(i + 1, j + 1);
        test0.print();
        ASSERT_TRUE(test0.percolates());
    }

    {
        std::vector<std::vector<int>> doesNotPercolateExampleSmall = {
            {0, 0, 1},
            {1, 0, 0},
            {1, 1, 1},
        };
        unsigned N = doesNotPercolateExampleSmall.size();
        Percolation test0(N);
        for(unsigned i = 0; i < N; ++i)
            for(unsigned j = 0; j < N; ++j)
                if (doesNotPercolateExampleSmall[i][j] == 1)
                    test0.open(i + 1, j + 1);
        test0.print();
        ASSERT_FALSE(test0.percolates());
    }

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
        Percolation test0(N);
        for(unsigned i = 0; i < N; ++i)
            for(unsigned j = 0; j < N; ++j)
                if (doesPercolateExample[i][j] == 1)
                    test0.open(i + 1, j + 1);
        test0.print();
        ASSERT_TRUE(test0.percolates());
    }

    {
        std::vector<std::vector<int>> doesNOTPercolateExample = {
            {0, 0, 1, 1, 0, 1, 0, 0},
            {1, 1, 1, 1, 1, 0, 0, 0},
            {1, 1, 0, 0, 1, 1, 0, 0},
            {0, 0, 1, 1, 1, 1, 1, 0},
            {1, 0, 0, 0, 0, 0, 1, 1},
            {0, 1, 0, 1, 1, 1, 0, 0},
            {0, 1, 1, 0, 1, 1, 0, 1},
            {1, 0, 1, 0, 0, 0, 1, 0},
        };
        unsigned N = doesNOTPercolateExample.size();
        Percolation test0(N);
        for(unsigned i = 0; i < N; ++i)
            for(unsigned j = 0; j < N; ++j)
                if (doesNOTPercolateExample[i][j] == 1)
                    test0.open(i + 1, j + 1);
        test0.print();
        ASSERT_FALSE(test0.percolates());
    }
}
