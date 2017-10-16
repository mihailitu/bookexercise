#include "_3_remove_dup_char.h"
#include <vector>
#include <string>
#include <list>
#include <iostream>

/* 3. Remove Alternate Duplicate characters from a char array you have to do it in Place.Like keeping only the odd occurences of each character.
    Example: Input: “you got beautiful eyes”Output: ”you gtbeaiful es”
    Allowed Time Complexity was O(n) and Space Complexity was O(1)
*/
void _3_remove_dup_char()
{

    std::string ss = "you got beautiful eyes";
    {
        /* method 1 - O(n2) */
        std::vector<char> s(ss.begin(), ss.end());
        auto  c = s.begin();
        while(c != s.end()) {
            auto i = c;
            ++i;
            int occ = 0;
            while(i != s.end()) {
                if (*i == *c) {
                    ++occ;
                    if(occ % 2 != 0)
                        s.erase(i);
                }
                ++i;
            }
            ++c;
        }
        for(auto i : s)
            std::cout << i;
        std::cout << std::endl;
    }

    { /* method 2 - O(N) */
        std::list<char> s(ss.begin(), ss.end());
        std::vector<int> occ(127, 0);

        auto c = s.begin();
        while(c != s.end()) {
            ++occ[*c];
            if((occ[*c] % 2 == 0)) {
                s.erase(c++);
                continue;
            }
            ++c;
        }
        for(auto i : s)
            std::cout << i;
        std::cout << std::endl;

    }
}
