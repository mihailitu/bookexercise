#ifndef UNIONFIND_H
#define UNIONFIND_H

#include <vector>

class UnionFind
{
    int N;
public:
    UnionFind(int N); // initialize UnionFind data structure with objects N objects (from 0 to N-1)
    virtual void union_connect(int p, int q) = 0; // add a connection between p and q
    virtual bool connected(int p, int q) = 0; // are p and q in the same component?
    virtual int count() {return N; }
    virtual ~UnionFind();
};

class UnionFindQuickFind : public UnionFind
{
    std::vector<int> id;
public:
    UnionFindQuickFind(int N); // initialize UnionFind data structure with objects N objects (from 0 to N-1)
    void union_connect(int p, int q); // add a connection between p and q
    bool connected(int p, int q); // are p and q in the same component?
};

class UnionFindQuickUnion : public UnionFind
{
    std::vector<int> id;

    int root(int i);
public:
    UnionFindQuickUnion(int N); // initialize UnionFind data structure with objects N objects (from 0 to N-1)
    void union_connect(int p, int q); // add a connection between p and q
    bool connected(int p, int q); // are p and q in the same component?
};

#endif // UNIONFIND_H