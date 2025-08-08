#include "Portfolio.h"
#include <stdexcept>
#include <sstream>

using namespace std;

Portfolio::Portfolio()
{
}

void Portfolio::credit(const string& currency, double amount)
{
    if (amount < 0)
    {
        throw invalid_argument("Cannot credit a negative amount.");
    }
    holdings[currency] += amount;
}

bool Portfolio::debit(const string& currency, double amount)
{
    if (!hasSufficientFunds(currency, amount))
    {
        return false;
    }
    holdings[currency] -= amount;
    return true;
}

bool Portfolio::hasSufficientFunds(const string& currency, double amount) const
{
    if (holdings.count(currency) == 0)
    {
        return false;
    }
    return holdings.at(currency) >= amount;
}

string Portfolio::getPortfolioSummary() const
{
    stringstream ss;
    ss << "Portfolio Holdings:\n";
    for (const auto& pair : holdings)
    {
        ss << "  " << pair.first << ": " << pair.second << "\n";
    }
    return ss.str();
}

bool Portfolio::canCoverTrade(const TradeOrder& order)
{
    const size_t separator_pos = order.pair.find('/');
    if (separator_pos == string::npos) return false;

    string base = order.pair.substr(0, separator_pos);
    string quote = order.pair.substr(separator_pos + 1);

    if (order.type == TradeType::SELL)
    {
        return hasSufficientFunds(base, order.quantity);
    }
    if (order.type == TradeType::BUY)
    {
        return hasSufficientFunds(quote, order.quantity * order.rate);
    }

    return false;
}

void Portfolio::finalizeTransaction(const TradeOrder& transaction)
{
    const size_t separator_pos = transaction.pair.find('/');
    if (separator_pos == string::npos) return;

    string base = transaction.pair.substr(0, separator_pos);
    string quote = transaction.pair.substr(separator_pos + 1);

    if (transaction.type == TradeType::SELLSALE)
    {
        double outgoingAmount = transaction.quantity;
        double incomingAmount = transaction.quantity * transaction.rate;
        holdings[base] -= outgoingAmount;
        holdings[quote] += incomingAmount;
    }
    if (transaction.type == TradeType::BUYSALE)
    {
        double incomingAmount = transaction.quantity;
        double outgoingAmount = transaction.quantity * transaction.rate;
        holdings[base] += incomingAmount;
        holdings[quote] -= outgoingAmount;
    }
}
