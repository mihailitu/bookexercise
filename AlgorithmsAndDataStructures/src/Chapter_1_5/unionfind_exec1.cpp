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
    unsigned N;
    std::vector<unsigned> id; // roots
    std::vector<unsigned> sz; // tree sz
    unsigned components;
    bool is_valid_node(int p) {
        return (p > 0);
    }
public:
    UF(unsigned n) : N(n), components(n - 1) {
        for(unsigned i = 0; i < N; ++i) {
            id.push_back(i);
            sz.push_back(1);
        }
    }

    int find_root(unsigned p) {
        if (!is_valid_node(p))
            return -1;

        while(p != id[p])
            p = id[p];
        return p;
    }

    bool connected(unsigned p, unsigned q) {
        if (!is_valid_node(p) || !is_valid_node(q))
            return false;
        return find_root(p) == find_root(q);
    }

    void connect(unsigned p, unsigned q) {
        if (!is_valid_node(p) || !is_valid_node(q))
            return;

        if (connected(p, q))
            return;

        unsigned pid = find_root(p);
        unsigned qid = find_root(q);
        if (sz[pid] < sz[qid]) {
            id[pid] = qid;
            sz[qid] += sz[pid];
        } else {
            id[qid] = pid;
            sz[pid] += sz[qid];
        }
        --components;
    }

    void print() {
        for(unsigned i = 0; i < id.size(); ++i) {
            std::cout << id[i] << ' ';
        }
        std::cout << '\n';
        for(unsigned i = 0; i < sz.size(); ++i) {
            std::cout << sz[i] << ' ';
        }
        std::cout << "\n\n";
    }

    int count() {
        return components;
    }
};

int all_connected(const unsigned N, const std::vector<std::pair<unsigned, unsigned>> &connections) {
    UF uf(N);
    if (uf.count() == 1)
        return 0;

    uf.print();
    unsigned when = 0;
    for(when = 0; when < connections.size(); ++when) {
        uf.connect(connections[when].first, connections[when].second);
        std::cout << "Count: " << uf.count() << '\n';
        uf.print();
        if (uf.count() == 1)
            return when;
    }

    return -1;
}

TEST(Chapter_1_5, Ex1_SocialNetworkConnectivityInput1)
{
        unsigned N = 5;
        std::vector<std::pair<unsigned, unsigned>> ex = {
            {1, 2},
            {3, 4}
        };

        int when = all_connected(N, ex);
        ASSERT_EQ(when, -1);
}

TEST(Chapter_1_5, Ex1_SocialNetworkConnectivityInput2)
{
    unsigned N = 5;
    std::vector<std::pair<unsigned, unsigned>> ex = {
        {0, 1},
        {1, 2},
        {2, 3},
        {3, 4},
        {2, 0}
    };

    int when = all_connected(N, ex);
    ASSERT_EQ(when, 3);
}

/*
Union-find with specific canonical element. Add a method find() to the union-find data type so that find(i) returns the largest element in the connected component containing iii. The operations, union(), connected(), and find() should all take logarithmic time or better.

For example, if one of the connected components is {1,2,6,9}\{1, 2, 6, 9\}{1,2,6,9}, then the find() method should return 999 for each of the four elements in the connected components.
*/
TEST(Chapter_1_5, Ex2_LargestElementInComponent)
{

}

/*
 * Successor with delete. Given a set of n integers S={0,1,...,n−1}  and a sequence of requests of the following form:

    Remove x from S
    Find the successor of x: the smallest y in S such that y >= x.

design a data type so that all operations (except construction) take logarithmic time or better in the worst case.
*/
TEST(Chapter_1_5, Ex3_LargestElementInComponent)
{

}
