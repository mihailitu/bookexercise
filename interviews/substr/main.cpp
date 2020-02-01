#include <iostream>
#include <string>
#include <vector>
/*
 * Determine if a string is a substring in anohter.
 * The catch is that the order of letter can be different.
 * Eg.: 'abc' is a substring of 'rbca'
 */

unsigned lettersNo()
{
    return static_cast<int>('z') - static_cast<int>('a');
}

unsigned charIdx(char c) {
    return static_cast<unsigned>(c) - static_cast<unsigned>('a');
}

void countLetter(const std::string &str, size_t startIdx, size_t count, std::vector<unsigned> &letters)
{
    for(size_t i = startIdx; i < count; ++i)
        ++letters[charIdx(str[i])];
}

bool vequal(const std::vector<unsigned> &v1, const std::vector<unsigned> &v2)
{
    return std::equal(v1.begin(), v1.end(), v2.begin(), v2.end());
}

bool isSubstr(const std::string &str, const std::string &substr, size_t &idx)
{
    if (substr.length() == 0)
        return true;
    if (str.length() < substr.length())
        return false;

    unsigned lettersInAlfabet =lettersNo();
    std::vector<unsigned> substrCount(lettersInAlfabet); // count the letters from substr
    std::vector<unsigned> strCount(lettersInAlfabet);    // for each possible substr from str, count the letters and compare with substrCount

    countLetter(substr, 0, substr.length(), substrCount);
    countLetter(str, 0, substr.length(), strCount);
    if (vequal(substrCount, strCount)) {
        idx = 0;
        return true;
    }

    for(size_t i = 1; i < str.length() - substr.length(); ++i) {
        --strCount[charIdx(str[i])];
        ++strCount[charIdx(str[i+str.length()])];

        if (vequal(substrCount, strCount)) {
            idx = i;
            return true;
        }
    }
    return false;
}

int main()
{
    {
        std::string str = "rbca";
        std::string subStr = "abc";
        size_t idx = 0;
        bool isTrue = isSubstr(str, subStr, idx);
        std::cout << isTrue << " " << (isTrue ? std::to_string(idx) : "") << std::endl;
    }
    return 0;
}
