#include "gtest/gtest.h"
#include <random>

// assume data is sorted
template<typename T>
std::vector<T> shuffle_random(const std::vector<T> &data)
{

    std::random_device rd;

    std::mt19937 e2(rd());

    std::uniform_real_distribution<double> dist(0, 1);

    std::vector<std::pair<double, int>> newIdxs;
    for(unsigned i = 0; i < data.size(); ++i) {
        newIdxs.push_back(std::make_pair(dist(e2), i));
    }

    auto pairCompaireSecond = [](const std::pair<int, double> &r1, const std::pair<int, double> &r2) {
      return r1.second < r2.second;
    };

    //Sort based on random values - it will get us shuffled indexes
    std::sort(newIdxs.begin(), newIdxs.end());

    std::vector<T> shuffled;
    for (unsigned i = 0; i < data.size(); ++i) {
        shuffled.push_back(data[newIdxs[i].second]);
    }

    return shuffled;
}

TEST(Chapter_2_1, ShuffleRandom)
{
    int N = 12;
    std::vector<int> data;

    for(unsigned i = 0; i < N; ++i)
        data.push_back(i);

    std::vector<int> shuffled = shuffle_random(data);
    for(unsigned i = 0; i < N; ++i)
        std::cout << shuffled[i] << " ";
    std::cout << "\n";
}
