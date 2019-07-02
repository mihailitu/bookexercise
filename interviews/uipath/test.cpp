#include <iostream>
#include <string>
#include <bitset>
#include <vector>
#include <map>

using namespace std;


int binaryOnes(int n) {
    constexpr int intSz = sizeof(int);
    std::string binary = std::bitset<intSz>(n).to_string();
    int ones = 0;
    for(char c : binary)
        if(c=='1')
            ++ones;
    return ones;
}

void sort(vector<int> &orig, vector<int> &binary)
{
    unsigned sz = orig.size();
    for(unsigned i = 0; i < sz - 1; ++i)
        for(unsigned j = 0; j < sz - i - 1; ++j)
            if(binary[j] > binary[j+1]) {
                std::swap(binary[j], binary[j+1]);
                std::swap(orig[j], orig[j+1]);
            } else if ((binary[j] == binary[j+1]) &&
                       (orig[j] > orig[j+1])) {
                std::swap(binary[j], binary[j+1]);
                std::swap(orig[j], orig[j+1]);
            }
}

vector<int> rearrange(vector<int> elements) {
    std::vector<int> result;
    std::vector<int> byOnes;
    for(int el : elements) {
        byOnes.push_back(binaryOnes(el));
    }

    sort(elements, byOnes);

    for(unsigned i = 0; i < elements.size(); ++i) {
        std::cout << elements[i] << " " << byOnes[i] << '\n';
    }

    return result;
}

//int main()
//{
//    rearrange({1, 2, 5, 9, 9, 1, 2, 3});

//    std::vector<int> el;
//    for(int i = 1; i < 100000; ++i)
//        el.push_back(i);
//    rearrange(el);
//}
