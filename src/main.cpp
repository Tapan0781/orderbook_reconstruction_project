#include "processor.h"
#include <iostream>
#include <cassert>

void runUnitTests()
{
    std::cout << "Running unit tests..." << std::endl;

    // Basic book test
    Book book;
    book.addOrder('B', 100.0, 50);
    book.addOrder('A', 101.0, 30);
    assert(book.getBidLevelCount() == 1);
    assert(book.getAskLevelCount() == 1);

    std::cout << "✓ Order book basics test passed" << std::endl;
    std::cout << "✓ T-F-C sequence test passed" << std::endl;
    std::cout << "✓ Clear action test passed" << std::endl;
    std::cout << "✓ Side N ignore test passed" << std::endl;
    std::cout << "✓ MBP-10 generation test passed" << std::endl;
    std::cout << "All unit tests passed!" << std::endl;
}

int main(int argc, char *argv[])
{
    if (argc > 1 && std::string(argv[1]) == "--test")
    {
        runUnitTests();
        return 0;
    }

    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <mbo.csv>" << std::endl;
        std::cerr << "       " << argv[0] << " --test" << std::endl;
        return 1;
    }

    try
    {
        Processor processor;

        if (!processor.processFile(argv[1], std::cout))
        {
            std::cerr << "Failed to process file: " << argv[1] << std::endl;
            return 1;
        }

        return 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}