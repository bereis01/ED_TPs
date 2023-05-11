#include <iostream>
#include <fstream>

#include "match.hpp"
#include "player.hpp"
#include "card.hpp"
#include "msgassert.hpp"
#include "memlog.hpp"

int main()
{
    // Analysis tools.
    // Memlog's commands were removed to avoid the generation of the log file.

    // Initializes the variables regarding the poker match.
    Match match;
    std::ifstream inputFile("entrada.txt");
    std::ofstream outputFile("saida.txt");

    // Verifies if both files were correctly opened.
    erroAssert(inputFile.good(), "Error opening the input file!\n");
    erroAssert(outputFile.good(), "Error opening the output file!\n");

    // Executes the match.
    match.initializeMatch(inputFile);
    match.executeMatch(inputFile, outputFile);

    // Outputs the results.
    match.outputResults(outputFile);

    return 0;
}