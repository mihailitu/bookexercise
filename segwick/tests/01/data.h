#ifndef DATA_H
#define DATA_H

#include <string>
#include <vector>

/* data file format:
 * N - number of elements
 * p1 q1 - connection (p1, q1 < N)
 * p2 q2
 * ....
 */

void readUFDataFile(const std::string &fName, unsigned &N, std::vector<std::pair<unsigned, unsigned>> &connections);

#endif // DATA_H
