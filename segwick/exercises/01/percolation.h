#ifndef PERCOLATION_H
#define PERCOLATION_H

#include "unionfind.h"

/// Percolation.
/// Given a composite systems comprised of randomly distributed insulating and metallic materials:
/// what fraction of the materials need to be metallic so that the composite system is an electrical conductor?
/// Given a porous landscape with water on the surface (or oil below), under what conditions will the water be able to
/// drain through to the bottom (or the oil to gush through to the surface)?
/// Scientists have defined an abstract process known as percolation to model such situations.
///
/// The model.
/// We model a percolation system using an n-by-n grid of sites.
/// Each site is either open or blocked. A full site is an open site that can be connected to an open site in the top row
/// via a chain of neighboring (left, right, up, down) open sites.
/// We say the system percolates if there is a full site in the bottom row.
/// In other words, a system percolates if we fill all open sites connected to the top row and that process fills some open site on the bottom row.
/// (For the insulating/metallic materials example, the open sites correspond to metallic materials,
/// so that a system that percolates has a metallic path from top to bottom, with full sites conducting.
/// For the porous substance example, the open sites correspond to empty space through which water might flow,
/// so that a system that percolates lets water fill open sites, flowing from top to bottom.)
///
/// Eg.: 8x8 grid
/// 1) percolates    1) does not percolates
/// xx___xxx            xx__x_xx              x <- blocked site
/// _xx_____            _____xxx              _ <- open site
/// ___xx__x            __xx__xx
/// xx__x___            xx_____x
/// x___x__x            _xxxxx__
/// x_xxxx___           x_x___xx
/// _x_x____            x__x__x_
/// ____x_xx            _x_xxx_x


class Percolation
{
public:
    /// creates n-by-n grid, with all sites initially blocked
    Percolation(unsigned n);

    //// opens the site (row, col) if it is not open already
    void open(unsigned row, unsigned col);

    /// is the site (row, col) open?
    bool isOpen(unsigned row, unsigned col);

    /// is the site (row, col) full?
    bool isFull(unsigned row, unsigned col);

    /// returns the number of open sites
    unsigned numberOfOpenSites();

    /// does the system percolate?
    bool percolates();

    /// print the system
    void print();

private:
    /// UnionFind structure
    QuickUnionWeighted qfw;

    /// NxN dimension of the system
    unsigned N;

    /// open sites number
    unsigned openSites;

    /// open/closed sites
    std::vector<std::vector<bool>> sites;

    /// calculates the index in UnionFind array that correpsonds to [row, col] in the system
    unsigned qfIndex(unsigned row, unsigned col);

    /// verifies if indexes are valid
    bool indexesAreValid(unsigned row, unsigned col);
};

#endif // PERCOLATION_H
