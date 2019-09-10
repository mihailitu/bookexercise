#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

//unicomp6.unicomp.net - - [01/Jul/1995:00:00:06 -0400] "GET /shuttle/countdown/ HTTP/1.0" 200 3985
//burger.letters.com - - [01/Jul/1995:00:00:11 -0400] "GET /shuttle/countdown/liftoff.html HTTP/1.0" 304 0
//burger.letters.com - - [01/Jul/1995:00:00:12 -0400] "GET /images/NASA-logosmall.gif HTTP/1.0" 304 0
//burger.letters.com - - [01/Jul/1995:00:00:12 -0400] "GET /shuttle/countdown/video/livevideo.gif HTTP/1.0" 200 0
//d104.aa.net - - [01/Jul/1995:00:00:13 -0400] "GET /shuttle/countdown/ HTTP/1.0" 200 3985
//unicomp6.unicomp.net - - [01/Jul/1995:00:00:14 -0400] "GET /shuttle/countdown/count.gif HTTP/1.0" 200 40310
//unicomp6.unicomp.net - - [01/Jul/1995:00:00:14 -0400] "GET /images/NASA-logosmall.gif HTTP/1.0" 200 786
//unicomp6.unicomp.net - - [01/Jul/1995:00:00:14 -0400] "GET /images/KSC-logosmall.gif HTTP/1.0" 200 1204
//d104.aa.net - - [01/Jul/1995:00:00:15 -0400] "GET /shuttle/countdown/count.gif HTTP/1.0" 200 40310
//d104.aa.net - - [01/Jul/1995:00:00:15 -0400] "GET /images/NASA-logosmall.gif HTTP/1.0" 200 786

std::string getGif(string str)
{
    std::string::size_type pos = str.find(".gif");
    if( pos != string::npos) {
        string::size_type slash = str.rfind("/", pos);
        if(slash != string::npos && slash < pos)
            return string(str.data() + slash + 1, str.data() + pos + 4);
    }
    return "";
}

int getResponseCode(string str) {
    string http = "HTTP/1.0\" ";
    std::string::size_type pos = str.find(http);
    std::string::size_type lastSpace = str.find_last_of(' ');
    if( pos != string::npos && lastSpace != string::npos) {
        string respCode = string(str.data() + pos + http.size(), str.data() + lastSpace);
        std::cout << respCode << '\n';
        int responseCode = stoi(respCode);
        return responseCode;
    }
    return -1;
}

int main()
{
    vector<string> files = {
        "input001.txt",
    };
    for(string file : files) {
        fstream infile(file);
        if(!infile.is_open()) {
            cout << "No file " << file << '\n';
            continue;
        }
        string line;
        while(std::getline(infile, line)) {
            std::cout << "Line: " << line << '\n';
            std::cout << getGif(line) << '\n';
            std::cout << getResponseCode(line) << '\n';

        }
    }
}
