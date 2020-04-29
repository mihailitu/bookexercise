#include "percolation.h"

Percolation::Percolation(unsigned n) : qfw(n * n + 2)
{

}

// opens the site (row, col) if it is not open already
void Percolation::open(unsigned /*row*/, unsigned /*col*/)
{

}

// is the site (row, col) open?
bool Percolation::isOpen(unsigned /*row*/, unsigned /*col*/)
{
    return false;
}

// is the site (row, col) full?
bool Percolation::isFull(unsigned /*row*/, unsigned /*col*/)
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
