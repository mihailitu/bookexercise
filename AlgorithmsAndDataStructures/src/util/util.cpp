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
