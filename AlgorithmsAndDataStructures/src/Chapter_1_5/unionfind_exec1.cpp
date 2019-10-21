#include "gtest.h"

#include <vector>
/*
 * Social network connectivity.
 * Given a social network containing n members and a log file containing m timestamps at which times pairs of members formed friendships,
 * design an algorithm to determine the earliest time at which all members are connected (i.e., every member is a friend of a friend of a friend ... of a friend).
 * Assume that the log file is sorted by timestamp and that friendship is an equivalence relation.
 * The running time of your algorithm should be m log n or better and use extra space proportional to n.
 */

class UF {
    int N;
    std::vector<int> v; // roots
    std::vector<int> sz; // tree sz
    int components;
    bool is_valid_node(int p) {
        return (p > 0 && p < N);
    }
public:
    UF(int n) : N(n), components(n) {
        if (N < 0) {
            N = 0;
            components = 0;
        }
        for(int i = 0; i < N; ++i) {
            v.push_back(i);
            sz.push_back(1);
        }
    }

    int find_root(int p) {
        if (!is_valid_node(p))
            return -1;

        while(p != v[p])
            p = v[p];
        return p;
    }

    bool connected(int p, int q) {
        if (!is_valid_node(p) || !is_valid_node(q))
            return false;
        return find_root(p) == find_root(q);
    }

    void connect(int p, int q) {
        if (!is_valid_node(p) || !is_valid_node(q))
            return;
    }

    int count() {
        return components;
    }
};

TEST(Chapter_1_5, Ex1_SocialNetworkConnectivity)
{

}
