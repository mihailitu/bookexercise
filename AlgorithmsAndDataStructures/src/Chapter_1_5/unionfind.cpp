#include "unionfind.h"
#include "gtest.h"

UnionFind::UnionFind(int N) : N(N)
{

}

UnionFind::~UnionFind()
{

}

UnionFindQuickFind::UnionFindQuickFind(int N) : UnionFind (N)
{
    for(int i = 0; i < N; ++i) // N array accesses
        id.push_back(i);
}

void UnionFindQuickFind::union_connect(int p, int q)
{
    int pid = id[p];
    int qid = id[q];
    for(unsigned i = 0; i < id.size(); ++i) { // at most 2N + 2 array accesses
        if (id[i] == pid)
            id[i] = qid;
    }
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

void UnionFindQuickUnion::union_connect(int p, int q)
{
    int i = root(p);
    int j = root(q);
    id[i] = j;
}

bool UnionFindQuickUnion::connected(int p, int q)
{
    return root(p) == root(q);
}
