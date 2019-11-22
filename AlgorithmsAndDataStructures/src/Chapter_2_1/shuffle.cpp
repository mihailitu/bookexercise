#include "gtest/gtest.h"
#include <random>

// assume data is sorted
template<typename T>
std::vector<T> shuffle_random(const std::vector<T> &data)
{

    std::random_device rd;

    std::mt19937 e2(rd());

    std::uniform_real_distribution<double> dist(0, 1);

    std::vector<std::pair<double, unsigned>> newIdxs;
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
    unsigned N = 1000000;
    std::vector<int> data;

    for(unsigned i = 0; i < N; ++i)
        data.push_back(static_cast<int>(i));

    std::sort(data.begin(), data.end());

    std::vector<int> shuffled = shuffle_random(data);
//    for(unsigned i = 0; i < N; ++i)
//        std::cout << shuffled[i] << " ";
//    std::cout << "\n";
    ASSERT_EQ(data.size(), shuffled.size());

    unsigned equalElements = 0;
    for(unsigned i = 0; i < N; ++i)
        if(data[i] == shuffled[i])
            ++equalElements;

    std::cout << "Equal elements after shuffle: " << equalElements << std::endl;
    ASSERT_TRUE(equalElements < N/10);
}
