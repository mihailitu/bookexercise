#ifndef UNIONFIND_H
#define UNIONFIND_H

#include <vector>

class QuickFind {
public:
    QuickFind(unsigned _n) : N(_n) {
        rootID.resize(N);
        for(unsigned i = 0; i < N; ++i)
            rootID[i] = i; // each element is it's own root
    }

    // connect p and q
    void connect(unsigned p, unsigned q) {
        // TODO: don't construct vector before hand, just insert up to p or q when connecting.
        if(p >= N) {
            // increaseTo(p);
            N = p;
        }
        if(q >= N) {
            // increaseTo(q);
            N = q;
        }

        unsigned pID = rootID[p];
        unsigned qID = rootID[q];

        for(unsigned i = 0; i < N; ++i) // change all entries that have rootID[p] as root with rootID[q] as root
            if (rootID[i] == pID)       // (at most 2N+2 array accesses)
                rootID[i] = qID;
    }

    // return true if p and q are connected, false otherwise
    bool connected(unsigned p, unsigned q) {
        return rootID[p] == rootID[q];
    }

    // return the number of elements
    unsigned capacity() const {
        return N;
    }
private:
    void increaseTo(unsigned val); // TODO: implement!
    unsigned N; // the capacity
    std::vector<unsigned> rootID;
};

#endif // UNIONFIND_H
