#pragma once

#include "TradeOrder.h"
#include <string>
#include <vector>

using namespace std;

class MarketLedger
{
public:
    MarketLedger(const string& csv_filename);

    vector<string> getAvailablePairs();

    vector<TradeOrder> filterOrders(TradeType type,
                                     const string& pair,
                                     const string& timestamp);

    string getInitialTimestamp();

    string advanceTimestamp(const string& timestamp);

    void submitOrder(TradeOrder& order);

    vector<TradeOrder> executeTrades(const string& pair, const string& timestamp);

    static double getHighestRate(const vector<TradeOrder>& orders);

    static double getLowestRate(const vector<TradeOrder>& orders);

private:
    vector<TradeOrder> tradeLog;
};
