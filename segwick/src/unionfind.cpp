#include "unionfind.h"

QuickFind::QuickFind(unsigned _n) : N(_n) {
    rootID.resize(N);
    for(unsigned i = 0; i < N; ++i)
        rootID[i] = i; // each element is it's own root
}

// connect p and q
void QuickFind::connect(unsigned p, unsigned q) {
    // TODO: don't construct vector before hand, just insert up to p or q when connecting.
    increaseTo(std::max(p, q));
    unsigned pID = rootID[p];
    unsigned qID = rootID[q];

    for(unsigned i = 0; i < N; ++i) // change all entries that have rootID[p] as root with rootID[q] as root
        if (rootID[i] == pID)       // (at most 2N+2 array accesses)
            rootID[i] = qID;
}

// return true if p and q are connected, false otherwise
bool QuickFind::connected(unsigned p, unsigned q) {
    return rootID[p] == rootID[q];
}

// return the number of elements
unsigned QuickFind::capacity() const {
    return N;
}

void QuickFind::increaseTo(unsigned val) {
    if (val >= N) {
        rootID.resize(val);
        for(unsigned i = N; i < val; ++i)
            rootID[i] = i;
        N = val;
    }
}
