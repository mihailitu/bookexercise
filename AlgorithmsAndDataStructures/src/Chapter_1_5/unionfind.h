#ifndef UNIONFIND_H
#define UNIONFIND_H

#include <vector>

class UnionFind
{
protected:
    int N;
    std::vector<int> id;
    int numberOfComponents; // number of components
public:
    UnionFind(int N); // initialize UnionFind data structure with objects N objects (from 0 to N-1)
    virtual void connect(int p, int q) = 0; // add a connection between p and q
    virtual bool connected(int p, int q) = 0; // are p and q in the same component?
    virtual int count() const {return numberOfComponents;}
    virtual void print() const;
    virtual ~UnionFind();
};

class UnionFindQuickUnionWeighted : public UnionFind
{

    std::vector<int> sz;

    int root(int i);
public:
    UnionFindQuickUnionWeighted(int N); // initialize UnionFind data structure with objects N objects (from 0 to N-1)
    void connect(int p, int q); // add a connection between p and q
    bool connected(int p, int q); // are p and q in the same component?
    void print() const;
};

class UnionFindQuickFind : public UnionFind
{
public:
    UnionFindQuickFind(int N); // initialize UnionFind data structure with objects N objects (from 0 to N-1)
    void connect(int p, int q); // add a connection between p and q
    bool connected(int p, int q); // are p and q in the same component?
};

class UnionFindQuickUnion : public UnionFind
{
    int root(int i);
public:
    UnionFindQuickUnion(int N); // initialize UnionFind data structure with objects N objects (from 0 to N-1)
    void connect(int p, int q); // add a connection between p and q
    bool connected(int p, int q); // are p and q in the same component?
};

#endif // UNIONFIND_H
