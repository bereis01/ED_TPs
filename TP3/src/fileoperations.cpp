#include "fileoperations.hpp"

void initializeFiles(int argc, char **argv, std::ifstream &inputFile, std::ofstream &outputFile)
{
    // Limits the number of command line arguments (since only two are valid).
    if (argc > 15)
    {
        throw std::logic_error(std::string("Error: Too many command line arguments!"));
    }

    // Searches for the input and output files identifiers.
    // Initializes them, if provided.
    int inputFlag = 0;
    int outputFlag = 0;

    std::string argumentHold;
    for (int i = 1; i < argc; i++)
    {
        argumentHold = argv[i];

        if (argumentHold == "-i")
        {
            if (i + 1 < argc && std::string(argv[i + 1]) != "-o")
            {
                inputFile.open(argv[++i]);
                inputFlag = 1;
            }
        }
        else if (argumentHold == "-o")
        {
            if (i + 1 < argc && std::string(argv[i + 1]) != "-i")
            {
                outputFile.open(argv[++i]);
                outputFlag = 1;
            }
        }
    }

    // Guarantees that an input file and an output file have been provided.
    if (!(inputFlag))
    {
        throw std::logic_error(std::string("Error: No input file provided!"));
    }
    if (!(outputFlag))
    {
        throw std::logic_error(std::string("Error: No output file provided!"));
    }
}

void insertMail(MailServer &server, std::ifstream &inputFile, std::ofstream &outputFile)
{
    // Initializes the message's information.
    int userID, mailID, wordCount;
    inputFile >> userID >> mailID >> wordCount;

    // Verifies if the input file was correctly read.
    if (inputFile.bad())
    {
        throw std::runtime_error(std::string("Error: Input file not appropriately read!"));
    }

    // Inputs the message from the file.
    std::string message, messageHold;
    inputFile >> message;

    // Verifies if the input file was correctly read.
    if (inputFile.bad())
    {
        throw std::runtime_error(std::string("Error: Input file not appropriately read!"));
    }

    while (wordCount > 1)
    {
        inputFile >> messageHold;

        // Verifies if the input file was correctly read.
        if (inputFile.bad())
        {
            throw std::runtime_error(std::string("Error: Input file not appropriately read!"));
        }

        message += " " + messageHold;

        wordCount--;
    }

    // Inserts the message into the server.
    outputFile << server.insert(userID, mailID, message) << std::endl;

    // Verifies if the output file was correctly written.
    if (outputFile.bad())
    {
        throw std::runtime_error(std::string("Error: Output file not appropriately written!"));
    }
}

void removeMail(MailServer &server, std::ifstream &inputFile, std::ofstream &outputFile)
{
    // Inputs the message's information.
    int userID, mailID;
    inputFile >> userID >> mailID;

    // Verifies if the input file was correctly read.
    if (inputFile.bad())
    {
        throw std::runtime_error(std::string("Error: Input file not appropriately read!"));
    }

    // Removes the message from the server.
    outputFile << server.remove(userID, mailID) << std::endl;

    // Verifies if the output file was correctly written.
    if (outputFile.bad())
    {
        throw std::runtime_error(std::string("Error: Output file not appropriately written!"));
    }
}

void searchMail(MailServer &server, std::ifstream &inputFile, std::ofstream &outputFile)
{
    // Inputs the message's information.
    int userID, mailID;
    inputFile >> userID >> mailID;

    // Verifies if the input file was correctly read.
    if (inputFile.bad())
    {
        throw std::runtime_error(std::string("Error: Input file not appropriately read!"));
    }

    // Searches for the message in the server.
    outputFile << server.search(userID, mailID) << std::endl;

    // Verifies if the output file was correctly written.
    if (outputFile.bad())
    {
        throw std::runtime_error(std::string("Error: Output file not appropriately written!"));
    }
}