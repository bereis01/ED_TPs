#ifndef STRINGOPERATIONS_H
#define STRINGOPERATIONS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>

#include "memlog.hpp"

// Verifies the command line parameters and initiate (when applicable) the corresponding values.
void gatherArguments(int argc, char **argv, std::string &inputFile, std::string &outputFile, int &median, int &minPartSize);

// Extracts the text and the order bits from the input entry.
void gatherTextAndOrder(std::ifstream &inputFile, std::stringstream &text, std::stringstream &order, int &maxNumOfWords);

// Formats a given stream of text based on a set of defined rules.
void formatText(std::stringstream &text);

#endif