#ifndef UNIONFIND_H
#define UNIONFIND_H

#include <vector>

template<typename T>
class UnionFind {
public:
    UnionFind(unsigned _n) : N(_n) {}

    // connect p and q
    void connect(unsigned p, unsigned q);

    // return true if p and q are connected, false otherwise
    bool connected(unsigned p, unsigned q);

    // return the number of elements
    unsigned capacity() const {
        return N;
    }
private:
    unsigned N; // the capacity
    std::vector<std::vector<T>> elements;
};

#endif // UNIONFIND_H
