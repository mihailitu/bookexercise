#include <gtest/gtest.h>

// Max priority queue using binary heap tree
template<typename T>
class MaxPriorityQueue {
private:
    std::vector<T> pq;
    unsigned long N; // maximum priority queue elements
public:
    MaxPriorityQueue(unsigned capacity) :
        N(1)
    {
        pq.reserve(capacity + 1);
    }

     bool isEmpty() {
         return pq.empty();
     }

     void insert(T key) { // at most 1 + lg(N) compares
         pq.insert(key);
         ++N;
         swim(N);
     }

     T delMax() { // At most 2*lg(N) compares
         T max = pq[1];
         std::swap(pq[1], pq[N--]);
         sink(1);
         pq.resize(N);
         return max;
     }

     void swim(int k) {
         while ((k > 1) && (pq[k/2] < pq[k]))
         {
             std::swap(pq[k], pq[k/2]); // parent of node k is k/2
             k = k/2;
         }
     }

     void sink(int k) {
         while (2 * k <= N) // children of node k are 2*k and 2*k+1
         {
             int j = 2*k;
             if ((j < N) && (pq[j] < pq[j+1])) // choose the larger of the two children
                 j++;
             if (!(pq[k] < pq[j]))
                 break;
             std::swap(pq[k], pq[j]);
             k = j;
         }
     }
};

TEST(Chapter_2_4, PriorityQueue)
{
    MaxPriorityQueue<char> mpq(100);
}
