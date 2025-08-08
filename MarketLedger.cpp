#include "MarketLedger.h"
#include "CSVParser.h" 
#include <algorithm>
#include <set>
#include <iostream>

using namespace std;

MarketLedger::MarketLedger(const string& csv_filename)
{
    tradeLog = DataParser::parseCSV(csv_filename);
}

vector<string> MarketLedger::getAvailablePairs()
{
    set<string> pairSet;
    for (const TradeOrder& order : tradeLog)
    {
        pairSet.insert(order.pair);
    }

    vector<string> pairs(pairSet.begin(), pairSet.end());
    return pairs;
}

vector<TradeOrder> MarketLedger::filterOrders(TradeType type,
                                               const string& pair,
                                               const string& timestamp)
{
    vector<TradeOrder> filtered;
    for (const TradeOrder& order : tradeLog)
    {
        if (order.type == type && order.pair == pair && order.timestamp == timestamp)
        {
            filtered.push_back(order);
        }
    }
    return filtered;
}

string MarketLedger::getInitialTimestamp()
{
    if (tradeLog.empty()) return "";
    return tradeLog[0].timestamp;
}

string MarketLedger::advanceTimestamp(const string& timestamp)
{
    for (const TradeOrder& order : tradeLog)
    {
        if (order.timestamp > timestamp)
        {
            return order.timestamp;
        }
    }
    return getInitialTimestamp();
}

void MarketLedger::submitOrder(TradeOrder& order)
{
    tradeLog.push_back(order);
    sort(tradeLog.begin(), tradeLog.end(), TradeOrderComparators::compareByTimestamp);
}

double MarketLedger::getHighestRate(const vector<TradeOrder>& orders)
{
    if (orders.empty()) return 0.0;
    double max = orders[0].rate;
    for (const TradeOrder& o : orders)
    {
        if (o.rate > max) max = o.rate;
    }
    return max;
}

double MarketLedger::getLowestRate(const vector<TradeOrder>& orders)
{
    if (orders.empty()) return 0.0;
    double min = orders[0].rate;
    for (const TradeOrder& o : orders)
    {
        if (o.rate < min) min = o.rate;
    }
    return min;
}

vector<TradeOrder> MarketLedger::executeTrades(const string& pair, const string& timestamp)
{
    vector<TradeOrder> asks = filterOrders(TradeType::SELL, pair, timestamp);
    vector<TradeOrder> bids = filterOrders(TradeType::BUY, pair, timestamp);
    vector<TradeOrder> completedSales;

    sort(asks.begin(), asks.end(), TradeOrderComparators::compareByRateAsc);
    sort(bids.begin(), bids.end(), TradeOrderComparators::compareByRateDesc);

    for (TradeOrder& bid : bids)
    {
        for (TradeOrder& ask : asks)
        {
            if (bid.quantity == 0 || ask.quantity == 0) continue;

            if (bid.rate >= ask.rate)
            {
                double tradeQuantity = min(bid.quantity, ask.quantity);
                
                TradeType saleType = TradeType::UNKNOWN;
                if (bid.user == "simuser") saleType = TradeType::BUYSALE;
                if (ask.user == "simuser") saleType = TradeType::SELLSALE;

                TradeOrder sale{ask.rate, tradeQuantity, timestamp, pair, saleType, "simuser"};
                completedSales.push_back(sale);

                bid.quantity -= tradeQuantity;
                ask.quantity -= tradeQuantity;
            }
        }
    }
    return completedSales;
}
