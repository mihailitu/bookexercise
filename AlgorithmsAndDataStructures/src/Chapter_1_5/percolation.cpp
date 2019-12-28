#include "percolation.h"
#include <iostream>

Percolation::Percolation(unsigned long _N) : N(_N), openSites(0)
{
    grid = std::vector<std::vector<bool>>(N, std::vector<bool>(N, false));
}

// opens the site (row, col) if it is not open already
void Percolation::open(unsigned row, unsigned col)
{
    if (row >= N || col >= N)
        throw("IndexOutOfBounds");

    if (grid[row][col])
        return;
    grid[row][col] = true;
    ++openSites;
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

void Percolation::print() const
{
    for(unsigned i = 0; i < N; ++i) {
        for(unsigned j = 0; j < N; ++j) {
            std::cout << (grid[i][j] ? '0' : 'x');
        }
        std::cout << '\n';
    }
}
