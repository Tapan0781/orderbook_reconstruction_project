

#ifndef BOOK_H
#define BOOK_H

#include <map>
#include <string>
#include <cstdint>

class Book
{
private:
    
    std::map<double, int64_t, std::greater<double>> bids; // automatic sorting (descending)for bids

    // automatic sorting (ascending) for asks
    std::map<double, int64_t> asks;

public:
    void addOrder(char side, double price, int64_t size);
    void cancelOrder(char side, double price, int64_t size);
    void clear();

    // getting output as top 10 bids and asks
    std::string getTop10();

    //  methods for testing & debugging
    int getBidLevels() const;
    int getAskLevels() const;
    double getBestBid() const;
    double getBestAsk() const;
};

#endif
