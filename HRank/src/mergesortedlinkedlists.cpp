#include "gtest/gtest.h"

#include <forward_list>
/**
 * @brief TEST MergeSortedLinkedList
 * Given two sorted linked lists, merge the two lists in a sorted results.
 * Consider implementing with and without memory restraint
 */

template <typename T>
void MergeSortedLinkedLists()
{
    std::forward_list<T> ll;

}

TEST(HRank, MergeSortedLinkedList)
{

}


enum GanularilyType {
    OneMin = 1,
    TenMin = 10,
    OneHour = 60,
    SixHours = 360,
    OneDay = 1440
};

struct AggregateFileInfo {
    std::string fileSuffix;
    std::string parentSuffix;
    GanularilyType granularity;
    TrendFileTypeEnum fileType; // used to open the stream
    std::vector<std::pair<StreamTypeEnum, std::vector<StreamTypeEnum>>> streamDependency;
};

AggregateFileInfo rawFile = { "", "", OneMin, TrendFileType_Regular,{} };

AggregateFileInfo _pas = {
    "_pas",
    "",
    OneMin,
    TrendFileType_Aggregate,
    { { STREAM_APA_TREND_EX,            { STREAM_APA_SERVER_TREND_EX, STREAM_APA_SUMMARY_TREND_EX } },
      { STREAM_ATA_DETAILS_TREND_EX,    { STREAM_ATA_DETAILS_SERVER_TREND_EX, STREAM_ATA_DETAILS_SUMMARY_TREND_EX } },
      { STREAM_ATA_FIX_TREND_EX,        { STREAM_ATA_FIX_TREND_EX, STREAM_ATA_FIX_SUMMARY_TREND_EX } },
      { STREAM_ATA_SQL_TREND_EX,        { STREAM_ATA_SQL_SERVER_TREND_EX, STREAM_ATA_SQL_SUMMARY_TREND_EX } },
    }
};

AggregateFileInfo _10m = {
    "_10m",
    "",
    TenMin,
    TrendFileType_Aggregate,
    { { STREAM_APA_TREND_EX,{ STREAM_APA_SERVER_TREND_EX, STREAM_APA_SUMMARY_TREND_EX } },
      { STREAM_ATA_DETAILS_TREND_EX,{ STREAM_ATA_DETAILS_SERVER_TREND_EX, STREAM_ATA_DETAILS_SUMMARY_TREND_EX } },
      { STREAM_ATA_FIX_TREND_EX,{ STREAM_ATA_FIX_TREND_EX, STREAM_ATA_FIX_SUMMARY_TREND_EX } },
      { STREAM_ATA_SQL_TREND_EX,{ STREAM_ATA_SQL_SERVER_TREND_EX, STREAM_ATA_SQL_SUMMARY_TREND_EX } },
    }
};

std::vector<StreamTypeEnum> rawFileStreams = {
    STREAM_APA_TREND_EX,
    STREAM_ATA_DETAILS_TREND_EX,
    STREAM_ATA_FIX_TREND_EX,
    STREAM_ATA_SQL_TREND_EX,
    STREAM_ATA_URL_TREND_EX,
    STREAM_NETWORK_TOTALS_TREND_EX,
    STREAM_PAIR_EX
};

std::vector<AggregateFileInfo> rollupsInfo = {
    { _pas },
    { _10m },
};

