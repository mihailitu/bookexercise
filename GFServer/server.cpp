#include <zmq.hpp>
#include <random>

#include "gf_generated.h"
#include "gfrecordstruct.h"
#include <iostream>
#include <thread>
#include <chrono>
#include "logger.h"
#include <zlib.h>


flatbuffers::FlatBufferBuilder createRecordBuffer(const GigaFlowRecord &gfrec);
//int def(std::vector<unsigned char> &in, std::vector<unsigned char> &out, int level = 2);
int compress_memory(void *in_data, size_t in_data_size, std::vector<unsigned char> &out_data);
//bool decompress_memory(void *in_data, size_t in_data_size, std::vector<unsigned char> &out_data);
//void test_decode(std::vector<unsigned char> &buffer);
void write_short(std::vector<unsigned char> &buffer, short value);
unsigned short readShort(std::vector<unsigned char> &data, unsigned offset)
{
    return *(reinterpret_cast<unsigned short *>(data.data() + offset));
}
void write_gf_record(std::ostream &out, const GigaFlow::Data::GFRecord * gfr);

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
        records.emplace_back(data);
    }
    log_info("Done!");

    std::vector<unsigned char> TenKFlows;

    log_info("Start sending data.");
    std::cout.flush();
    unsigned i = 0;
    unsigned long bytes = 0;
    unsigned pos = 0;
    unsigned loops = 0;
    while(loops++ < 10) {
        TenKFlows.clear();
        unsigned short recNo = static_cast<unsigned short>(records.size());

        log_info("Sending %d records... ", recNo);
        write_short(TenKFlows, recNo);
        pos += sizeof(recNo);
        bytes += sizeof(recNo);
        //for (const GigaFlowRecord &gfrec : records) {
        for (i = 0; i < N; ++i) {
            const GigaFlowRecord &gfrec = records[i];
            // Show progress for each 1000 records
            if ((i % 1000) == 0) {
                std::cout << ".";
                std::cout.flush();
            }

            auto builder = createRecordBuffer(gfrec);

            unsigned short recordSz = static_cast<unsigned short>(builder.GetSize());
            write_short(TenKFlows, recordSz);

            pos += sizeof(recordSz);
            bytes += sizeof(recordSz);

            unsigned char * recBuffer = builder.GetBufferPointer();
            TenKFlows.insert(TenKFlows.end(), recBuffer, recBuffer + builder.GetSize());

            pos += builder.GetSize();
            bytes += builder.GetSize();
        }

        std::vector<unsigned char> compressedData;
        if (compress_memory(TenKFlows.data(), TenKFlows.size(), compressedData) != Z_OK)
            continue;

        std::cout << "Message sz: " << compressedData.size() << std::endl;

        zmq::message_t request(compressedData.data(), compressedData.size());
        std::cout << "\nMesg len " << request.size() << " bytes\n";

        while(!publishSocket.send(request)) {
            std::cerr << "data " << i << " not sent!!!\n";
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
        // break;
    }
    std::cout << "\nDone sending " << i << " records " << " summimg " << bytes << " bytes\n";

    std::cout << " Done!\n";
    return 0;
}

void write_short(std::vector<unsigned char> &buffer, short value)
{
    value = static_cast<short>((value >> 8) | (value << 8)); // transform 'value' in BigEndian value, as GigaFlow will (BigEndian Java)
    auto p_val = static_cast<unsigned char*>(static_cast<void*>(&value));
    buffer.insert(buffer.end(), p_val, p_val + sizeof(value));
}

void test_decode(std::vector<unsigned char> &buffer)
{
    size_t buffLen = buffer.size();
    std::cout << "Decompressed sz " << buffLen << std::endl;

    if (buffLen < 2) // make sure we have enough bytes
        return;

    unsigned short recNo = readShort(buffer, 0);
    unsigned offset = 2; // normally, we will use sizeof(short). But the data comes from a Java program, so harcode it
    std::cout << "Rec no: " << recNo << std::endl;
    for(unsigned i = 0; i < recNo; ++i) {
        if (offset + 2 > buffLen) // the buffer is malformed
            break;

        unsigned short recLen = readShort(buffer, offset);
        std::cout << "Read rec: " << i << " size: " << recLen << std::endl;
        offset += 2;

        if (offset + recLen > buffLen) {// the buffer is malformed
            std::cout << "Buffer malformed: " << i << std::endl;
            continue;
        }

        const GigaFlow::Data::GFRecord * gfr = GigaFlow::Data::GetGFRecord(buffer.data() + offset);

        write_gf_record(std::cout, gfr);

        offset += recLen;
    }
}

int compress_memory(void *in_data, size_t in_data_size, std::vector<unsigned char> &out_data)
{
    const size_t BUFSIZE = 1024 * 1024;
    uint8_t temp_buffer[BUFSIZE];

    z_stream strm;
    strm.zalloc = nullptr;
    strm.zfree = nullptr;
    strm.next_in = static_cast<unsigned char *>(in_data);
    strm.avail_in = static_cast<unsigned>(in_data_size);

    int ret = deflateInit(&strm, 2);
    if (ret != Z_OK)
        return -1;

    // retrieve the compressed bytes blockwise
    do {
        strm.next_out = reinterpret_cast<Bytef*>(temp_buffer);
        strm.avail_out = BUFSIZE;

        ret = deflate(&strm, Z_FINISH);

        if (out_data.size() < strm.total_out) {
            // append the block to the output string
            out_data.insert(out_data.end(), temp_buffer, temp_buffer + strm.total_out - out_data.size());
        }
    } while (ret == Z_OK);

    deflateEnd(&strm);

    if (ret != Z_STREAM_END)
        return -1;

    std::cout << " Done! " << out_data.size() << std::endl;
    return Z_OK;
}

bool decompress_memory(void *in_data, size_t in_data_size, std::vector<unsigned char> &out_data)
{
    std::cout << "Decompress..." << in_data_size;
    std::cout.flush();

    const size_t BUFSIZE = 1024 * 1024;
    uint8_t temp_buffer[BUFSIZE];

    z_stream strm;
    strm.zalloc = nullptr;
    strm.zfree = nullptr;
    strm.next_in = reinterpret_cast<unsigned char *>(in_data);
    strm.avail_in = static_cast<unsigned int>(in_data_size);
    strm.next_out = temp_buffer;
    strm.avail_out = BUFSIZE;

    int ret = inflateInit(&strm);
    if (ret != Z_OK)
        return false;

    do {
        strm.next_out = static_cast<Bytef*>(temp_buffer);
        strm.avail_out = BUFSIZE;

        ret = inflate(&strm, 0);

        if (out_data.size() < strm.total_out) {
            out_data.insert(out_data.end(), temp_buffer,
                             temp_buffer + strm.total_out - out_data.size());
        }

    } while (ret == Z_OK);

    inflateEnd(&strm);

    if (ret != Z_STREAM_END)
        return false;

    return true;
}

static const unsigned chunk_sz = 16384;
int def(std::vector<unsigned char> &in, std::vector<unsigned char> &out, int level)
{
    int ret;
    unsigned have;
    z_stream strm;
    unsigned char out_buff[chunk_sz];

    /* allocate deflate state */
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    ret = deflateInit(&strm, level);

    if (ret != Z_OK)
        return ret;

    strm.avail_in = static_cast<unsigned>(in.size());
    strm.next_in = in.data();

    /* run deflate() on input until output buffer not full, finish
           compression if all of source has been read in */
    do {
        strm.avail_out = chunk_sz;
        strm.next_out = out_buff;
        ret = deflate(&strm, Z_NO_FLUSH); /* no bad return value */
        assert(ret != Z_STREAM_ERROR);    /* state not clobbered */
        have = chunk_sz - strm.avail_out;
        out.insert(out.end(), out_buff, out_buff + have);
    } while (strm.avail_out == 0);
    assert(strm.avail_in == 0);     /* all input will be used */

    /* clean up and return */
    deflateEnd(&strm);
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
    auto url = builder.CreateString(gfrec.url);
    auto fwevent = builder.CreateString(gfrec.fwevent);
    auto fwextcode = builder.CreateString(gfrec.fwextcode);

//    GigaFlow::Data::GFRecordBuilder gfr(builder);
//    gfr.add_record_id(gfrec.record_id);

    auto gfr = GigaFlow::Data::CreateGFRecord(builder,
                                              gfrec.record_id,
                                              dev_ip,
                                              client_addr,
                                              server_addr,
                                              gfrec.inif,
                                              gfrec.outif,
                                              gfrec.packets1to2,
                                              gfrec.bytes1to2,
                                              gfrec.duration1to2,
                                              gfrec.packets2to1,
                                              gfrec.bytes2to1,
                                              gfrec.duration2to1,
                                              gfrec.port,
                                              gfrec.flags,
                                              gfrec.proto,
                                              gfrec.tos,
                                              user,
                                              domain,
                                              gfrec.macsrc,
                                              gfrec.macdst,
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
                                              gfrec.endTime,
                                              gfrec.srcas,
                                              gfrec.dstas);
//    auto record = gfr.Finish();
    builder.Finish(gfr);
    return builder;
}

std::vector<uint8_t> get_ip(const flatbuffers::Vector<uint8_t> *ip)
{
    std::vector<uint8_t> return_ip(ip->begin(), ip->end());
    return return_ip;
}

void write_ip(std::ostream &out, const flatbuffers::Vector<uint8_t> *ip)
{
    if (ip->size() == 0)
        return;
    std::vector<uint8_t> vip = get_ip(ip);
    unsigned long vlen = vip.size();
    if (vlen == 0)
        return;
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
    out.flush();
}
