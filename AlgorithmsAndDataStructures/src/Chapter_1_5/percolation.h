#ifndef PERCOLATION_H
#define PERCOLATION_H

#include <vector>

class Percolation
{
    unsigned N;
    std::vector<std::vector<bool>> grid;
public:
    // creates n-by-n grid, with all sites initially blocked
    Percolation(unsigned _N);

    // opens the site (row, col) if it is not open already
    void open(unsigned row, unsigned col);

    // is the site (row, col) open?
    bool isOpen(unsigned row, unsigned col);

    // is the site (row, col) full?
    bool isFull(unsigned row, unsigned col);

    // returns the number of open sites
    unsigned numberOfOpenSites();

    // does the system percolate?
    bool percolates();
};

#endif // PERCOLATION_H
