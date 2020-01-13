#include <gtest.h>

template<typename T>
void printv(const std::vector<T> &v)
{
    for(unsigned i = 0; i < v.size(); ++i)
        std::cout << v[i] << ' ';
    std::cout << std::endl;
}

template<typename T>
bool isSorted(const std::vector<T> &v, unsigned long lo, unsigned long hi)
{
    if (v.size() == 1)
        return true;
    if (lo >= hi)
        return true;
    for(unsigned long i = lo + 1; i <= hi; ++i)
        if (v[i - 1] > v[i])
            return false;
    return true;
}

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
    std::vector<T> aux(data.size());
    sort(aux, data, 0, data.size() - 1);
}

TEST(Chapter_2_1, MergeSortInt1)
{
    std::vector<int> data = { 1, 3, 6, 4, 2, 4, 1, 4};
    printv(data);

    mergesort(data);

    EXPECT_TRUE(isSorted(data, 0, data.size() - 1));

    printv(data);
}

TEST(Chapter_2_1, MergeSortChar1)
{
    std::string str = "MERGESORTEXAMPLE";
    std::vector<char> data (str.begin(), str.end());
    printv(data);

    mergesort(data);

    EXPECT_TRUE(isSorted(data, 0, data.size() - 1));

    printv(data);
}
