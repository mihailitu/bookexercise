#include "util.h"
#include <gtest/gtest.h>
#include <random>

template<typename T>
void sink(std::vector<T> &data, unsigned long k, unsigned long N) {
    while (2 * k <= N) // children of node k are 2*k and 2*k+1
    {
        unsigned long j = 2*k;
        if ((j < N) && (data[j - 1] < data[j+1 - 1])) // choose the larger of the two children
            j++;
        if (!(data[k-1] < data[j-1]))
            break;
        std::swap(data[k-1], data[j-1]);
        k = j;
    }
}



template<typename T>
void heapSort(std::vector<T> &data)
{
    unsigned long N = data.size();
    for(unsigned long k = N/2; k>=1;k--)
        sink(data, k, N);

    while(N>1) {
        // when working on data elements, make sure to decrement indexes, as heap priority queue works with 1 to N indexes,
        // but we are expecting the vector to be 0 to N - 1
//        std::swap(data[1], data[N]);
        std::swap(data[1 - 1], data[N - 1]);
        sink(data, 1, --N);
    }
}

TEST(Chapter_2_4, HeapSortInt)
{
    std::vector<int> data = { 1, 3, 6, 4, 2, 4, 1, 4};
    printv(data);

    heapSort(data);

    EXPECT_TRUE(isSorted(data, 0, data.size() - 1));

    printv(data);
}

TEST(Chapter_2_4, HeapSortChar)
{
    std::string str = "MERGESORTEXAMPLE";
    std::vector<char> data (str.begin(), str.end());
    printv(data);

    heapSort(data);

    EXPECT_TRUE(isSorted(data, 0, data.size() - 1));

    printv(data);
}

TEST(Chapter_2_4, HeapSortIntRandom1MElem)
{
    unsigned N = 1'000'000;
    std::vector<int> data;
    data.reserve(N);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, N - 1);

    for(unsigned i = 0; i < N; ++i)
        data.push_back(dis(gen));

    heapSort(data);

    EXPECT_TRUE(isSorted(data, 0, data.size() - 1));
}

