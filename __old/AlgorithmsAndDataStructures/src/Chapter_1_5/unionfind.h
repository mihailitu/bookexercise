#ifndef UNIONFIND_H
#define UNIONFIND_H

#include <vector>

class UnionFind
{
protected:
    unsigned N;
    std::vector<unsigned> id;
    unsigned numberOfComponents; // number of components
public:
    UnionFind(unsigned N); // initialize UnionFind data structure with objects N objects (from 0 to N-1)
    virtual void connect(unsigned p, unsigned q) = 0; // add a connection between p and q
    virtual bool connected(unsigned p, unsigned q) = 0; // are p and q in the same component?
    virtual unsigned count() const {return numberOfComponents;}
    virtual void print() const;
    virtual ~UnionFind();
};

class UnionFindQuickUnionWeighted : public UnionFind
{

    std::vector<int> sz;

    unsigned root(unsigned i);
public:
    UnionFindQuickUnionWeighted(unsigned N); // initialize UnionFind data structure with objects N objects (from 0 to N-1)
    void connect(unsigned p, unsigned q); // add a connection between p and q
    bool connected(unsigned p, unsigned q); // are p and q in the same component?
    void print() const;
};

class UnionFindQuickFind : public UnionFind
{
public:
    UnionFindQuickFind(unsigned N); // initialize UnionFind data structure with objects N objects (from 0 to N-1)
    void connect(unsigned p, unsigned q); // add a connection between p and q
    bool connected(unsigned p, unsigned q); // are p and q in the same component?
};

class UnionFindQuickUnion : public UnionFind
{
    unsigned root(unsigned i);
public:
    UnionFindQuickUnion(unsigned N); // initialize UnionFind data structure with objects N objects (from 0 to N-1)
    void connect(unsigned p, unsigned q); // add a connection between p and q
    bool connected(unsigned p, unsigned q); // are p and q in the same component?
};

#endif // UNIONFIND_H
