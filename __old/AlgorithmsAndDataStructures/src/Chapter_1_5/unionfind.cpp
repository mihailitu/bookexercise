#include "unionfind.h"
#include "gtest.h"

UnionFind::UnionFind(unsigned N) : N(N), numberOfComponents(N-1)
{
    for(unsigned i = 0; i < N; ++i) // N array accesses
        id.push_back(i);
}

UnionFind::~UnionFind()
{

}

void UnionFind::print() const
{
    for(unsigned i = 0; i < id.size(); ++i)
        std::cout << id[i] << ' ';
    std::cout << '\n';
}

UnionFindQuickUnionWeighted::UnionFindQuickUnionWeighted(unsigned N) : UnionFind (N)
{
    for(unsigned i = 0; i < N; ++i) { // N array accesses
        sz.push_back(1);
    }
}

unsigned UnionFindQuickUnionWeighted::root(unsigned i)
{
    while(i != id[i]) {
        id[i] = id[id[i]]; // path compression
        i = id[i];
    }
    return i;
}

void UnionFindQuickUnionWeighted::connect(unsigned p, unsigned q)
{
    unsigned i = root(p);
    unsigned j = root(q);
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

bool UnionFindQuickUnionWeighted::connected(unsigned p, unsigned q)
{
    return root(p) == root(q);
}

void UnionFindQuickUnionWeighted::print() const
{
    for(unsigned i = 0; i < id.size(); ++i)
        std::cout << id[i] << ' ';
    std::cout << '\n';
    for(unsigned i = 0; i < sz.size(); ++i)
        std::cout << sz[i] << ' ';
    std::cout << "\n\n";
}

UnionFindQuickFind::UnionFindQuickFind(unsigned N) : UnionFind (N)
{
}

void UnionFindQuickFind::connect(unsigned p, unsigned q)
{
    unsigned pid = id[p];
    unsigned qid = id[q];

    if(pid == qid)
        return;

    for(unsigned i = 0; i < id.size(); ++i) { // at most 2N + 2 array accesses
        if (id[i] == pid)
            id[i] = qid;
    }

    --numberOfComponents;
}

bool UnionFindQuickFind::connected(unsigned p, unsigned q)
{
    return (id[p] == id[q]);
}

UnionFindQuickUnion::UnionFindQuickUnion(unsigned N) : UnionFind (N)
{
}

unsigned UnionFindQuickUnion::root(unsigned i)
{
    while(i != id[i])
        i = id[i];
    return i;
}

void UnionFindQuickUnion::connect(unsigned p, unsigned q)
{
    unsigned i = root(p);
    unsigned j = root(q);
    if (i == j)
        return;
    id[i] = j;
    --numberOfComponents;
}

bool UnionFindQuickUnion::connected(unsigned p, unsigned q)
{
    return root(p) == root(q);
}
