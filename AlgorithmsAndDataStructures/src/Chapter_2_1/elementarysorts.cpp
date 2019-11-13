#include "gtest/gtest.h"
#include "logger.h"
#include <chrono>

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

template<typename T>
void insertionSort(std::vector<T> &a)
{
    auto N = a.size();
    for(decltype (N) i = 0; i < N; ++i) {
        for(decltype (i) j = i; j > 0; --j)
            if (a[j] < a[j-1])
                std::swap(a[j], a[j-1]);
            else
                break;
    }
}

TEST(Chapter_2_1, SelectionSort)
{
    std::vector<int> arr =    { 7, 10, 5, 3, 8, 4, 2, 9, 6};
    std::vector<int> sorted = { 2, 3, 4, 5, 6, 7, 8, 9, 10};

    selectionSort<int>(arr);

    //    for(unsigned i = 0; i < arr.size(); ++i) {
    //        log_info("%d", arr[i]);
    //    }
    for(unsigned i = 0; i < arr.size(); ++i)
        ASSERT_EQ(arr[i], sorted[i]);
}

TEST(Chapter_2_1, InsertionSort)
{
    std::vector<int> arr =    { 7, 10, 5, 3, 8, 4, 2, 9, 6};
    std::vector<int> sorted = { 2, 3, 4, 5, 6, 7, 8, 9, 10};

    insertionSort<int>(arr);

    //    for(unsigned i = 0; i < arr.size(); ++i) {
    //        log_info("%d", arr[i]);
    //    }

    for(unsigned i = 0; i < arr.size(); ++i)
        ASSERT_EQ(arr[i], sorted[i]);
}

TEST(Chapter_2_1, ElementarySorts)
{
    std::vector<int> arr =    { 7, 10, 5, 3, 8, 4, 2, 9, 6};
    std::vector<int> sorted = { 2, 3, 4, 5, 6, 7, 8, 9, 10};

    auto start = std::chrono::system_clock::now();
    insertionSort<int>(arr);
    auto end = std::chrono::system_clock::now();
    log_info("selection sort with %ul elements: %ul", arr.size(), std::chrono::duration<std::chrono::seconds>(end - start));
    //    for(unsigned i = 0; i < arr.size(); ++i) {
    //        log_info("%d", arr[i]);
    //    }

    for(unsigned i = 0; i < arr.size(); ++i)
        ASSERT_EQ(arr[i], sorted[i]);
}
