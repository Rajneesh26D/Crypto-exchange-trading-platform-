#pragma once

#include "MarketLedger.h"
#include "Portfolio.h"
#include <string>

using namespace std;

class TradingApp
{
public:
    TradingApp();
    void run();

private:
    void setup();
    void mainLoop();

    void displayMenu();
    int getMenuChoice();
    void handleChoice(int choice);

    void showHelp();
    void displayMarketOverview();
    void placeSellOrder();
    void placeBuyOrder();
    void displayPortfolio();
    void advanceToNextStep();

    MarketLedger market;
    Portfolio portfolio;
    string currentTimestamp;
};
