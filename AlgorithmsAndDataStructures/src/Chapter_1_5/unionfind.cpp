#include "unionfind.h"
#include "gtest.h"

UnionFind::UnionFind(int N) : N(N), numberOfComponents(N)
{

}

UnionFind::~UnionFind()
{

}

UnionFindQuickUnionWeighted::UnionFindQuickUnionWeighted(int N) : UnionFind (N)
{
    for(int i = 0; i < N; ++i) { // N array accesses
        id.push_back(i);
        sz.push_back(1);
    }
}

int UnionFindQuickUnionWeighted::root(int i)
{
    while(i != id[i]) {
        id[i] = id[id[i]]; // path compression
        i = id[i];
    }
    return i;
}

void UnionFindQuickUnionWeighted::connect(int p, int q)
{
    int i = root(p);
    int j = root(q);
    if (i == j)
        return;

    if (sz[i] < sz[j]) {
        id[i] = j;
        sz[j] += sz[i];
    } else {
        id[j] = i;
        sz[i] += sz[j];
    }
    --numberOfComponents;
}

bool UnionFindQuickUnionWeighted::connected(int p, int q)
{
    return root(p) == root(q);
}


UnionFindQuickFind::UnionFindQuickFind(int N) : UnionFind (N)
{
    for(int i = 0; i < N; ++i) // N array accesses
        id.push_back(i);
}

void UnionFindQuickFind::connect(int p, int q)
{
    int pid = id[p];
    int qid = id[q];

    if(pid == qid)
        return;

    for(unsigned i = 0; i < id.size(); ++i) { // at most 2N + 2 array accesses
        if (id[i] == pid)
            id[i] = qid;
    }

    --numberOfComponents;
}

bool UnionFindQuickFind::connected(int p, int q)
{
    return (id[p] == id[q]);
}

UnionFindQuickUnion::UnionFindQuickUnion(int N) : UnionFind (N)
{
    for(int i = 0; i < N; ++i) // N array accesses
        id.push_back(i);
}

int UnionFindQuickUnion::root(int i)
{
    while(i != id[i])
        i = id[i];
    return i;
}

void UnionFindQuickUnion::connect(int p, int q)
{
    int i = root(p);
    int j = root(q);
    if (i == j)
        return;
    id[i] = j;
    --numberOfComponents;
}

bool UnionFindQuickUnion::connected(int p, int q)
{
    return root(p) == root(q);
}
