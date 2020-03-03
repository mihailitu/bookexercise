#include "fundamentals.h"

/* 1.2.6 A string s is a circular rotation of a string t if it matches when the characters
 * are circularly shifted by any number of positions; e.g., ACTGACG is a circular shift of
 * TGACGAC, and vice versa. Detecting this condition is important in the study of genomic
 * sequences. Write a program that checks whether two given strings s and t are circular
 * shifts of one another. Hint : The solution is a one-liner with indexOf(), length(), and
 * string concatenation.
 */

/**
 * @brief _1_2_6_CircularStr
 * @param s1
 * @param s2
 * @return true if s2 is circular rotation of s1
 */
bool _1_2_6_CircularStr(const std::string &s1, const std::string &s2)
{
    if(s1.length() != s2.length())
        return false;

    auto slen = s1.length();
    for(unsigned i = 0; i < slen; ++i) {
        int comp = s1.compare(i, slen - i, s2, 0, slen - i);
        if (comp != 0)
            continue;

        comp = s1.compare(0, i, s2, slen - i, i);
        if( comp == 0)
            return true;
    }

    return false;
}

bool _1_2_6_CircularStr1(const std::string &s1, const std::string &s2)
{
    if(s1.length() != s2.length())
        return false;

    auto slen = s1.length();

    for(unsigned i = 0; i < slen; ++i) {
        std::string ss1 = s1.substr(i, slen - i);
        std::string ss2 = s2.substr(0, slen - i);
        if(ss1.compare(ss2) != 0)
            continue;
        std::string css1 = s1.substr(0, i);
        std::string css2 = s2.substr(slen - i, css1.length());
        if(css1.compare(css2) == 0)
            return true;
    }

    return false;
}

bool _1_2_6_CircularStr2(const std::string &s1, const std::string &s2)
{
    if(s1.length() != s2.length())
        return false;

    std::string temp = s1  + s2;

    return temp.find(s2) != std::string::npos;
}

TEST(Fundamentals, _1_2_6_CircularStr1)
{
    ASSERT_TRUE(_1_2_6_CircularStr("abcde", "deabc"));
    ASSERT_TRUE(_1_2_6_CircularStr1("abcde", "deabc"));
    ASSERT_TRUE(_1_2_6_CircularStr2("abcde", "deabc"));

    ASSERT_TRUE(_1_2_6_CircularStr("ACTGACG", "TGACGAC"));
    ASSERT_TRUE(_1_2_6_CircularStr1("ACTGACG", "TGACGAC"));
    ASSERT_TRUE(_1_2_6_CircularStr2("ACTGACG", "TGACGAC"));

    ASSERT_TRUE(_1_2_6_CircularStr("ABCDE", "ABCDE"));
    ASSERT_TRUE(_1_2_6_CircularStr1("ABCDE", "ABCDE"));
    ASSERT_TRUE(_1_2_6_CircularStr2("ABCDE", "ABCDE"));

    ASSERT_TRUE(_1_2_6_CircularStr("ABCDE", "BCDEA"));
    ASSERT_TRUE(_1_2_6_CircularStr1("ABCDE", "BCDEA"));
    ASSERT_TRUE(_1_2_6_CircularStr2("ABCDE", "BCDEA"));
}
