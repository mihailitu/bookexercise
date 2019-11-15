#include <iostream>
#include "GFClient.h"

using namespace std;

int main()
{
    // CGigaFlowClient gfclient("tcp://localhost:5555", 1000000);
    CGigaFlowClient gfclient("tcp://office13.anuview.net:5555", 1000000);
    int rc = gfclient.StartListener();
    std::cout << "RC " << rc << std::endl;
    // while() {
    std::this_thread::sleep_for(std::chrono::seconds(60));
    // }

    std::cout << "Ending..." << std::endl;
    gfclient.CloseConnection();
    std::cout << "Ended..." << std::endl;

    rc = gfclient.StartListener();
    std::cout << "RC " << rc << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(10));
    gfclient.CloseConnection();

    return 0;
}
