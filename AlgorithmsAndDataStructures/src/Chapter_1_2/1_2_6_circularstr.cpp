#include "fundamentals.h"

/* 1.2.6 A string s is a circular rotation of a string t if it matches when the characters
 * are circularly shifted by any number of positions; e.g., ACTGACG is a circular shift of
 * TGACGAC, and vice versa. Detecting this condition is important in the study of genomic
 * sequences. Write a program that checks whether two given strings s and t are circular
 * shifts of one another. Hint : The solution is a one-liner with indexOf(), length(), and
 * string concatenation.
 */

bool _1_2_6_CircularStr(const std::string &s1, const std::string &s2)
{
    if(s1.length() != s2.length())
        return false;
}

TEST(Fundamentals, _1_2_6_CircularStr1)
{
    ASSERT_TRUE(_1_2_6_CircularStr("ACTGACG", "TGACGAC"));
    ASSERT_TRUE(!_1_2_6_CircularStr("CTGACG", "TGACGAC"));
}
