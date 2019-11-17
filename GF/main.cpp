#include "GFClient.h"

#include <fstream>
#include <iostream>

std::string current_time();
std::vector<uint8_t> get_ip(const flatbuffers::Vector<uint8_t> *ip);
void write_ip(std::ostream &out, const flatbuffers::Vector<uint8_t> *ip);
void write_gf_record(std::ostream &out, const GigaFlow::Data::GFRecord * gfr);

namespace {
    std::ofstream out;
}


void zmqMessageHandler(const std::string &gfName, const GigaFlow::Data::GFRecord *gfRecord)
{
    out << gfName << " #: ";
    write_gf_record(out, gfRecord);
    std::cout << gfName << " #: ";
    write_gf_record(std::cout, gfRecord);
}

void runGFClients()
{
    CGigaFlowClient gfclient("office13.anuview.net", 5555, 1000000, zmqMessageHandler);
    int rc = gfclient.StartListener();
    std::cout << "RC " << rc << std::endl;
    // while() {
    std::this_thread::sleep_for(std::chrono::seconds(10));
    // }

    std::cout << "Ending..." << std::endl;
    gfclient.CloseConnection();
    std::cout << "Ended..." << std::endl;

    rc = gfclient.StartListener();
    std::cout << "RC " << rc << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(10));
    gfclient.CloseConnection();
}

int main()
{
    std::string fName = "GFR_" + current_time() + ".txt";
    out.open(fName);
    if(!out.is_open()) {
        std::cout << "Cannot create " << fName << '\n';
        return -1;
    }

    std::thread t1(runGFClients);
    std::thread t2(runGFClients);
    std::thread t3(runGFClients);
    std::thread t4(runGFClients);
    t1.join();
    t2.join();
    t3.join();
    t4.join();

    // CGigaFlowClient gfclient("tcp://localhost:5555", 1000000);
    CGigaFlowClient gfclient("office13.anuview.net", 5555, 1000000, zmqMessageHandler);
    int rc = gfclient.StartListener();
    std::cout << "RC " << rc << std::endl;
    // while() {
    std::this_thread::sleep_for(std::chrono::seconds(10));
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

std::string current_time() {
    char timebuffer[100];
    std::time_t t = std::time(nullptr);
    std::size_t tlen = std::strftime(timebuffer, sizeof(timebuffer), "%Y.%m.%d-%H-%M-%S", std::localtime(&t));
    if (tlen == 0)
        return "";
    return std::string(timebuffer, tlen);
}

std::vector<uint8_t> get_ip(const flatbuffers::Vector<uint8_t> *ip)
{
    std::vector<uint8_t> return_ip(ip->begin(), ip->end());
    return return_ip;
}

void write_ip(std::ostream &out, const flatbuffers::Vector<uint8_t> *ip)
{
    std::vector<uint8_t> vip = get_ip(ip);
    unsigned long vlen = vip.size();
    if (vlen > 4) {// mac or ipv6
        for(unsigned long i = 0; i < vlen - 1; ++i)
            out << std::hex << (int)vip[i] << '.';
        out << std::hex << (int)vip[vlen - 1];
        out << std::dec;
    } else {
        for(unsigned long i = 0; i < vlen - 1; ++i)
            out << (int)vip[i] << '.';
        out << (int)vip[vlen - 1];
    }
}

void write_gf_record(std::ostream &out, const GigaFlow::Data::GFRecord * gfr)
{
    out << std::to_string(gfr->record_id()); out << ", ";
    write_ip(out, gfr->dev_ip()); out << ", ";
    write_ip(out, gfr->client_addr()); out << ", ";
    write_ip(out, gfr->server_addr()); out << ", ";
    out << gfr->inif(); out << ", ";
    out << gfr->outif(); out << ", ";
    out << gfr->packets1to2(); out << ", ";
    out << gfr->bytes1to2(); out << ", ";
    out << gfr->duration1to2(); out << ", ";
    out << gfr->packets2to1(); out << ", ";
    out << gfr->bytes2to1(); out << ", ";
    out << gfr->duration2to1(); out << ", ";
    out << gfr->port(); out << ", ";
    out << gfr->flags(); out << ", ";
    out << gfr->proto(); out << ", ";
    out << gfr->tos(); out << ", ";
    out << gfr->user()->c_str(); out << ", ";
    out << gfr->domain()->c_str(); out << ", ";
    out << gfr->macsrc(); out << ", ";
    out << gfr->macdst(); out << ", ";
    out << gfr->response1to2(); out << ", ";
    out << gfr->responseCount1to2(); out << ", ";
    out << gfr->flows1to2(); out << ", ";
    out << gfr->response2to1(); out << ", ";
    out << gfr->responseCount2to1(); out << ", ";
    out << gfr->flows2to1(); out << ", ";
    out << gfr->url()->c_str(); out << ", ";
    out << gfr->fwevent()->c_str(); out << ", ";
    out << gfr->fwextcode()->c_str(); out << ", ";
    out << gfr->startTime(); out << ", ";
    out << gfr->trueStartTime(); out << ", ";
    out << gfr->endTime(); out << ", ";
    out << gfr->srcas(); out << ", ";
    out << gfr->dstas(); out << '\n';
}
