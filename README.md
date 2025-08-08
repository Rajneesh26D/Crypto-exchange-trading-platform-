# Crypto Trading Platform

A robust, object-oriented C++ application for trading cryptocurrencies like Bitcoin (BTC) and Ethereum (ETH). This platform leverages advanced C++ features—including static functions and function overloading—to deliver efficient trading, a dynamic order book, and an intelligent matching algorithm.

## Features

- **Market Stats:** View up-to-date (demo/static) market statistics.
- **Order Placement:** Place bids (buy orders) or asks (sell orders) for supported cryptocurrencies. Orders are sorted and matched automatically.
- **Wallet Management:** Check your virtual wallet balance, including holdings and available funds.
- **Order Book & Matching:** All buy/sell orders are efficiently organized and matched at each trading interval.
- **Time Frame Resolution:** Pending orders are resolved at the end of each time frame.
- **CSV Import:** Load historical orders from a CSV file to simulate and analyze past trades.

## Getting Started

1. **Clone the repository:**
    ```bash
    git clone https://github.com/gautamV19/Crypto-Trading-Plateform.git
    ```
2. **Compile the code:**
    ```bash
    g++ main.cpp -o trading_platform
    ```
3. **Run the application:**
    ```bash
    ./trading_platform
    ```

## Menu Overview

Upon running, you'll see:

```
1: Print help
2: Print exchange stats
3: Make an offer/ask
4: Make a bid
5: Print wallet
6: Continue
===========
Current time is: <timestamp>
Type in 1-6
```

Choose an option to explore platform features.

---
