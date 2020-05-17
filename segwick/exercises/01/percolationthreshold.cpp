#include "percolationthreshold.h"

#include <random>

/// perform independent trials on an n-by-n grid
PercolationStats::PercolationStats(int n, int trials) :
    systemSize(n),
    trials(trials),
    _mean(0.0),
    _stddev(0.0)
{
    runTrials();
}

void PercolationStats::runTrials()
{
    std::random_device r;
    std::default_random_engine e1(r());
    std::uniform_int_distribution<unsigned> uniform_dist(1, systemSize);

    for(unsigned i = 0; i < trials; ++i) {
        Percolation p(systemSize);
        while(!p.percolates()) // make sure we don't run indefinetly
            p.open(uniform_dist(e1), uniform_dist(e1));
        double threshold = static_cast<double>(p.numberOfOpenSites()) /
                static_cast<double>(p.size() * p.size());
        trialsThreshold.push_back(threshold);
    }

    for(unsigned i = 0; i < trials; ++i)
        _mean += trialsThreshold[i];

    _mean = _mean / static_cast<double>(trials);

    for(unsigned i = 0; i < trials; ++i)
        _stddev += ((trialsThreshold[i] - _mean) * (trialsThreshold[i] - _mean));

    _stddev = _stddev / static_cast<double>(trials - 1);
    _stddev = std::sqrt(_stddev);
}

/// sample mean of percolation threshold
double PercolationStats::mean()
{
    return _mean;
}

/// sample standard deviation of percolation threshold
double PercolationStats::stddev()
{
    return _stddev;
}

/// low endpoint of 95% confidence interval
double PercolationStats::confidenceLo()
{
    return _mean - (1.96 * _stddev) / std::sqrt(static_cast<double>(trials));
}

/// high endpoint of 95% confidence interval
double PercolationStats::confidenceHi()
{
    return _mean + (1.96 * _stddev) / std::sqrt(static_cast<double>(trials));
}
