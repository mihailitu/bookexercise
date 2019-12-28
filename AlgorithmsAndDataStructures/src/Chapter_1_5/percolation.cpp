#include "percolation.h"

Percolation::Percolation(unsigned _N) : N(_N)
{
    grid = std::vector<std::vector<bool>>(N, std::vector<bool>(N, false));
//    for(unsigned i = 0; i < N; ++i) {
//        grid.push_back(std::vector<bool>(N, false));
//    }
}

// opens the site (row, col) if it is not open already
void Percolation::open(unsigned row, unsigned col)
{
}

// is the site (row, col) open?
bool Percolation::isOpen(unsigned row, unsigned col)
{
    return false;
}

// is the site (row, col) full?
bool Percolation::isFull(unsigned row, unsigned col)
{
    return false;
}

// returns the number of open sites
unsigned Percolation::numberOfOpenSites()
{
    return 0;
}

// does the system percolate?
bool Percolation::percolates()
{
    return false;
}
