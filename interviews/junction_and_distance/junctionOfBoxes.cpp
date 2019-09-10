/**

You are working for a telecomunication company that is trying to upgrade junction boxes over Techlandia. Some of the junction boxes have already been upgraded and other boxes have not. Your task is to identify the oldest boxes that need to be upgraded first but leaving the newer model boxes so that they will not be prioritized.

All the junction boxes are identified by an alphanumeric identifier, followed by a space delimited version information. The older generation uses space delimited lowecase English stings to identify the version, but the newer generation uses space delimited positive integers to identify the version. Your task is to sort the junction boxes in the following order:
1. The older generation junction boxes with the earliest lexicographic version should come first
2. If there are any ties in the older generation, ties should be broken by the alphanumeric identifier
3. Finally, the newer generation boxes should also be returned, in the original order they were in the List.

Write a function or method to return the junction boxes in the specified order.

Input:
    The input to the function/method consists of two arguments:
        - numberOfBoxes, an integer representing the number of junction boxes
        - boxList, a list of String representing all of the identifiers and version information

Output:
    Return a list of strings representing the correctly ordered junction boxes.

Note:
    The junction box identifier consists of only lowe case English characters and numbers

Example:
    Input:
        numberOfBoxes = 6
        boxList = {
                    "ykc B2 01",
                    "eo first qpx",
                    "09z cat hamster",
                    "06f 12 25 6",
                    "az0 first qpx",
                    "236 cat dog rabbit snake"
                }

    Output:
        {
            "236 cat dog rabbit snake",
            "09z cat hamster",
            "az0 first qpx",
            "eo first qpx",
            "ykc B2 01",
            "06f 12 25 6"
        }
*/
#include <vector>
#include <string>
using namespace std;
vector<string> oderedJunctionBoxes(int /*numberOfBoxes*/, std::string /*boxList*/)
{
    return {};
}
