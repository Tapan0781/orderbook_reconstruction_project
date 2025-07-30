#include "processor.h"
#include <fstream>
#include <iomanip>
#include <stdexcept>
#include <iostream>

Processor::Processor() : currentIndex(0), outputSequence(0)
{
    
}

bool Processor::processFile(const std::string &filename, std::ostream &output)
{
    try
    {
        loadRecords(filename);
        return processAllRecords(output);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error processing file: " << e.what() << std::endl;
        return false;
    }
}

void Processor::loadRecords(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("Cannot open file: " + filename);
    }

    std::string line;
    std::getline(file, line); 

    records.clear();
    while (std::getline(file, line))
    {
        if (!line.empty() && parser.isValidLine(line))
        {
            Order order = parser.parseCSVLine(line);
            records.push_back(order);
        }
    }
    file.close();
}

bool Processor::processAllRecords(std::ostream &output)
{
    outputHeader(output);
    reset();

    while (currentIndex < static_cast<int>(records.size()))
    {
        Order &record = records[currentIndex];

        
        if (record.action == 'R')
        {
            book.clear();
            outputRecord(output, record);
            currentIndex++;
            continue;
        }

        
        if (record.action == 'T' && isPartOfTFCSequence(currentIndex))
        {
            Order &tradeRecord = records[currentIndex];
            Order &cancelRecord = records[currentIndex + 2];

            
            if (cancelRecord.side != 'N')
            {
                book.cancelOrder(cancelRecord.side, cancelRecord.price, cancelRecord.size);
            }

            
            outputTRecord(output, tradeRecord, cancelRecord);
            currentIndex += 3; 
            continue;
        }

        
        if (record.action == 'T')
        {
            outputRecord(output, record);
            currentIndex++;
            continue;
        }

        
        if (record.action == 'A')
        {
            book.addOrder(record.side, record.price, record.size);
            outputRecord(output, record);
        }
        else if (record.action == 'C')
        {
            if (!isPartOfPreviousTFC(currentIndex))
            {
                book.cancelOrder(record.side, record.price, record.size);
                outputRecord(output, record);
            }
        }

        currentIndex++;
    }

    return true;
}

void Processor::outputHeader(std::ostream &output)
{
    output << ",ts_recv,ts_event,rtype,publisher_id,instrument_id,action,side,depth,price,size,flags,ts_in_delta,sequence,";
    for (int i = 0; i < 10; i++)
    {
        output << "bid_px_" << std::setfill('0') << std::setw(2) << i << ","
               << "bid_sz_" << std::setfill('0') << std::setw(2) << i << ","
               << "bid_ct_" << std::setfill('0') << std::setw(2) << i << ",";
        output << "ask_px_" << std::setfill('0') << std::setw(2) << i << ","
               << "ask_sz_" << std::setfill('0') << std::setw(2) << i << ","
               << "ask_ct_" << std::setfill('0') << std::setw(2) << i;
        if (i < 9)
            output << ",";
    }
    output << ",symbol,order_id" << std::endl;
}

void Processor::outputRecord(std::ostream &output, const Order &record)
{
    output << outputSequence++ << ","
           << record.ts_event << ","
           << record.ts_event << ","
           << "10,"
           << record.publisher_id << ","
           << record.instrument_id << ","
           << record.action << ","
           << record.side << ","
           << "0,"
           << record.price_str << ","
           << record.size << ","
           << record.flags << ","
           << record.ts_in_delta << ","
           << record.sequence << ","
           << book.getTop10() << ","
           << record.symbol << ","
           << record.order_id
           << std::endl;
}

void Processor::outputTRecord(std::ostream &output, const Order &timeRecord, const Order &cancelRecord)
{
    output << outputSequence++ << ","
           << timeRecord.ts_event << ","
           << timeRecord.ts_event << ","
           << "10,"
           << timeRecord.publisher_id << ","
           << timeRecord.instrument_id << ","
           << "T,"
           << cancelRecord.side << ","
           << "0,"
           << cancelRecord.price_str << ","
           << cancelRecord.size << ","
           << timeRecord.flags << ","
           << timeRecord.ts_in_delta << ","
           << timeRecord.sequence << ","
           << book.getTop10() << ","
           << timeRecord.symbol << ","
           << cancelRecord.order_id
           << std::endl;
}

bool Processor::isPartOfTFCSequence(int index)
{
    if (index + 2 >= static_cast<int>(records.size()))
        return false;
    return records[index].action == 'T' &&
        records[index + 1].action == 'F' &&
        records[index + 2].action == 'C';
}

bool Processor::isPartOfPreviousTFC(int index)
{
    return (index >= 2 &&
            records[index - 2].action == 'T' &&
            records[index - 1].action == 'F' &&
            records[index].action == 'C');
}

void Processor::reset()
{
    currentIndex = 0;
    outputSequence = 0;
    book.clear();
}