#include <gtest.h>
#include <random>
#include "util.h"

template<typename T>
void merge(std::vector<T> &aux, std::vector<T> &data, unsigned long lo, unsigned long mid, unsigned long hi)
{
    // first and second has to be sorted
    ASSERT_TRUE(isSorted(data, lo, mid));
    ASSERT_TRUE(isSorted(data, mid+1, hi));
    // aux.insert(aux.begin() + lo, data.begin() + lo, data.begin() + hi);
    for(auto k = lo; k <= hi; ++k)
        aux[k] = data[k];

    unsigned long i = lo;
    unsigned long j = mid + 1;

    for(auto k = lo; k <= hi; ++k) {
        if (i > mid)
            data[k] = aux[j++];
        else if (j > hi)
            data[k] = aux[i++];
        else if (aux[i] <= aux[j])
            data[k] = aux[i++];
        else
            data[k] = aux[j++];
    }
    EXPECT_TRUE(isSorted(data, lo, hi));
}

template<typename T>
void sort(std::vector<T> &aux, std::vector<T> &data, unsigned long lo, unsigned long hi)
{
    if (hi <= lo)
        return;
    unsigned long mid = lo + (hi - lo)/2;

    sort(aux, data, lo, mid);
    sort(aux, data, mid + 1, hi);

    merge(aux, data, lo, mid, hi);
}

template<typename T>
void mergesort(std::vector<T> &data)
{
    if (data.size() == 0)
        return;
    std::vector<T> aux(data.size());
    sort(aux, data, 0, data.size() - 1);
}

template<typename T>
void bottomupmergesort(std::vector<T> &data)
{
    if (data.size() == 0)
        return;
    std::vector<T> aux(data.size());
    unsigned long N = data.size();
    for(unsigned long sz = 1; sz < N; sz = 2 * sz )
        for(unsigned long lo = 0; lo < N - sz; lo += sz * 2)
            merge(aux, data, lo, lo + sz - 1, std::min(lo + sz + sz - 1, N - 1));
}


TEST(Chapter_2_2, MergeSortInt)
{
    std::vector<int> data = { 1, 3, 6, 4, 2, 4, 1, 4};
    printv(data);

    mergesort(data);

    EXPECT_TRUE(isSorted(data, 0, data.size() - 1));

    printv(data);
}

TEST(Chapter_2_2, MergeSortChar)
{
    std::string str = "MERGESORTEXAMPLE";
    std::vector<char> data (str.begin(), str.end());
    printv(data);

    mergesort(data);

    EXPECT_TRUE(isSorted(data, 0, data.size() - 1));

    printv(data);
}

TEST(Chapter_2_2, MergeSortIntRandom1MElem)
{
    unsigned N = 10'000'000;
    std::vector<int> data;
    data.reserve(N);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, N - 1);

    for(unsigned i = 0; i < N; ++i)
        data.push_back(dis(gen));

    mergesort(data);

    EXPECT_TRUE(isSorted(data, 0, data.size() - 1));
}

TEST(Chapter_2_2, MergeSortBottomUp1MElem)
{
    unsigned N = 10'000'000;
    std::vector<int> data;
    data.reserve(N);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, N - 1);

    for(unsigned i = 0; i < N; ++i)
        data.push_back(dis(gen));

    bottomupmergesort(data);

    EXPECT_TRUE(isSorted(data, 0, data.size() - 1));
}
