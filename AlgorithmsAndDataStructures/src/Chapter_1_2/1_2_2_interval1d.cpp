#include "gtest.h"
#include "fundamentals.h"

/* 1.2.2 Write an Interval1D client that takes an int value N as command-line argument,
 * reads N intervals (each defined by a pair of double values) from standard input,
 * and prints all pairs that intersect.
 */

bool intersects(const std::pair<int, int> &i1, const std::pair<int, int> &i2)
{
    // if one of the boundaries of the first interval is in between the boundaries of the second interval,
    // there is an intersection
    return ((i1.first >= i2.first && i1.first <= i2.second) ||
            (i1.second >= i2.first && i1.second <= i2.second) ||
            (i2.first >= i1.first && i2.first <= i1.second) ||
            (i2.second >= i1.first && i2.second <= i1.second));
}

std::vector<std::vector<unsigned>> _1_2_2_Interval1D(const std::vector<std::pair<int, int>> &intervals)
{
    std::cout << "Intervals: ";
    for(unsigned i = 0; i < intervals.size(); ++i) {
        std::cout << "[" << intervals[i].first << ", " << intervals[i].second << "]";
        if (i == intervals.size() -1)
            std::cout << "\n";
        else
            std::cout << ", ";
    }

    std::vector<std::vector<unsigned>> intersections(intervals.size()); // holds the vector position of intersected intervals
    for(unsigned i = 0; i < intervals.size(); ++i)
        for(unsigned j = 0; j < intervals.size(); ++j)
            if ((i != j) && intersects(intervals[i], intervals[j]))
                intersections[i].push_back(j);

    for(unsigned i = 0; i < intersections.size(); ++i)
        if(!intersections[i].empty()) {
            std::cout << "Interval " << "[" << intervals[i].first << ", " << intervals[i].second << "] intercts with interval(s): ";
            for(unsigned j = 0; j < intersections[i].size(); ++j)
                std::cout << "[" << intervals[intersections[i][j]].first << ", " << intervals[intersections[i][j]].second << "] ";
            std::cout << '\n';
        }

    std::cout << "-------------------\n";
    return intersections;
}

TEST(Fundamentals, _1_2_2_Interval1D)
{
    std::vector<std::pair<int, int>> intervals;

    intervals = {
        {1, 8},    // 0 intersects with 1, 2
        {3, 9},    // 1 intersects with 0, 2
        {7, 12},   // 2 intersects with 0, 1, 3
        {11, 15}   // 3 intersects with 2
    };
    std::vector<std::vector<unsigned>> ret = _1_2_2_Interval1D(intervals);

    intervals = {
        {2, 5},
        {5, 7},
        {3, 5}
    };

    ret = _1_2_2_Interval1D(intervals);
}
