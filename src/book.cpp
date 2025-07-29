#include "book.h"
#include <sstream>
#include <iomanip>

void Book::addOrder(char side, double price, int64_t size)
{
    if (side == 'B')
    {
        bids[price] += size;
        if (bids[price] <= 0)
        {
            bids.erase(price);
        }
    }
    else if (side == 'A')
    {
        asks[price] += size;
        if (asks[price] <= 0)
        {
            asks.erase(price);
        }
    }
}

void Book::cancelOrder(char side, double price, int64_t size)
{
    addOrder(side, price, -size);
}

void Book::clear()
{
    bids.clear();
    asks.clear();
}

std::string Book::getTop10()
{
    std::ostringstream result;

    // Get top 10 bids and asks
    auto bid_it = bids.begin();
    auto ask_it = asks.begin();

    for (int level = 0; level < 10; level++)
    {
        // Bid level
        if (bid_it != bids.end())
        {
            result << bid_it->first << "," << bid_it->second << ",1,";
            bid_it++;
        }
        else
        {
            result << ",0,0,";
        }

        // Ask level
        if (ask_it != asks.end())
        {
            result << ask_it->first << "," << ask_it->second << ",1";
            ask_it++;
        }
        else
        {
            result << ",0,0";
        }

        if (level < 9)
        {
            result << ",";
        }
    }

    return result.str();
}

int Book::getBidLevels() const
{
    return bids.size();
}

int Book::getAskLevels() const
{
    return asks.size();
}

double Book::getBestBid() const
{
    if (bids.empty())
        return 0.0;
    return bids.begin()->first;
}

double Book::getBestAsk() const
{
    if (asks.empty())
        return 0.0;
    return asks.begin()->first;
}