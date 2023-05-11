#include <iostream>
#include <fstream>
#include <exception>

#include "mailserver.hpp"
#include "fileoperations.hpp"
#include "memlog.hpp"

int main(int argc, char **argv)
{
    // Analysis tools were removed to avoid the generation of the log file.

    // Gathers and initializes the input and output files.
    std::ifstream inputFile;
    std::ofstream outputFile;
    initializeFiles(argc, argv, inputFile, outputFile);

    // Verifies if all files were successfully opened.
    if (!inputFile.is_open())
    {
        throw std::runtime_error(std::string("Error: Input file not appropriately opened!"));
    }
    if (!outputFile.is_open())
    {
        throw std::runtime_error(std::string("Error: Output file not appropriately opened!"));
    }

    // Gathers the server size and initializes a properly sized mail server object.
    int mailServerSize;
    inputFile >> mailServerSize;

    // Verifies if the input file was correctly read.
    if (inputFile.bad())
    {
        throw std::runtime_error(std::string("Error: Input file not appropriately read!"));
    }

    MailServer server(mailServerSize);

    // Reads from the input file each command, executing the according operation, if applicable.
    std::string serverCommand;
    while (inputFile >> serverCommand)
    {
        // Verifies if the input file was correctly read.
        if (inputFile.bad())
        {
            throw std::runtime_error(std::string("Error: Input file not appropriately read!"));
        }

        // Inserts a new mail for a certain user.
        if (serverCommand == "ENTREGA")
        {
            insertMail(server, inputFile, outputFile);
        }
        // Removes a given mail from a certain user.
        else if (serverCommand == "APAGA")
        {
            removeMail(server, inputFile, outputFile);
        }
        // Searches for a given mail from a certain user.
        else if (serverCommand == "CONSULTA")
        {
            searchMail(server, inputFile, outputFile);
        }
    }

    return 0;
}