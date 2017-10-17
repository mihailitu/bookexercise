#include "_4_most_freq_words.h"
#include <map>
#include <string>
#include <iostream>
#include <istream>
#include <vector>
#include <set>
#include <algorithm>

struct MostCommon {
    std::string word;
    int freq;
    bool operator<(const MostCommon &other) const{
        return freq < other.freq;
    }
};


void addToHeap(std::string w, int freq, std::vector<MostCommon> &mc, unsigned maxWords)
{
    MostCommon mmc{w, freq};
    auto comp = [&](const MostCommon &el) {return el.word.compare(mmc.word) == 0; };

    auto current = std::find_if(mc.begin(), mc.end(), comp);
    if (current != mc.end()) {
        if ((*current).freq >= mmc.freq) {
            return;
        } else {
            (*current).freq = mmc.freq;
            std::sort_heap(mc.begin(), mc.end());
            return;
        }
    }

    if (mc.size() < maxWords) {
        mc.push_back(mmc);
        std::sort_heap(mc.begin(), mc.end());
        return;
    }

    auto it = mc.begin();
    if (it != mc.end()) {
        mc.erase(it);
        mc.push_back(mmc);
        std::sort_heap(mc.begin(), mc.end());
    }
}

/* In a file there are 1 million words . Find 10 most frequent words in that file. */
void _4_most_freq_words()
{
    unsigned k = 4;//10;
    std::map<std::size_t, int> wordCount;
    std::vector<std::string> words = {
        "one", "two", "three", "four", "five",
        "one", "two", "three", "four", "five",
        "one", "two", "three",
        "one", "two",
        "one",

    };

//    auto comp = [&](const MostCommon &lhs, const MostCommon &rhs) { return lhs.freq < rhs.freq; };

    std::vector<MostCommon> mc;
    for(auto w : words) {
        std::size_t strHash = std::hash<std::string>{}(w);
        auto it = wordCount.find(strHash);
        int wOcc = 1;
        if (it == wordCount.end())
            wordCount[strHash] =  1;
        else {
            ++(*it).second;
            wOcc = (*it).second;
        }
        addToHeap(w, wOcc, mc, k);
    }

    for(auto i : mc)
        std::cout << i.word << ' ' << i.freq << std::endl;
}
