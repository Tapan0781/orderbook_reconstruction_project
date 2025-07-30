#include "parser.h"
#include <sstream>

Order Parser::parseCSVLine(const std::string &line)
{
    Order record;
    std::istringstream ss(line);
    std::string field;

    std::getline(ss, record.ts_recv, ',');
    std::getline(ss, record.ts_event, ',');
    std::getline(ss, field, ',');
    record.rtype = field.empty() ? 0 : std::stoi(field);
    std::getline(ss, field, ',');
    record.publisher_id = field.empty() ? 0 : std::stoi(field);
    std::getline(ss, field, ',');
    record.instrument_id = field.empty() ? 0 : std::stoi(field);
    std::getline(ss, field, ',');
    record.action = field.empty() ? 'X' : field[0];
    std::getline(ss, field, ',');
    record.side = field.empty() ? 'X' : field[0];
    std::getline(ss, record.price_str, ',');
    record.price = record.price_str.empty() ? 0.0 : std::stod(record.price_str);
    std::getline(ss, field, ',');
    record.size = field.empty() ? 0 : std::stoll(field);
    std::getline(ss, field, ',');
    record.channel_id = field.empty() ? 0 : std::stoi(field);
    std::getline(ss, field, ',');
    record.order_id = field.empty() ? 0 : std::stoll(field);
    std::getline(ss, field, ',');
    record.flags = field.empty() ? 0 : std::stoi(field);
    std::getline(ss, field, ',');
    record.ts_in_delta = field.empty() ? 0 : std::stoi(field);
    std::getline(ss, field, ',');
    record.sequence = field.empty() ? 0 : std::stoi(field);
    std::getline(ss, record.symbol);

    return record;
}

bool Parser::isValidLine(const std::string &line)
{
    if (line.empty())
        return false;

    int commaCount = 0;
    for (char c : line)
    {
        if (c == ',')
            commaCount++;
    }

    return commaCount == 14;
}