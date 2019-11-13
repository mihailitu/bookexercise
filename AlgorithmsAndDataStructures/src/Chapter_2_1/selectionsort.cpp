#include "gtest/gtest.h"
#include "logger.h"

template <typename T>
void selectionSort(std::vector<T> &arr) {
    auto N = arr.size();
    for(decltype (N) i = 0; i < N; ++i) {
        auto min = i;
        for(decltype (N) j = i + 1; j < N; ++j)
            if (arr[j] < arr[min])
                min = j;

        std::swap(arr[i], arr[min]);
    }
}

TEST(Chapter_2_1, SelectionSort)
{
    std::vector<int> arr =    { 7, 10, 5, 3, 8, 4, 2, 9, 6};
    std::vector<int> sorted = { 2, 3, 4, 5, 6, 7, 8, 9, 10};
    selectionSort<int>(arr);
    for(unsigned i = 0; i < arr.size(); ++i) {
        log_info("%d", arr[i]);
    }
    for(unsigned i = 0; i < arr.size(); ++i)
        ASSERT_EQ(arr[i], sorted[i]);
}
