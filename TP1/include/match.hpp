#ifndef POKER_H
#define POKER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>

#include "player.hpp"
#include "card.hpp"
#include "msgassert.hpp"
#include "memlog.hpp"

class Match
{
public:
    // Constructor, destructor.
    Match();

    // Match manipulation methods.
    void initializeMatch(std::ifstream &inputFile);
    void executeMatch(std::ifstream &inputFile, std::ofstream &outputFile);
    void readRoundInfo(std::ifstream &inputFile, int &numOfPlayers, double &initialBet);
    void readPlayerInfo(std::ifstream &inputFile, int numOfPlayers, std::string *playerNames, double *playerBets);
    void updatePlayerStatus(std::string playerName, double playerBet);
    void updatePlayerHand(std::string playerName, std::stringstream &handInput);

    // Match information methods.
    void outputResults(std::ofstream &outputFile);

private:
    // Attributes.
    ListOfPlayers listOfPlayers;
    int numOfRounds;
    int roundCount;
    double initialAmount;
};

#endif