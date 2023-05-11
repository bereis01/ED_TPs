#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>

#include "stringOperations.hpp"
#include "stringList.hpp"
#include "memlog.hpp"

int main(int argc, char **argv)
{
    // Analysis tools were removed to avoid the generation of the log file.

    // Receives and processes the command line parameters.
    std::string inFileName = "";
    std::string outFileName = "";
    int median = 1;
    int minPartSize = 0;
    gatherArguments(argc, argv, inFileName, outFileName, median, minPartSize);

    // Initializes the input and output files.
    std::ifstream inputFile(inFileName);
    std::ofstream outputFile(outFileName);

    // Verifies if all files were successfully opened.
    if (!inputFile.is_open())
    {
        throw std::runtime_error(std::string("Error: Input file not appropriately opened!"));
    }
    if (!outputFile.is_open())
    {
        throw std::runtime_error(std::string("Error: Output file not appropriately opened!"));
    }

    // Gathers the string stream for the text and order.
    int maxNumOfWords;
    std::stringstream textStream;
    std::stringstream orderStream;
    gatherTextAndOrder(inputFile, textStream, orderStream, maxNumOfWords);
    formatText(textStream);

    // Creates a list with all the words, counting repetitions during the process.
    StringList wordList(maxNumOfWords);
    std::string stringHold;
    while (textStream >> stringHold)
    {
        // Verifies if the stream was correctly read/written.
        if (textStream.bad())
        {
            throw std::runtime_error(std::string("Error: Stream not appropriately read/written!"));
        }

        wordList.insert(stringHold);
    }

    // Orders the list based on the given order.
    wordList.setOrder(orderStream);
    wordList.order(median, minPartSize);

    // Prints the list information to an output file.
    wordList.print(outputFile);

    return 0;
}