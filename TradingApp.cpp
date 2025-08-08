#include "TradingApp.h"
#include "CSVParser.h" 
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

TradingApp::TradingApp()
    : market("data.csv")
{
}

void TradingApp::run()
{
    setup();
    mainLoop();
}

void TradingApp::setup()
{
    currentTimestamp = market.getInitialTimestamp();
    portfolio.credit("USDT", 20000.0);
    portfolio.credit("BTC", 2.0);
}

void TradingApp::mainLoop()
{
    while (true)
    {
        displayMenu();
        int choice = getMenuChoice();
        handleChoice(choice);
    }
}

void TradingApp::displayMenu()
{
    cout << "\n1: Display Help\n";
    cout << "2: Display Market Overview\n";
    cout << "3: Place a Sell Order (Ask)\n";
    cout << "4: Place a Buy Order (Bid)\n";
    cout << "5: Display Portfolio\n";
    cout << "6: Advance to Next Time Step\n";
    cout << "============================\n";
    cout << "Current Time: " << currentTimestamp << "\n";
}

int TradingApp::getMenuChoice()
{
    cout << "Enter your choice (1-6): ";
    string line;
    getline(cin, line);
    try
    {
        return stoi(line);
    }
    catch (const exception& e)
    {
        return 0;
    }
}

void TradingApp::handleChoice(int choice)
{
    switch (choice)
    {
        case 1: showHelp(); break;
        case 2: displayMarketOverview(); break;
        case 3: placeSellOrder(); break;
        case 4: placeBuyOrder(); break;
        case 5: displayPortfolio(); break;
        case 6: advanceToNextStep(); break;
        default: cout << "Invalid choice. Please try again.\n"; break;
    }
}

void TradingApp::showHelp()
{
    cout << "This is a trading simulation. Your goal is to make profitable trades by analyzing the market.\n";
}

void TradingApp::displayMarketOverview()
{
    cout << "--- Market Overview for " << currentTimestamp << " ---\n";
    for (const string& pair : market.getAvailablePairs())
    {
        cout << "Pair: " << pair << endl;
        vector<TradeOrder> asks = market.filterOrders(TradeType::SELL, pair, currentTimestamp);
        cout << "  Asks: " << asks.size();
        cout << " | Lowest Ask: " << MarketLedger::getLowestRate(asks);
        cout << " | Highest Ask: " << MarketLedger::getHighestRate(asks) << endl;
    }
}

void TradingApp::placeSellOrder()
{
    cout << "Place Sell Order (Format: pair,rate,quantity e.g. BTC/USDT,6000,0.5): ";
    string line;
    getline(cin, line);

    vector<string> tokens = DataParser::splitString(line, ',');
    if (tokens.size() != 3) {
        cout << "Invalid format. Please try again.\n";
        return;
    }
    try {
        TradeOrder order{ stod(tokens[1]), stod(tokens[2]), currentTimestamp, tokens[0], TradeType::SELL, "simuser" };
        if (portfolio.canCoverTrade(order)) {
            market.submitOrder(order);
            cout << "Sell order placed successfully.\n";
        } else {
            cout << "Insufficient funds to place this sell order.\n";
        }
    } catch (const exception& e) {
        cout << "Invalid input. Please ensure rate and quantity are numbers.\n";
    }
}

void TradingApp::placeBuyOrder()
{
    cout << "Place Buy Order (Format: pair,rate,quantity e.g. BTC/USDT,5000,0.5): ";
    string line;
    getline(cin, line);

    vector<string> tokens = DataParser::splitString(line, ',');
    if (tokens.size() != 3) {
        cout << "Invalid format. Please try again.\n";
        return;
    }
    try {
        TradeOrder order{ stod(tokens[1]), stod(tokens[2]), currentTimestamp, tokens[0], TradeType::BUY, "simuser" };
        if (portfolio.canCoverTrade(order)) {
            market.submitOrder(order);
            cout << "Buy order placed successfully.\n";
        } else {
            cout << "Insufficient funds to place this buy order.\n";
        }
    } catch (const exception& e) {
        cout << "Invalid input. Please ensure rate and quantity are numbers.\n";
    }
}

void TradingApp::displayPortfolio()
{
    cout << portfolio.getPortfolioSummary();
}

void TradingApp::advanceToNextStep()
{
    cout << "--- Advancing Time Step & Processing Trades ---\n";
    for (const string& pair : market.getAvailablePairs())
    {
        vector<TradeOrder> sales = market.executeTrades(pair, currentTimestamp);
        for (TradeOrder& sale : sales)
        {
            portfolio.finalizeTransaction(sale);
        }
    }
    currentTimestamp = market.advanceTimestamp(currentTimestamp);
}
