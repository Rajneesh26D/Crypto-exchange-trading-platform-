#pragma once

#include "TradeOrder.h"
#include <string>
#include <vector>

using namespace std;

namespace DataParser
{
    vector<TradeOrder> parseCSV(const string& filename);

    vector<string> splitString(const string& line, char separator);
}
