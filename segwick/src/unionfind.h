#ifndef UNIONFIND_H
#define UNIONFIND_H

#include <vector>

template<typename T>
class QuickFind {
public:
    QuickFind(unsigned _n) : N(_n) {}

    // connect p and q
    void connect(unsigned p, unsigned q) {
        // TODO: don't construct vector before hand, just insert up to p or q when connecting.
        if(p >= N) {
            increaseTo(p);
            N = p;
        }
        if(q >= N) {
            increaseTo(q);
            N = q;
        }
    }

    // return true if p and q are connected, false otherwise
    bool connected(unsigned p, unsigned q) {
        return false;
    }

    // return the number of elements
    unsigned capacity() const {
        return N;
    }
private:
    void increaseTo(T val); // TODO: implement!
    unsigned N; // the capacity
    std::vector<T> elements;
};

#endif // UNIONFIND_H
