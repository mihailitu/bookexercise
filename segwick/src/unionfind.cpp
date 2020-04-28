#include "unionfind.h"

UnionFind::UnionFind(unsigned _n) : N(_n)
{
    rootID.resize(N);
    sz.resize(N);
    for(unsigned i = 0; i < N; ++i) {
        rootID[i] = i; // each element is it's own root
        sz[i] = 1;     // with tree size 1
    }
}

void UnionFind::increaseTo(unsigned val)
{
    if (val > N) {
        rootID.resize(val);
        sz.resize(val);
        for(unsigned i = N; i < val; ++i) {
            rootID[i] = i;
            sz[i] = 1;
        }
        N = val;
    }
}

QuickUnionWeighted::QuickUnionWeighted(unsigned n) : UnionFind (n)
{
}

void QuickUnionWeighted::connect(unsigned int p, unsigned int q)
{
    increaseTo(std::max(p, q));

    unsigned pRoot = findRoot(p);
    unsigned qRoot = findRoot(q);
    if (pRoot == qRoot)
        return;

    if (sz[pRoot] < sz[qRoot]) {
        rootID[pRoot] = qRoot;
        sz[qRoot] += sz[pRoot];
    } else {
        rootID[qRoot] = pRoot;
        sz[pRoot] += sz[qRoot];
    }
}

bool QuickUnionWeighted::connected(unsigned int p, unsigned int q)
{
    return (findRoot(p) == findRoot(q));
}

unsigned QuickUnionWeighted::findRoot(unsigned p)
{
    while(p != rootID[p])
        p = rootID[p];

    return p;
}

QuickUnion::QuickUnion(unsigned n) : UnionFind(n)
{
}

void QuickUnion::connect(unsigned int p, unsigned int q)
{
    increaseTo(std::max(p, q));
    unsigned pRoot = findRoot(p);
    unsigned qRoot = findRoot(q);
    rootID[pRoot] = qRoot;
}

bool QuickUnion::connected(unsigned int p, unsigned int q)
{
    return findRoot(p) == findRoot(q);
}

unsigned QuickUnion::findRoot(unsigned p)
{
    while(p != rootID[p])
        p = rootID[p];

    return p;
}

QuickFind::QuickFind(unsigned n) : UnionFind(n)
{
}

// connects p and q
void QuickFind::connect(unsigned p, unsigned q)
{
    // TODO: don't construct vector before hand, just insert up to p or q when connecting.
    increaseTo(std::max(p, q));
    unsigned pID = rootID[p];
    unsigned qID = rootID[q];

    for(unsigned i = 0; i < N; ++i) // change all entries that have rootID[p] as root with rootID[q] as root
        if (rootID[i] == pID)       // (at most 2N+2 array accesses)
            rootID[i] = qID;
}

// return true if p and q are connected, false otherwise
bool QuickFind::connected(unsigned p, unsigned q)
{
    return rootID[p] == rootID[q];
}
