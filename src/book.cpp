#include "book.h"
#include <sstream>
#include <vector>

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
    std::ostringstream ss;

    std::vector<std::pair<double, int64_t>> top_bids;
    std::vector<std::pair<double, int64_t>> top_asks;

    auto bid_it = bids.begin();
    for (int i = 0; i < 10 && bid_it != bids.end(); ++i, ++bid_it)
    {
        top_bids.push_back(*bid_it);
    }

    auto ask_it = asks.begin();
    for (int i = 0; i < 10 && ask_it != asks.end(); ++i, ++ask_it)
    {
        top_asks.push_back(*ask_it);
    }

    for (int i = 0; i < 10; ++i)
    {
        if (i < top_bids.size())
        {
            ss << top_bids[i].first << "," << top_bids[i].second << ",1,";
        }
        else
        {
            ss << ",0,0,";
        }

        if (i < top_asks.size())
        {
            ss << top_asks[i].first << "," << top_asks[i].second << ",1";
        }
        else
        {
            ss << ",0,0";
        }

        if (i < 9)
            ss << ",";
    }

    return ss.str();
}

size_t Book::getBidLevelCount() const
{
    return bids.size();
}

size_t Book::getAskLevelCount() const
{
    return asks.size();
}

double Book::getBestBid() const
{
    return bids.empty() ? 0.0 : bids.begin()->first;
}

double Book::getBestAsk() const
{
    return asks.empty() ? 0.0 : asks.begin()->first;
}