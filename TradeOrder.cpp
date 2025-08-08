#include "TradeOrder.h"

using namespace std;

TradeOrder::TradeOrder(double _rate,
                       double _quantity,
                       string _timestamp,
                       string _pair,
                       TradeType _type,
                       string _user)
    : rate(_rate),
      quantity(_quantity),
      timestamp(_timestamp),
      pair(_pair),
      type(_type),
      user(_user)
{
}

TradeType TradeOrder::stringToTradeType(const string& s)
{
    if (s == "ask" || s == "sell")
    {
        return TradeType::SELL;
    }
    if (s == "bid" || s == "buy")
    {
        return TradeType::BUY;
    }
    return TradeType::UNKNOWN;
}
