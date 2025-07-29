#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <cstdint>
#include <vector>
struct Order
{
    std::string ts_recv;
    std::string ts_event;
    int rtype;
    int publisher_id;
    int instrument_id;
    char action;
    char side;
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
    // breating the csv data into an Order object
    Order parseCSVLine(const std::string &line); // '&' is used to avoid copying the string 

    // method to validate the CSV line format
    bool isValidLine(const std::string &line);

private:
    // Helper method to split string by delimiter
    std::vector<std::string> split(const std::string &str, char delimiter);

    //methods to convert strings safely
    double parseDouble(const std::string &str);
    int64_t parseInt64(const std::string &str);
    int parseInt(const std::string &str);
    char parseChar(const std::string &str);
};

#endif
