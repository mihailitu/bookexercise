#include "percolation.h"

#include "gtest.h"

Percolation createPercolationClass(const std::vector<std::vector<unsigned>> &layout)
{
    Percolation p(layout.size());
    for (unsigned i = 0; i < layout.size(); ++i)
        for(unsigned j = 0; j < layout[i].size(); ++j) {
            EXPECT_EQ(layout.size(), layout[i].size());
            if (layout[i][j] == 1)
                p.open(i, j);
        }
    return p;
}

void percolationTest(Percolation &p)
{
    p.print();
    std::cout << "Open sites " << p.numberOfOpenSites() << '\n';
}
TEST(Chapter_1_5, PercolationTest_1)
{
    std::vector<std::vector<unsigned>> gridEx = {
       //0  1  2  3  4  5  6  7
        {0, 0, 1, 1, 1, 0, 0, 0}, //0
        {1, 0, 0, 1, 1, 1, 1, 1}, //1
        {1, 1, 1, 0, 0, 1, 1, 0}, //2
        {0, 0, 1, 1, 0, 1, 1, 1}, //3
        {0, 1, 1, 1, 0, 1, 1, 0}, //4
        {0, 1, 0, 0, 0, 0, 1, 1}, //5
        {1, 0, 1, 0, 1, 1, 1, 1}, //6
        {1, 1, 1, 1, 0, 1, 0, 0}, //7
    };
    for (unsigned i = 0; i < gridEx.size(); ++i)
        for(unsigned j = 0; j < gridEx[i].size(); ++j)
            ASSERT_EQ(gridEx.size(), gridEx[i].size());

    Percolation p = createPercolationClass(gridEx);
    percolationTest(p);
}

TEST(Chapter_1_5, PercolationTest_2)
{
    std::vector<std::vector<unsigned>> gridEx = {
       //0  1  2  3  4  5  6  7
        {0, 0, 1, 1, 0, 1, 0, 0}, //0
        {1, 1, 1, 1, 1, 0, 0, 0}, //1
        {1, 1, 0, 0, 1, 1, 0, 0}, //2
        {0, 0, 1, 1, 1, 1, 1, 0}, //3
        {1, 0, 0, 0, 0, 0, 1, 1}, //4
        {0, 1, 0, 1, 1, 1, 0, 0}, //5
        {0, 1, 1, 0, 1, 1, 0, 1}, //6
        {1, 0, 1, 0, 0, 0, 1, 0}, //7
    };
    for (unsigned i = 0; i < gridEx.size(); ++i)
        for(unsigned j = 0; j < gridEx[i].size(); ++j)
            ASSERT_EQ(gridEx.size(), gridEx[i].size());

    Percolation p = createPercolationClass(gridEx);
    percolationTest(p);
}
