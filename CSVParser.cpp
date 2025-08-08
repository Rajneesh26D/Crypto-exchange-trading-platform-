#include "CSVParser.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

vector<string> DataParser::splitString(const string& line, char separator)
{
    vector<string> tokens;
    string token;
    stringstream tokenStream(line);

    while (getline(tokenStream, token, separator))
    {
        tokens.push_back(token);
    }
    return tokens;
}

vector<TradeOrder> DataParser::parseCSV(const string& filename)
{
    vector<TradeOrder> entries;
    ifstream file(filename);
    string line;

    if (!file.is_open())
    {
        cout << "Error: DataParser could not open file " << filename << endl;
        return entries;
    }

    while (getline(file, line))
    {
        vector<string> tokens = splitString(line, ',');
        
        if (tokens.size() != 5)
        {
            continue;
        }

        try
        {
            double rate = stod(tokens[3]);
            double quantity = stod(tokens[4]);
            
            TradeOrder order{
                rate,
                quantity,
                tokens[0],
                tokens[1],
                TradeOrder::stringToTradeType(tokens[2])
            };
            entries.push_back(order);
        }
        catch (const exception& e)
        {
        }
    }

    cout << "DataParser: Loaded " << entries.size() << " entries from " << filename << endl;
    return entries;
}
