#pragma once
#include <string>
#include <vector>

using namespace std;

enum class TradeType
{
    BUY,
    SELL,
    BUYSALE,
    SELLSALE,
    UNKNOWN
};

class TradeOrder
{
public:
    double rate;
    double quantity;
    string timestamp;
    string pair;
    TradeType type;
    string user;

    TradeOrder(double _rate,
               double _quantity,
               string _timestamp,
               string _pair,
               TradeType _type,
               string _user = "sim_user");

    static TradeType stringToTradeType(const string& s);
};

struct TradeOrderComparators
{
    static bool compareByTimestamp(const TradeOrder& a, const TradeOrder& b)
    {
        return a.timestamp < b.timestamp;
    }

    static bool compareByRateAsc(const TradeOrder& a, const TradeOrder& b)
    {
        return a.rate < b.rate;
    }

    static bool compareByRateDesc(const TradeOrder& a, const TradeOrder& b)
    {
        return a.rate > b.rate;
    }
};
