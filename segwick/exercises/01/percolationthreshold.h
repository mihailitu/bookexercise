#ifndef PERCOLATIONTHRESHOLD_H
#define PERCOLATIONTHRESHOLD_H

/// Write a program to estimate the value of the percolation threshold via Monte Carlo simulation.
/// The problem.
/// In a famous scientific problem, researchers are interested in the following question:
/// if sites are independently set to be open with probability p (and therefore blocked with probability 1 − p),
/// what is the probability that the system percolates?
/// When p equals 0, the system does not percolate; when p equals 1, the system percolates.
/// The plots below show the site vacancy probability p versus the percolation probability for 20-by-20 random grid (left)
/// and 100-by-100 random grid (right).
///
/// When n is sufficiently large, there is a threshold value p* such that when p < p* a random n-by-n grid almost never percolates,
/// and when p > p*, a random n-by-n grid almost always percolates.
/// No mathematical solution for determining the percolation threshold p* has yet been derived.
/// Your task is to write a computer program to estimate p*.
///
/// Monte Carlo simulation. To estimate the percolation threshold, consider the following computational experiment:
///
/// Initialize all sites to be blocked.
/// Repeat the following until the system percolates:
/// Choose a site uniformly at random among all blocked sites.
/// Open the site.
/// The fraction of sites that are opened when the system percolates provides an estimate of the percolation threshold.
/// For example, if sites are opened in a 20-by-20 lattice according to the snapshots below,
/// then our estimate of the percolation threshold is 204/400 = 0.51 because the system percolates when the 204th site is opened.
/// By repeating this computation experiment T times and averaging the results,
/// we obtain a more accurate estimate of the percolation threshold.
/// Let xt be the fraction of open sites in computational experiment t.
/// The sample mean x¯¯¯ provides an estimate of the percolation threshold;
/// the sample standard deviation s; measures the sharpness of the threshold.

// Eg:
// ~/Desktop/percolation> java-algs4 PercolationStats 200 100
// mean                    = 0.5929934999999997
// stddev                  = 0.00876990421552567
// 95% confidence interval = [0.5912745987737567, 0.5947124012262428]
// ~/Desktop/percolation> java-algs4 PercolationStats 200 100
// mean                    = 0.592877
// stddev                  = 0.009990523717073799
// 95% confidence interval = [0.5909188573514536, 0.5948351426485464]

// ~/Desktop/percolation> java-algs4 PercolationStats 2 10000
// mean                    = 0.666925
// stddev                  = 0.11776536521033558
// 95% confidence interval = [0.6646167988418774, 0.6692332011581226]

// ~/Desktop/percolation> java-algs4 PercolationStats 2 100000
// mean                    = 0.6669475
// stddev                  = 0.11775205263262094
// 95% confidence interval = [0.666217665216461, 0.6676773347835391]

class PercolationStats {
public:
    // perform independent trials on an n-by-n grid
    PercolationStats(int n, int trials);

    // sample mean of percolation threshold
    double mean();

    // sample standard deviation of percolation threshold
    double stddev();

    // low endpoint of 95% confidence interval
    double confidenceLo();

    // high endpoint of 95% confidence interval
    double confidenceHi();
};

class PercolationThreshold
{
public:
    PercolationThreshold();
};

#endif // PERCOLATIONTHRESHOLD_H
