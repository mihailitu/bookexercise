#include "percolation.h"
#include <iostream>

Percolation::Percolation(unsigned n) :
    qfw(n * n + 2), // UnionFind will store n*n values, plus fake top node and fake bottom node
    N(n), // sites will be from 1 to N
    virtualTop(N * N),
    virtualBottom(N * N+1),
    openSites(0)
{
    sites.resize(N);
    for(unsigned i = 0; i < N; ++i) {
        sites[i].resize(N);
        sites[i].assign(N, false);
    }

    for(unsigned i = 0; i < N; ++i) {
        qfw.connect(i, virtualTop); // connect top row to virtual top
        qfw.connect(qfIndex(N - 1, i), virtualBottom); // connect bottom row to virtual bottom
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

    --row; --col;

    sites[row][col] = true;
    ++openSites;

    // connect this site to its open neighbors
    if (row > 0 && isOpen(row - 1, col))
        qfw.connect(qfIndex(row, col), qfIndex(row - 1, col));
    if (row < N && isOpen(row + 1, col))
        qfw.connect(qfIndex(row, col), qfIndex(row + 1, col));
    if (col > 0 && isOpen(row, col - 1))
        qfw.connect(qfIndex(row, col), qfIndex(row, col - 1));
    if (col < N && isOpen(row, col + 1))
        qfw.connect(qfIndex(row, col), qfIndex(row, col + 1));
}

// is the site (row, col) open?
bool Percolation::isOpen(unsigned row, unsigned col)
{
    if (!indexesAreValid(row, col))
        return false;

    --row; --col;

    return sites[row][col];
}

// is the site (row, col) full?
bool Percolation::isFull(unsigned row, unsigned col)
{
    if (!indexesAreValid(row, col))
        return false;

    --row; --col;

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
    return qfw.connected(virtualBottom, virtualTop);
}

unsigned Percolation::qfIndex(unsigned row, unsigned col)
{
    return col + N * row;
}

void Percolation::print()
{
    std::cout << '|';
    for(unsigned i = 0; i < N; ++i)
        std::cout << '-';
    std::cout << "|\n";

    for(unsigned i = 0; i < N; ++i) {
        std::cout << '|';
        for(unsigned j = 0; j < N; ++j)
            std::cout << (isOpen(i, j) ? ' ' : 'x');
        std::cout << "|\n";
    }

    std::cout << '|';
    for(unsigned i = 0; i < N; ++i)
        std::cout << '-';
    std::cout << "|\n";
}
