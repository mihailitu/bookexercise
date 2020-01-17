#include <gtest/gtest.h>
#include <random>

#include "util.h"

template<typename T>
unsigned long partition(std::vector<T> &data, unsigned long lo, unsigned long hi)
{
    unsigned long i = lo;
    unsigned long j = hi + 1;

    while (true) {
        while(data[++i] < data[lo]) // find item on the left to swap
            if (i == hi)
                break;

        while(j > 0 && (data[lo] < data[--j])) // find item on the right side to swap
            if (j == lo)
                break;

        if (i >= j) // check if pointer crossed
            break;

        std::swap(data[i], data[j]);
    }
    std::swap(data[lo], data[j]); // swap with partition item
    return j;
}

template<typename T>
void sort(std::vector<T> &data, unsigned long lo, unsigned long hi)
{
    if (hi <= lo)
        return;
    unsigned long j = partition(data, lo, hi);

    if (j > 0)
        sort(data, lo, j - 1);
    sort(data, j + 1, hi);

}

template<typename T>
void quicksort(std::vector<T> &data)
{
    unsigned long lo = 0;
    unsigned long hi = data.size() - 1;
    std::random_shuffle(data.begin(), data.end());
    sort(data, lo, hi);
}

TEST(Chapter_2_3, QuickSortInt)
{
    std::vector<int> data = { 1, 3, 6, 4, 2, 4, 1, 4};
    printv(data);

    quicksort(data);

    EXPECT_TRUE(isSorted(data, 0, data.size() - 1));

    printv(data);
}

TEST(Chapter_2_3, QuickSortChar)
{
    std::string str = "MERGESORTEXAMPLE";
    std::vector<char> data (str.begin(), str.end());
    printv(data);

    quicksort(data);

    EXPECT_TRUE(isSorted(data, 0, data.size() - 1));

    printv(data);
}

TEST(Chapter_2_3, QuickSortIntRandom1MElem)
{
    unsigned N = 1'000'000;
    std::vector<int> data;
    data.reserve(N);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, N - 1);

    for(unsigned i = 0; i < N; ++i)
        data.push_back(dis(gen));

    quicksort(data);

    EXPECT_TRUE(isSorted(data, 0, data.size() - 1));
}

