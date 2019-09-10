#include <iostream>

using namespace std;

// you can use includes, for example:
#include <algorithm>
#include <vector>
// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;

/**
 * @brief vec_solution - return smallest number not in vector A
 * @param A -
 * @return smallest nonzero number not in A
 *
 * Eg:
 * [6, 4, 1, 3, 2] -> 5
 * [-1, -2] -> 1
 * [0, 1, 2, 3] -> 4
 */
int vec_solution(vector<int> &A) {
    // write your code in C++14 (g++ 6.2.0)
    std::sort(A.begin(), A.end());
    A.erase( unique( A.begin(), A.end() ), A.end() );
    int result = 1;
    for(unsigned i = 0; i < A.size(); ++i) {
        if (A[i] <= 0)
            continue;
        if (A[i] != result)
            return result;
        ++result;
    }
    return result;
}

/**
 * @brief int_solution - return the number of set bits from prod of A and B
 * @param A positive integer <= 1000000
 * @param B positive integet <= 1000000
 * @return number of bits set to 1 of A * B
 */
int int_solution(int A, int B) {
    // write your code in C++14 (g++ 6.2.0)
    int result = 0;
    if (A<0 || B<0)
        return 0;

    if (A > 1000000 || B > 1000000)
        return 0;

    unsigned long long a = static_cast<unsigned long long>(A);
    unsigned long long b = static_cast<unsigned long long>(B);

    unsigned long long prod = (a * b);
    cout << prod << " = bin(";
    while (prod)
    {
        cout << (prod & 1);
        result += prod & 1;
        prod >>= 1;
    }
    cout << ")" << endl;
    return result;
}

/**
 * @brief find sentences (delimited by . ? !) and max words in solution (" This  is an example  . How many words are there? "
 * @param s
 * @return max word in a sentence
 */
int str_solution(string &s) {
    vector<vector<string>> text;
    int maxWords = 0;
    string word;
    vector<string> sentence;
    for(char c : s) {
        if (c == ' ') {
            if (word.length() > 0) {
                sentence.push_back(word);
                word.clear();
            }
        } else if (c == '.' || c == '!' || c == '?') {
            if (word.length() > 0)
                sentence.push_back(word);
            text.push_back(sentence);
            word.clear();
            sentence.clear();
        } else {
            word.push_back(c);
        }
    }
    if (word.size()> 0) {
        sentence.push_back({word});
        word.clear();
    }
    if(sentence.size() > 0) {
        text.push_back(sentence);
        sentence.clear();
    }

    for(auto sentence : text) {
        int noWordsInSentence = static_cast<int>(sentence.size());
        if (maxWords < noWordsInSentence)
            maxWords = noWordsInSentence;
    }

    return maxWords;
}

int main()
{
    std::cout << "---- Probl 1 ----" << endl;

    vector<vector<int>> vectors = {
        {6, 4, 1, 3, 2},
        {-1, -2},
        {0, 1, 2, 3}
    };

    for(auto v : vectors) {
        int result = vec_solution(v);
        std::cout << result << '\n';
    }
    std::cout << "---- Probl 1 ----" << endl;

    std::cout << "---- Probl 2 ----" << endl;

    std::vector<string> texts = {
        "empty",
        "hey. How Are you",
        "We test coders. Give us a try?",
        "Forget  CVs..Save time . x x",
        " . ",
        "!!!!",
        ".",
        " a ...!?. ..!"
    };
    for(auto s : texts) {
        int result = str_solution(s);
        std::cout << s << '\n';
        std::cout << result << '\n';
    }

    std::cout << "---- Probl 2 ----" << endl;

    std::cout << "---- Probl 3 ----" << endl;

    std::vector<std::vector<int>> prods = {
        {3, 7},
        {3, 1},
        {2, 1},
        {0, 5},
        {1000000, 1000000},
        {1000000000, 1000000000}
    };
    for(auto v : prods) {
        int result = int_solution(v[0], v[1]);
        std::cout << result << '\n';
    }

    std::cout << "---- Probl 3 ----" << endl;

    return 0;
}
