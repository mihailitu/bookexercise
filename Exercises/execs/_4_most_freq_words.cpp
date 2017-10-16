#include "_4_most_freq_words.h"
#include <map>
#include <string>
#include <iostream>
#include <istream>
#include <vector>
#include <set>

struct MostCommon {
    std::string word;
    int freq;
    bool operator() (const MostCommon &lhs, const MostCommon &rhs) const {
         return lhs.freq < rhs.freq;
    }
};


void addToHeap(std::string w, int freq, std::set<MostCommon> &mc, int maxWords)
{
    if (mc.size() < maxWords) {
        MostCommon mmc{w, freq};
        // mc.insert(mmc);
        return;
    }

}

/* In a file there are 1 million words . Find 10 most frequent words in that file. */
void _4_most_freq_words()
{
    int k = 3;//10;
    std::map<std::size_t, int> wordCount;
    std::vector<std::string> words = {
        "one", "two", "three", "four", "five",
        "one", "two", "three", "four", "five",
        "one", "two", "three",
        "one", "two",
        "one",

    };

//    auto comp = [&](const MostCommon &lhs, const MostCommon &rhs) { return lhs.freq < rhs.freq; };

//    std::set<MostCommon, std::decltype(comp)> mc(comp);
    std::set<MostCommon> mc;
    for(auto w : words) {
        std::size_t strHash = std::hash<std::string>{}(w);
        auto it = wordCount.find(strHash);
        int wOcc = 0;
        if (it == wordCount.end())
            wordCount[strHash] =  1;
        else {
            ++(*it).second;
            wOcc = (*it).second;
        }
        addToHeap(w, wOcc, mc, k);
    }
}
