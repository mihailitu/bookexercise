#include "percolation.h"
#include <iostream>

Percolation::Percolation(unsigned n) :
    qfw(n * n + 2), // UnionFind will store n*n values, plus fake top node and fake bottom node
    N(n) // sites will be from 1 to N
{
    sites.resize(N + 1);
    for(unsigned i = 1; i <= N; ++i) {
        sites[i].resize(N + 1);
        sites[i].assign(N + 1, false);
    }

    for(unsigned i = 1; i <= N; ++i) {
        qfw.connect(i, 0); // connect top row to virtual top
        qfw.connect(qfIndex(N, i), N * N + 1); // connect bottom row to virtual bottom
    }
}

bool Percolation::indexesAreValid(unsigned row, unsigned col)
{
    return ((row >= 1 && row <= N) &&
            (col >= 1 && col <= N));
}

// opens the site (row, col) if it is not open already
void Percolation::open(unsigned row, unsigned col)
{
    if (!indexesAreValid(row, col) || isOpen(row, col))
        return;

    sites[row][col] = true;
    ++openSites;

    // connect this site to its open neighbors
    if (indexesAreValid(row - 1, col) && isOpen(row - 1, col))
        qfw.connect(row - 1, col);
    if (indexesAreValid(row + 1, col) && isOpen(row + 1, col))
        qfw.connect(row + 1, col);
    if (indexesAreValid(row, col - 1) && isOpen(row, col - 1))
        qfw.connect(row, col - 1);
    if (indexesAreValid(row, col + 1) && isOpen(row, col + 1))
        qfw.connect(row, col + 1);
}

// is the site (row, col) open?
bool Percolation::isOpen(unsigned row, unsigned col)
{
    if (!indexesAreValid(row, col))
        return false;

    return sites[row][col];
}

// is the site (row, col) full?
bool Percolation::isFull(unsigned row, unsigned col)
{
    if (!indexesAreValid(row, col))
        return false;

    return isOpen(row, col) && qfw.connected(0, qfIndex(row, col));
}

// returns the number of open sites
unsigned Percolation::numberOfOpenSites()
{
    return openSites;
}

// does the system percolate?
bool Percolation::percolates()
{
    // when virtual top is connected to virtual bottom, the system percolates
    return qfw.connected(0, N*N + 1);
}

unsigned Percolation::qfIndex(unsigned row, unsigned col)
{
    return col + N * (row - 1);
}

void Percolation::print()
{
    std::cout << '|';
    for(unsigned i = 1; i <= N; ++i)
        std::cout << '-';
    std::cout << "|\n";

    for(unsigned i = 1; i <= N; ++i) {
        std::cout << '|';
        for(unsigned j = 1; j <= N; ++j)
            std::cout << (isOpen(i, j) ? ' ' : 'x');
        std::cout << "|\n";
    }

    std::cout << '|';
    for(unsigned i = 1; i <= N; ++i)
        std::cout << '-';
    std::cout << "|\n";

}
