#ifndef FILEOPERATIONS_H
#define FILEOPERATIONS_H

#include <iostream>
#include <fstream>
#include <exception>

#include "mailserver.hpp"
#include "memlog.hpp"

// Receives the command line arguments and properly initialize the input/output files, if provided.
void initializeFiles(int argc, char **argv, std::ifstream &inputFile, std::ofstream &outputFile);

// Inserts a new mail on a given server.
void insertMail(MailServer &server, std::ifstream &inputFile, std::ofstream &outputFile);

// Removes a certain mail from a given server.
void removeMail(MailServer &server, std::ifstream &inputFile, std::ofstream &outputFile);

// Searches for a certain mail from a given server.
void searchMail(MailServer &server, std::ifstream &inputFile, std::ofstream &outputFile);

#endif