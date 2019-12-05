#ifndef GFRECORDSTRUCT_H
#define GFRECORDSTRUCT_H

#include "gf_generated.h"
#include <string>

enum PROTO {
    TCP = 0,
    ICMP = 1,
};

const unsigned N = 10000;

struct GigaFlowRecord {
    int64_t record_id;
    std::vector<uint8_t> device_ip;
    std::vector<uint8_t> client_addr;
    std::vector<uint8_t> server_addr;
    int32_t inif;
    int32_t outif;
    int64_t packets1to2;
    int64_t bytes1to2;
    int64_t duration1to2;
    int64_t packets2to1;
    int64_t bytes2to1;
    int64_t duration2to1;
    int32_t port;
    int32_t flags;
    int32_t proto;
    int32_t tos;
    std::string user;
    std::string domain;
    uint64_t macsrc;
    uint64_t macdst;
    int32_t response1to2;
    int32_t responseCount1to2;
    int32_t flows1to2;
    int32_t response2to1;
    int32_t responseCount2to1;
    int32_t flows2to1;
    std::string url;
    std::string fwevent;
    std::string fwextcode;
    uint64_t startTime;
    uint64_t trueStartTime;
    uint64_t endTime;
    int32_t srcas;
    int32_t dstas;

};

static GigaFlowRecord data =
{0,                                     // int64_t record_id;
 {0, 0, 0, 238},                         // std::vector<uint8_t> device_ip;
 {10, 2, 210, 100},                      // std::vector<uint8_t> client_addr;
 {10, 2, 152, 50},                       // std::vector<uint8_t> server_addr;
 1,                                      // int32_t inif;
 53,                                     // int32_t outif;
 143,                                    // int64_t packets1to2;
 9464,                                   // int64_t bytes1to2;
 5,                                      // int64_t duration1to2;
 60,                                     // int64_t packets2to1;
 1316,                                   // int64_t bytes2to1;
 3,                                      // int64_t duration2to1;
 139,                                    // int32_t port;
 16,                                     // int32_t flags;
 PROTO::TCP,                             // int32_t proto;
 14,                                     // int32_t tos;
 "",                                     // std::string user;
 "",                                     // std::string domain;
 1234,                                   // uint64_t macsrc;
 4321,                                   // uint64_t macdst;
 0,                                      // int32_t response1to2;
 0,                                      // int32_t responseCount1to2;
 14,                                     // int32_t flows1to2;
 0,                                      // int32_t response2to1;
 0,                                      // int32_t responseCount2to1;
 20,                                     // int32_t flows2to1;
 "www.viavisolutions.com",               // std::string url;
 "",                                     // std::string fwevent;
 "",                                     // std::string fwextcode;
 1569590160000,                          // uint64_t startTime;
 1569590216302,                          // uint64_t trueStartTime;
 1569590284910,                          // uint64_t endTime;
 123,                                    // int32_t srcas;
 321                                     // int32_t dstas;
};

#endif // GFRECORDSTRUCT_H
