#ifndef UNIONFIND_H
#define UNIONFIND_H


class UnionFind
{
    int N;
public:
    UnionFind(int no); //initialize with n objects
    void connect(int p, int q); // add a connection between p and q
    bool connected(int p, int q); // are p and q in the same component?

    int find(int p); // component identifier for p (0... N-1
    int count() const; // number of components

};

#endif // UNIONFIND_H
