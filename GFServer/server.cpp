#include <zmq.hpp>
#include <random>

#include "gf_generated.h"
#include "gfrecordstruct.h"
#include <iostream>
#include <thread>
#include <chrono>
#include "logger.h"

flatbuffers::FlatBufferBuilder createRecordBuffer(const GigaFlowRecord &gfrec);
int def(FILE *source, FILE *dest, int level);

int main () {
    zmq::context_t context = zmq::context_t(1);
    std::string public_key = "M[jOCOUmvzAqI@n@?7.TGRGegUpgbf=jK:#@TA3$";
    std::string private_key = "BZh3BWu9+kFObiAfxAk+OCMCZs]UYu9zVSYh.{a6";

    //  We send updates via this socket
    zmq::socket_t publishSocket = zmq::socket_t(context, ZMQ_PUB);

    publishSocket.setsockopt(ZMQ_CURVE_PUBLICKEY, public_key.c_str(), public_key.length());
    publishSocket.setsockopt(ZMQ_CURVE_SECRETKEY, private_key.c_str(), private_key.length());
    int isServer = 1;
    publishSocket.setsockopt(ZMQ_CURVE_SERVER, &isServer, sizeof(isServer));

    int queue = 1000000;
    publishSocket.setsockopt(ZMQ_SNDHWM, &queue, sizeof(queue));

    publishSocket.bind("tcp://*:5555");

    std::this_thread::sleep_for(std::chrono::seconds(1));

    log_info("Client connected");

    log_info("Create %d dummy records...", N);
    std::cout.flush();

    // create N dummy records
    std::vector<GigaFlowRecord> records;
    for(unsigned i = 0; i < N; ++i) {
        data.record_id = i;
        records.push_back(data);
    }
    log_info("Done!");

    std::vector<unsigned char> TenKFlows;

    log_info_l("Start sending data.");
    std::cout.flush();
    unsigned i = 0;
    unsigned long bytes = 0;
    while(true) {
        TenKFlows.clear();
        unsigned short recNo = static_cast<unsigned short>(records.size());

        TenKFlows.insert(TenKFlows.end(), &recNo, &recNo + 2);
        for (const GigaFlowRecord &gfrec : records) {
            // Show progress for each 1000 records
            if ((++i % 1000) == 0) {
                log_info_l(".");
                std::cout.flush();
            }

            auto builder = createRecordBuffer(gfrec);

            unsigned short recordSz = static_cast<unsigned short>(builder.GetSize());
            TenKFlows.insert(TenKFlows.end(), &recordSz, &recordSz + 2);

            auto recBuffer = builder.GetBufferPointer();
            TenKFlows.insert(TenKFlows.end(), recBuffer, recBuffer + recordSz);
            bytes += builder.GetSize();
        }

        zmq::message_t request(TenKFlows.data(), TenKFlows.size());
        while(!publishSocket.send(request)) {
            std::cerr << "data " << i << " not sent!!!\n";
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
        break;
    }
     std::cout << "\nDone sending " << i << " records " << " summimg " << bytes << " bytes\n";

    std::cout << " Done!\n";
    return 0;
}
#include <zlib.h>
#define CHUNK 16384

/* Compress from file source to file dest until EOF on source.
   def() returns Z_OK on success, Z_MEM_ERROR if memory could not be
   allocated for processing, Z_STREAM_ERROR if an invalid compression
   level is supplied, Z_VERSION_ERROR if the version of zlib.h and the
   version of the library linked do not match, or Z_ERRNO if there is
   an error reading or writing the files. */
int def(FILE *source, FILE *dest, int level)
{
    int ret, flush;
    unsigned have;
    z_stream strm;
    unsigned char in[CHUNK];
    unsigned char out[CHUNK];

    /* allocate deflate state */
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    ret = deflateInit(&strm, level);
    if (ret != Z_OK)
        return ret;

    /* compress until end of file */
    do {
        strm.avail_in = fread(in, 1, CHUNK, source);
        if (ferror(source)) {
            (void)deflateEnd(&strm);
            return Z_ERRNO;
        }
        flush = feof(source) ? Z_FINISH : Z_NO_FLUSH;
        strm.next_in = in;

        /* run deflate() on input until output buffer not full, finish
           compression if all of source has been read in */
        do {
            strm.avail_out = CHUNK;
            strm.next_out = out;
            ret = deflate(&strm, flush);    /* no bad return value */
            assert(ret != Z_STREAM_ERROR);  /* state not clobbered */
            have = CHUNK - strm.avail_out;
            if (fwrite(out, 1, have, dest) != have || ferror(dest)) {
                (void)deflateEnd(&strm);
                return Z_ERRNO;
            }
        } while (strm.avail_out == 0);
        assert(strm.avail_in == 0);     /* all input will be used */

        /* done when last data in file processed */
    } while (flush != Z_FINISH);
    assert(ret == Z_STREAM_END);        /* stream will be complete */

    /* clean up and return */
    (void)deflateEnd(&strm);
    return Z_OK;
}

flatbuffers::FlatBufferBuilder createRecordBuffer(const GigaFlowRecord &gfrec)
{
    // Build up a serialized buffer algorithmically:
    flatbuffers::FlatBufferBuilder builder;
    auto dev_ip = builder.CreateVector(gfrec.device_ip);
    auto client_addr = builder.CreateVector(gfrec.client_addr);
    auto server_addr = builder.CreateVector(gfrec.server_addr);
    auto user = builder.CreateString(gfrec.user);
    auto domain = builder.CreateString(gfrec.domain);
    auto macsrc = builder.CreateVector(gfrec.macsrc);
    auto macdst = builder.CreateVector(gfrec.macdst);
    auto url = builder.CreateString(gfrec.url);
    auto fwevent = builder.CreateString(gfrec.fwevent);
    auto fwextcode = builder.CreateString(gfrec.fwextcode);

    auto gfr = GigaFlow::Data::CreateGFRecord(builder,
                                              gfrec.record_id,
                                              dev_ip,
                                              client_addr,
                                              server_addr,
                                              gfrec.inif, gfrec.outif, gfrec.packets1to2, gfrec.bytes1to2, gfrec.duration1to2,
                                              gfrec.packets2to1,
                                              gfrec.bytes2to1,
                                              gfrec.duration2to1,
                                              gfrec.port,
                                              gfrec.flags,
                                              gfrec.proto,
                                              gfrec.tos,
                                              user,
                                              domain,
                                              macsrc,
                                              macdst,
                                              gfrec.response1to2,
                                              gfrec.responseCount1to2,
                                              gfrec.flows1to2,
                                              gfrec.response2to1,
                                              gfrec.responseCount2to1,
                                              gfrec.flows2to1,
                                              url,
                                              fwevent,
                                              fwextcode,
                                              gfrec.startTime,
                                              gfrec.trueStartTime,
                                              gfrec.endTime);
    builder.Finish(gfr);
    return builder;
}
