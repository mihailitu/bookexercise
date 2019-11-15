#include <iostream>
#include "GFClient.h"

using namespace std;

int main()
{
    CGigaFlowClient gfclient("tcp://office13.anuview.net:5555", 1000000);
    gfclient.StartListener();

    // while() {
    std::this_thread::sleep_for(std::chrono::seconds(10));
    // }

    std::cout << "Ending...";
    gfclient.CloseConnection();
    return 0;
}
