#ifndef BOOK_H
#define BOOK_H

#include <map>
#include <string>
#include <cstdint>

class Book
{
private:
    std::map<double, int64_t, std::greater<double>> bids;
    std::map<double, int64_t> asks;

public:
    void addOrder(char side, double price, int64_t size);
    void cancelOrder(char side, double price, int64_t size);
    void clear();
    std::string getTop10();

    // Helper methods
    size_t getBidLevelCount() const;
    size_t getAskLevelCount() const;
    double getBestBid() const;
    double getBestAsk() const;
};

#endif