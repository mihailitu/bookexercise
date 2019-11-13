#include "gtest/gtest.h"
#include "logger.h"
#include <chrono>
#include <random>

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

template<typename T>
void shellSort(std::vector<T> &a)
{
    auto N = a.size();

    decltype(N) h = N;
    while (h < N/3)
        h = 3*h + 1;

    while(h >= 1) {
        for(decltype (N) i = h; i < N; ++i) {
            for(decltype (i) j = i; j >= h; j -= h)
                if (a[j] < a[j-h])
                    std::swap(a[j], a[j-h]);
        }
        h = h / 3;
    }
}

TEST(Chapter_2_1, SelectionSort)
{
    std::vector<int> arr =    { 7, 10, 5, 3, 8, 4, 2, 9, 6};
    std::vector<int> sorted = { 2, 3, 4, 5, 6, 7, 8, 9, 10};

    selectionSort<int>(arr);

    for(unsigned i = 0; i < arr.size(); ++i)
        ASSERT_EQ(arr[i], sorted[i]);
}

TEST(Chapter_2_1, InsertionSort)
{
    std::vector<int> arr =    { 7, 10, 5, 3, 8, 4, 2, 9, 6};
    std::vector<int> sorted = { 2, 3, 4, 5, 6, 7, 8, 9, 10};

    insertionSort<int>(arr);

    for(unsigned i = 0; i < arr.size(); ++i)
        ASSERT_EQ(arr[i], sorted[i]);
}

TEST(Chapter_2_1, ShellSort)
{
    std::vector<int> arr =    { 7, 10, 5, 3, 8, 4, 2, 9, 6};
    std::vector<int> sorted = { 2, 3, 4, 5, 6, 7, 8, 9, 10};

    shellSort<int>(arr);

    for(unsigned i = 0; i < arr.size(); ++i)
        ASSERT_EQ(arr[i], sorted[i]);
}

TEST(Chapter_2_1, TimedElementarySorts)
{
    unsigned N = 100'000;
    std::vector<int> arr;

    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> dis(0, N - 1);

    for(unsigned i = 0; i < N; ++i)
        arr.push_back(dis(gen));

    std::vector<int> sorted = arr;
    std::vector<int> unsorted = arr;
    std::sort(sorted.begin(), sorted.end());

    {
        auto start = std::chrono::system_clock::now();
        selectionSort<int>(arr);
        auto end = std::chrono::system_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
        log_info("selection sort with %lu elements: %lu seconds", arr.size(), duration.count());

        for(unsigned i = 0; i < arr.size(); ++i)
            EXPECT_EQ(arr[i], sorted[i]);
    }

    arr = unsorted;
    {
        auto start = std::chrono::system_clock::now();
        insertionSort<int>(arr);
        auto end = std::chrono::system_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
        log_info("insertion sort with %lu elements: %lu seconds", arr.size(), duration.count());

        for(unsigned i = 0; i < arr.size(); ++i)
            EXPECT_EQ(arr[i], sorted[i]);
    }

    arr = unsorted;
    {
        auto start = std::chrono::system_clock::now();
        shellSort<int>(arr);
        auto end = std::chrono::system_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
        log_info("shellsort with %lu elements: %lu seconds", arr.size(), duration.count());

        for(unsigned i = 0; i < arr.size(); ++i)
            EXPECT_EQ(arr[i], sorted[i]);
    }

}
