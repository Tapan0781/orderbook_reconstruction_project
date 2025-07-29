#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "book.h"
#include "parser.h"
#include <vector>
#include <string>
#include <fstream>

class Processor
{
private:
    Book book;
    Parser parser;
    std::vector<Order> allRecords;
    int currentIndex;
    int outputSequence;

public:
    
    bool processFile(const std::string &filename, std::ostream &output);

    // Load all records from the file
    void loadAllRecords(const std::string &filename);
    bool processNextRecord();

    // Output methods
    void outputHeader(std::ostream &output);
    void outputMBPRecord(std::ostream &output, const Order &order, char finalAction, char finalSide);

    // T-F-C sequence handling
    bool isTFCSequence(int index);
    void processTFCSequence(int index);


    bool shouldSkipRecord(const Order &order);
    void applyOrderToBook(const Order &order);

    // Utility methods
    void reset();
    int getCurrentIndex() const;
    bool hasMoreRecords() const;
};

#endif
