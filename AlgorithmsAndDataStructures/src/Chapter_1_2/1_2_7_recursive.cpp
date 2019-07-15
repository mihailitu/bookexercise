#include "fundamentals.h"

/* 1.2.7 What does the mystery() recursive function return?
 */

// reversed string
std::string mystery(const std::string &s)
{
    unsigned long N = s.length();
    if (N <= 1)
        return s;
    std::string a = s.substr(0, N/2);
    std::string b = s.substr(N/2, N);
    return mystery(b) + mystery(a);
}

TEST(Fundamentals, _1_2_7_Mystery)
{
    std::string s = mystery("abcd");
    std::cout << s << "\n";
    s = mystery("abc");
    std::cout << s << "\n";
}
