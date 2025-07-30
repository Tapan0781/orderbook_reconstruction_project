#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <cstdint>

struct Order
{
    std::string ts_recv;
    std::string ts_event;
    int rtype;
    int publisher_id;
    int instrument_id;
    char action;
    char side;
    std::string price_str;
    double price;
    int64_t size;
    int channel_id;
    int64_t order_id;
    int flags;
    int ts_in_delta;
    int sequence;
    std::string symbol;
};

class Parser
{
public:
    Order parseCSVLine(const std::string &line);
    bool isValidLine(const std::string &line);
};

#endif