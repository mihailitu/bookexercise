#include "GigaFlowClient.h"

#include <fstream>
#include <iostream>
#include <string>
#include <memory>

std::string current_time();
std::vector<uint8_t> get_ip(const flatbuffers::Vector<uint8_t> *ip);
void write_ip(std::ostream &out, const flatbuffers::Vector<uint8_t> *ip);
void write_gf_record(std::ostream &out, const GigaFlow::Data::GFRecord * gfr);

namespace {
    std::ofstream out;
}

static int64_t lastRecord = -1;
static unsigned long records = 0;

void zmqMessageHandler(COrsAppDataManager *, const std::string &, const GigaFlow::Data::GFRecord *gfRecord)
{
    if (gfRecord == nullptr) {
        std::cout << "GFR null!!!" << std::endl;
        return;
    }
    if (lastRecord != -1 && (lastRecord + 1 != gfRecord->record_id()))
            std::cout << "Warn: missing records: " << lastRecord << "->" << gfRecord->record_id() << '\n';

    if ((++records % 1000) == 0) {
        std::cout << ".";
        std::cout.flush();
    }

    lastRecord = gfRecord->record_id();
    write_gf_record(std::cout, gfRecord);
    write_gf_record(out, gfRecord);
}

void runGFClients()
{
    std::string gfAddr = "localhost"/*"192.168.1.191"*/;
    std::string gfPublicKey = "M[jOCOUmvzAqI@n@?7.TGRGegUpgbf=jK:#@TA3$";

//    std::string gfAddr = "office13.anuview.net";
//    std::string gfPublicKey = "-pp7*ct:04-wIeEk!h7(gF}POBmLvDNt9YO]P*qc";

    CGigaFlowClient gfclient(gfAddr, 5555, gfPublicKey, 1000000, nullptr, zmqMessageHandler);
    int rc = gfclient.StartListener();
    std::cout << "RC " << rc << std::endl;
    // while() {
    std::this_thread::sleep_for(std::chrono::seconds(600));
    // }

    std::cout << "Ending..." << std::endl;
    gfclient.CloseConnection();
    std::cout << "Ended..." << std::endl;

    rc = gfclient.StartListener();
    std::cout << "RC " << rc << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(10));
    gfclient.CloseConnection();
}

class MessageHandler {
public:

};

int main()
{
    CGigaFlowClient::message_handler pfn = zmqMessageHandler;
    std::string fName = "GFR_" + current_time() + ".txt";
    out.open(fName);
    if(!out.is_open()) {
        std::cout << "Cannot create " << fName << '\n';
        return -1;
    }

    std::string gfAddr = "localhost"/*"192.168.1.191"*/;
    std::string gfPublicKey = "M[jOCOUmvzAqI@n@?7.TGRGegUpgbf=jK:#@TA3$";

//    std::string gfAddr = "office13.anuview.net";
//    std::string gfPublicKey = "-pp7*ct:04-wIeEk!h7(gF}POBmLvDNt9YO]P*qc";

    CGigaFlowClient gfclient(gfAddr, 5555, gfPublicKey, 1000000, nullptr, pfn);

    int rc = gfclient.StartListener();
    std::cout << "RC " << rc << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(60));

    std::cout << "Ending..." << std::endl;
    gfclient.CloseConnection();
    std::cout << "Ended..." << std::endl;

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
    if (!ip)
        return {};
    std::vector<uint8_t> return_ip(ip->begin(), ip->end());
    return return_ip;
}

void write_ip(std::ostream &out, const flatbuffers::Vector<uint8_t> *ip)
{
    if (!ip || ip->Length() == 0)
        return;
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
    if (gfr->user()) out << gfr->user()->c_str();
    out << ", ";
    if (gfr->domain()) out << gfr->domain()->c_str();
    out << ", ";
    out << gfr->macsrc(); out << ", ";
    out << gfr->macdst(); out << ", ";
    out << gfr->response1to2(); out << ", ";
    out << gfr->responseCount1to2(); out << ", ";
    out << gfr->flows1to2(); out << ", ";
    out << gfr->response2to1(); out << ", ";
    out << gfr->responseCount2to1(); out << ", ";
    out << gfr->flows2to1(); out << ", ";
    if (gfr->url()) out << gfr->url()->c_str();
    out << ", ";
    if (gfr->fwevent()) out << gfr->fwevent()->c_str();
    out << ", ";
    if (gfr->fwextcode()) out << gfr->fwextcode()->c_str();
    out << ", ";
    out << gfr->startTime(); out << ", ";
    out << gfr->trueStartTime(); out << ", ";
    out << gfr->endTime(); out << ", ";
    out << gfr->srcas(); out << ", ";
    out << gfr->dstas(); out << '\n';
    out.flush();
}
