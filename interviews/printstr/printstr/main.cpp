#include <iostream>
#include <string>
#include <vector>

using namespace std;

int getWidth(char ) {
    return 5;
}
int getHeight(int) {
    return 10;
}
int getStrWidth(std::string str) {
    int w = 0;
    for(char c : str)
        w += getWidth(c);
    return w;
}

bool itFits(int w_width, int w_height, const std::string &str) {
    if (str.length() == 0)
        return true;

    size_t i = 0;
    std::vector<string> words;
    size_t start_pos = 0;
    while((i = str.find(' ', start_pos)) != std::string::npos) {
        words.push_back(str.substr(start_pos, i - start_pos));
        start_pos = i +1;
    }

    words.push_back(str.substr(start_pos));

     for(auto w : words)
        std::cout << w << '.';
     std::cout << endl;

    if (w_height < getHeight(0))
        return false;

    std::vector<std::string> lines;
    int current_width = 0;
    int current_heigth = getHeight(0);
    for(auto word : words) {
        current_width += getStrWidth(word);
        if (current_width > w_width) {
            if (current_heigth + getHeight(0) > w_height) {
                return false;
            } else
                current_heigth += getHeight(0);
            current_width = getStrWidth(word);
            if (current_width > w_width)
                return false;
        }
        current_width += getWidth(' ');
    }
    return true;
}

void printFits(const string &str, int w, int h)
{
    cout << "[" << w << ", " << h << "] " << (itFits(w, h, str) ? "true:  " : "false: ") << " " << str << endl;
    std::cout << "-----------\n";
}

int main()
{
    printFits("    ", 20, 10);
    printFits("     ", 20, 10);
    printFits("this is a string", 120, 20);
    printFits("this is a string", 20, 20);
    printFits("12345", 20, 20);
    printFits("1234", 20, 20);
    printFits("1234 5", 20, 20);
    printFits("1234 12345", 20, 20);
    printFits("1234 12345 12345", 20, 20);
    printFits("1234 1234 1234", 20, 20);
    printFits("1234 1234 1234", 20, 30);
    return 0;
}

//width = 120px
//height =  20px

//"This is a string"


//int find(string s, char c, int pos); // -1 on failure, position of c
//bool itWillFit(str, max_width) {

//}


