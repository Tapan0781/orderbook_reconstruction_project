#include "parser.h"
#include <sstream>
#include <iostream>

Order Parser::parseCSVLine(const std::string &line)
{
    Order order;
    std::istringstream ss(line);  // Use string stream to parse the line
    std::string field;

    // Parse each field in order
    std::getline(ss, order.ts_recv, ',');
    std::getline(ss, order.ts_event, ',');

    std::getline(ss, field, ',');
    order.rtype = parseInt(field);

    std::getline(ss, field, ',');
    order.publisher_id = parseInt(field);

    std::getline(ss, field, ',');
    order.instrument_id = parseInt(field);

    std::getline(ss, field, ',');
    order.action = parseChar(field);

    std::getline(ss, field, ',');
    order.side = parseChar(field);

    std::getline(ss, field, ',');
    order.price = parseDouble(field);

    std::getline(ss, field, ',');
    order.size = parseInt64(field);

    std::getline(ss, field, ',');
    order.channel_id = parseInt(field);

    std::getline(ss, field, ',');
    order.order_id = parseInt64(field);

    std::getline(ss, field, ',');
    order.flags = parseInt(field);

    std::getline(ss, field, ',');
    order.ts_in_delta = parseInt(field);

    std::getline(ss, field, ',');
    order.sequence = parseInt(field);

    std::getline(ss, order.symbol); // Last field - no comma

    return order;
}

bool Parser::isValidLine(const std::string &line)
{
    if (line.empty())
        return false;

    // Counting commas - should have 14 commas for 15 fields
    int commaCount = 0;
    for (char c : line)
    {
        if (c == ',')
            commaCount++;
    }

    return commaCount == 14;
}

double Parser::parseDouble(const std::string &str)
{
    if (str.empty())
        return 0.0;

    try
    {
        return std::stod(str);
    }
    catch (const std::exception &e)
    {
        return 0.0; // if failed to parse, return safe default
    }
}

int64_t Parser::parseInt64(const std::string &str)
{
    if (str.empty())
        return 0;

    try
    {
        return std::stoll(str);
    }
    catch (const std::exception &e)
    {
        return 0; // if failed to parse, return safe default
    }
}

int Parser::parseInt(const std::string &str)
{
    if (str.empty())
        return 0;

    try
    {
        return std::stoi(str);
    }
    catch (const std::exception &e)
    {
        return 0; // Return safe default on error
    }
}

char Parser::parseChar(const std::string &str)
{
    if (str.empty())
        return 'X'; // Safe default
    return str[0];  // Return first character
}
