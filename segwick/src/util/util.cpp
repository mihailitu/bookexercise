#include "util.h"
#include "gtest.h"
#include "logger.h"

#include <fstream>

void readInts(const std::string &fName, std::vector<int> &elements)
{
    std::ifstream testFile(fName);
    if (!testFile.is_open()) {
        FAIL() << fName << " not found";
        return;
    }
    int p;
    while (testFile >> p)
        elements.push_back(p);

    log_info("Constructed %lu elements from %s",  elements.size(), fName.c_str());
}

//template<typename T>
//void printv(const std::vector<T> &v)
//{
//    for(unsigned i = 0; i < v.size(); ++i)
//        std::cout << v[i] << ' ';
//    std::cout << std::endl;
//}

//template<typename T>
//bool isSorted(const std::vector<T> &v, unsigned long lo, unsigned long hi)
//{
//    if (v.size() <= 1)
//        return true;
//    if (lo >= hi)
//        return true;
//    for(unsigned long i = lo + 1; i <= hi; ++i)
//        if (!(v[i - 1] <= v[i]))
//            return false;
//    return true;
//}
