#include <iostream>

#include "exercises.h"
/*
 * Compute the greatest common divisor of two nonnegative integers p and q as follows:
 * If q is 0, the answer is p. If not, divide p by q and take the remainder r.
 * The answer is the greatest common divisor of q and r.
 */
int gcd(int p, int q)
{
    if (q == 0) return p;
    int r = p % q;
    return gcd(q, r);
}

void test_euclids_gcd(int p, int q)
{
    std::cout << "Greatest common divisor for " << p << " and " << q << " is: " << gcd(p, q) << std::endl;
}

TEST(Euclid, Test1)
{
    test_euclids_gcd(233, 312);
}
