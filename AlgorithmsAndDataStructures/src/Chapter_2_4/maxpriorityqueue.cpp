#include <gtest/gtest.h>

template<typename T>
class MaxPriorityQueue {
private:
    std::vector<T> pq;
public:
    MaxPriorityQueue(unsigned capacity)
    {
        pq.reserve(capacity + 1);
    }

     bool isEmpty() {
         return pq.size() == 0;
     }

     void insert(T key);

     T delMax();

     void swim(int k);

     void sink(int k);
};

TEST(Chapter_2_4, PriorityQueue)
{

}
