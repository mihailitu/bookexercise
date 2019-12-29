#include "percolation.h"
#include "unionfind.h"

#include <iostream>

Percolation::Percolation(unsigned long _N) : N(_N), openSites(0),
    uf(static_cast<unsigned>(_N * _N))
{
    grid = std::vector<std::vector<bool>>(N, std::vector<bool>(N, false));
}

// TODO: the row and column indices are integers between 1 and n, where (1, 1) is the upper-left site

// opens the site (row, col) if it is not open already
void Percolation::open(unsigned row, unsigned col)
{
    if (row >= N || col >= N)
        throw("IndexOutOfBounds");

    if (isOpen(row, col))
        return;
    grid[row][col] = true;

    connectUF(ufIndex(row, col), row - 1 , col);
    connectUF(ufIndex(row, col), row + 1 , col);
    connectUF(ufIndex(row, col), row , col - 1);
    connectUF(ufIndex(row, col), row , col + 1);
    ++openSites;

}

void Percolation::connectUF(unsigned int ufidx, unsigned int row, unsigned int col)
{
    if (!isOpen(row, col) || row >= N || col >= N)
        return;
    uf.connect(ufidx, ufIndex(row, col));
}

// is the site (row, col) open?
bool Percolation::isOpen(unsigned row, unsigned col) const
{
    if (row >= N || col >= N)
        throw("IndexOutOfBounds");

    return grid[row][col];
}

// is the site (row, col) full?
bool Percolation::isFull(unsigned row, unsigned col)
{
    if (row >= N || col >= N)
        throw("IndexOutOfBounds");

    return false;
}

// returns the number of open sites
unsigned Percolation::numberOfOpenSites() const
{
    return openSites;
}

// does the system percolate?
bool Percolation::percolates()
{
    return false;
}

unsigned Percolation::ufIndex(unsigned row, unsigned col) const
{
    return (row * N) + col;
}

void Percolation::print() const
{
    for(unsigned i = 0; i < N; ++i) {
        for(unsigned j = 0; j < N; ++j) {
            std::cout << (grid[i][j] ? '0' : 'x');
        }
        std::cout << '\n';
    }
}
