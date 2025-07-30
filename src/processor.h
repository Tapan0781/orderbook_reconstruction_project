#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "parser.h" // This must come first to get Order struct
#include "book.h"
#include <vector>
#include <string>
#include <iostream>

class Processor
{
private:
    Book book;
    Parser parser;
    std::vector<Order> records; // Order should be defined from parser.h
    int currentIndex;
    int outputSequence;

    // Private helper methods
    void loadRecords(const std::string &filename);
    bool processAllRecords(std::ostream &output);
    void outputHeader(std::ostream &output);
    void outputRecord(std::ostream &output, const Order &record);
    void outputTRecord(std::ostream &output, const Order &timeRecord, const Order &cancelRecord);
    bool isPartOfTFCSequence(int index);
    bool isPartOfPreviousTFC(int index);
    void reset();

public:
    Processor();
    bool processFile(const std::string &filename, std::ostream &output);
};

#endif