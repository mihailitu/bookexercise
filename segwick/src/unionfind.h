#ifndef UNIONFIND_H
#define UNIONFIND_H

#include <vector>


class QuickFind {
public:
    QuickFind(unsigned _n);

    // connect p and q
    void connect(unsigned p, unsigned q);

    // return true if p and q are connected, false otherwise
    bool connected(unsigned p, unsigned q);

    // return the number of elements
    unsigned capacity() const;
private:
    void increaseTo(unsigned val);
    unsigned N; // the capacity
    std::vector<unsigned> rootID;
};

#endif // UNIONFIND_H
