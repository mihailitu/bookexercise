#ifndef UNIONFIND_H
#define UNIONFIND_H

#include <vector>

class UnionFind
{
public:
    UnionFind(unsigned n);
    // connect p and q
    virtual void connect(unsigned p, unsigned q) = 0;

    // return true if p and q are connected, false otherwise
    virtual bool connected(unsigned p, unsigned q) = 0;

    // return the number of elements
    unsigned capacity() const {
        return N;
    }
protected:
    void increaseTo(unsigned val);
    unsigned N; // the capacity
    std::vector<unsigned> rootID;
};

class QuickUnion : public UnionFind
{
public:
    QuickUnion(unsigned n);

    // connect p and q
    void connect(unsigned p, unsigned q);

    // return true if p and q are connected, false otherwise
    bool connected(unsigned p, unsigned q);

private:
    unsigned findRoot(unsigned p);
};

class QuickFind : public UnionFind{
public:
    QuickFind(unsigned n);

    // connect p and q
    void connect(unsigned p, unsigned q);

    // return true if p and q are connected, false otherwise
    bool connected(unsigned p, unsigned q);
};

#endif // UNIONFIND_H
