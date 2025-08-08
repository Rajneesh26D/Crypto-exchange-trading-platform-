#pragma once
#include <string>
#include <map>
#include "TradeOrder.h"

using namespace std;

class Portfolio
{
public:
    Portfolio();

    void credit(const string& currency, double amount);

    bool debit(const string& currency, double amount);

    bool hasSufficientFunds(const string& currency, double amount) const;

    bool canCoverTrade(const TradeOrder& order);

    void finalizeTransaction(const TradeOrder& transaction);

    string getPortfolioSummary() const;

private:
    map<string, double> holdings;
};
