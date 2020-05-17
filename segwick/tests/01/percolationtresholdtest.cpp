#include "gtest/gtest.h"

#include "percolationthreshold.h"
#include "logger.h"

#include <random>

TEST(Test_Percolation_Threshold, Test1_20x20_30_trials)
{
    std::vector<std::pair<unsigned, unsigned>> trials = {
        {200, 100},
        {200, 100},
        {2, 10000},
        {2, 100000},
        {500, 100}
    };

    for(unsigned i = 0; i < trials.size(); ++i) {
        log_info("Running N(%d), trials(%d)", trials[i].first, trials[i].second);
        PercolationStats ps(trials[i].first, trials[i].second);
        log_info("mean                    = %f", ps.mean());
        log_info("stddev                  = %f", ps.stddev());
        log_info("95%% confidence interval = [%f, %f]", ps.confidenceLo(), ps.confidenceHi());
    }
}
