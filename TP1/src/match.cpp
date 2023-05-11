#include "match.hpp"

// Match constructor.
Match::Match()
{
    this->numOfRounds = 0;
    this->roundCount = 0;
    this->initialAmount = 0;
}

// Initializes a match based on the number of rounds and initial player money amount.
void Match::initializeMatch(std::ifstream &inputFile)
{
    int numOfRoundsAux;
    double initialAmountAux;

    std::string matchInputs;
    std::getline(inputFile, matchInputs);

    // Verifies if the input file was correctly read.
    erroAssert(!inputFile.fail(), "Error reading from the input file!");

    // Verifies if the input data matches the defined format.
    std::regex regExpr("\\s*\\d+\\s+\\d+\\s*");
    erroAssert(std::regex_match(matchInputs, regExpr), "Input data in an invalid format!");

    std::stringstream matchInputsStream;
    matchInputsStream << matchInputs;

    // Verifies if the string stream was correctly written.
    erroAssert(!matchInputsStream.fail(), "Error writing on the string stream!");

    matchInputsStream >> numOfRoundsAux >> initialAmountAux;

    // Verifies if the string stream was correctly read.
    erroAssert(!matchInputsStream.fail(), "Error reading from the string stream!");

    this->numOfRounds = numOfRoundsAux;
    this->initialAmount = initialAmountAux;
}

// Executes the sequence of rounds for a given match. Assumes that all players will participate on the first round.
void Match::executeMatch(std::ifstream &inputFile, std::ofstream &outputFile)
{
    // Executes all rounds.
    for (; this->roundCount < this->numOfRounds; this->roundCount++)
    {
        // Creates a flag for invalidation.
        int invalidFlag = 0;

        // Inputs the information of the round.
        int numOfPlayers;
        double initialBet;
        this->readRoundInfo(inputFile, numOfPlayers, initialBet);

        // Assures that if the round does not have any players, it is invalidated.
        if (numOfPlayers == 0)
        {
            invalidFlag = 1;
        }

        // Analysis tools.
        defineFaseMemLog(0);

        std::string playerNames[numOfPlayers];
        double playerBets[numOfPlayers];
        this->readPlayerInfo(inputFile, numOfPlayers, playerNames, playerBets);

        // If a single player make two bets, invalidates the round. Assumes that every player has a unique name.
        for (int i = 0; i < numOfPlayers; i++)
        {
            for (int j = 0; j < numOfPlayers; j++)
            {
                if (i == j)
                {
                    continue;
                }
                else
                {
                    if (playerNames[i] == playerNames[j])
                    {
                        invalidFlag = 1;
                    }
                }
            }
        }

        // If there's a bet that isn't a multiple of 50, invalidates the round.
        for (int i = 0; i < numOfPlayers; i++)
        {
            if ((int)playerBets[i] % 50 != 0)
            {
                invalidFlag = 1;
            }
        }

        // Verifies the total bet amount accumulated for the round.
        double totalBet = 0.0;
        for (int i = 0; i < numOfPlayers; i++)
        {
            totalBet += playerBets[i];
        }
        totalBet += this->listOfPlayers.getSize() * initialBet;

        // Analysis tools.
        defineFaseMemLog(1);

        // Executes the sanity test. Invalidades the round if applicable.
        for (int i = 0; i < numOfPlayers; i++)
        {
            if (!this->listOfPlayers.sanityTest(playerNames[i], playerBets[i], initialBet))
            {
                invalidFlag = 1;
            }
        }

        if (invalidFlag == 1)
        {
            outputFile << "0 0 I" << std::endl;

            // Verifies if the output file was correctly written.
            erroAssert(!outputFile.fail(), "Error writing on the output file!");

            continue;
        }

        // Updates the information of all players.

        // Analysis tools.
        defineFaseMemLog(2);

        this->listOfPlayers.applyInitialBet(initialBet);

        // Analysis tools.
        defineFaseMemLog(3);

        for (int i = 0; i < numOfPlayers; i++)
        {
            this->updatePlayerStatus(playerNames[i], playerBets[i]);
        }

        // Verifies the winner.

        // Analysis tools.
        defineFaseMemLog(4);

        this->listOfPlayers.verifyWinner(playerNames, numOfPlayers, totalBet, outputFile);
    }
}

// Reads the information of the round.
void Match::readRoundInfo(std::ifstream &inputFile, int &numOfPlayers, double &initialBet)
{
    std::string roundInputs;
    std::getline(inputFile, roundInputs);

    // Verifies if the input file was correctly read.
    erroAssert(!inputFile.fail(), "Error reading from the input file!");

    // Verifies if the input data matches the defined format.
    std::regex regExpr("\\s*\\d+\\s+\\d+\\s*");
    erroAssert(std::regex_match(roundInputs, regExpr), "Input data in an invalid format!");

    std::stringstream roundInputsStream;
    roundInputsStream << roundInputs;

    // Verifies if the string stream was correctly written.
    erroAssert(!roundInputsStream.fail(), "Error writing on the string stream!");

    roundInputsStream >> numOfPlayers >> initialBet;

    // Verifies if the string stream was correctly read.
    erroAssert(!roundInputsStream.fail(), "Error reading from the string stream!");
}

// Reads the information for each player regarding each round.
void Match::readPlayerInfo(std::ifstream &inputFile, int numOfPlayers, std::string *playerNames, double *playerBets)
{
    std::string playerInputs;

    for (int i = 0; i < numOfPlayers; i++)
    {
        std::stringstream nameInput;
        std::stringstream betInput;
        std::stringstream handInput;

        // Reads an input line for a given player.
        std::getline(inputFile, playerInputs);

        // Verifies if the input file was correctly read.
        erroAssert(!inputFile.fail(), "Error reading from the input file!");

        // Verifies if the input data matches the defined format.
        std::regex regExpr("\\s*(.*?)\\s+\\d+\\s+\\d+\\w\\s+\\d+\\w\\s+\\d+\\w\\s+\\d+\\w\\s+\\d+\\w\\s*");
        erroAssert(std::regex_match(playerInputs, regExpr), "Input data in an invalid format!");

        // Scans the line searching for the first integer (end of the name). Assumes that the input line is formatted.
        int index = 0;
        while (!isdigit(playerInputs[index]))
        {
            index++;
        }

        // Inputs the name of the player.
        int j = 0;
        for (; j < index - 1; j++)
        {
            nameInput << playerInputs[j];

            // Verifies if the string stream was correctly written.
            erroAssert(!nameInput.fail(), "Error writing on the string stream!");
        }
        std::string holdVar;
        nameInput >> playerNames[i];

        // Verifies if the string stream was correctly read.
        erroAssert(!nameInput.fail(), "Error reading from the string stream!");

        while (nameInput >> holdVar)
        {
            playerNames[i] += " ";
            playerNames[i] += holdVar;

            // Verifies if the string stream was correctly read.
            erroAssert(!nameInput.fail(), "Error reading from the string stream!");
        }

        this->updatePlayerStatus(playerNames[i], 0);

        // Inputs the bet of the player.
        j++;
        for (; playerInputs[j] != ' '; j++)
        {
            betInput << playerInputs[j];

            // Verifies if the string stream was correctly written.
            erroAssert(!betInput.fail(), "Error writing on the string stream!");
        }
        betInput >> playerBets[i];

        // Verifies if the string stream was correctly read.
        erroAssert(!betInput.fail(), "Error reading from the string stream!");

        // Inputs the hand of the player.
        for (; playerInputs[j] != '\0'; j++)
        {
            handInput << playerInputs[j];

            // Verifies if the string stream was correctly written.
            erroAssert(!handInput.fail(), "Error writing on the string stream!");
        }
        this->updatePlayerHand(playerNames[i], handInput);
    }
}

// Updates the status of a given player participating in the match.
void Match::updatePlayerStatus(std::string playerName, double playerBet)
{
    // If the player is already in the list.
    if (this->listOfPlayers.playerExists(playerName))
    {
        this->listOfPlayers.updateAmount(playerName, playerBet);
    }
    // If the player is not yet in the list.
    else if (this->roundCount == 0)
    {
        this->listOfPlayers.insert(playerName, this->initialAmount);
        this->listOfPlayers.updateAmount(playerName, playerBet);
    }
}

// Updates the card hand of a given player participating in the match.
void Match::updatePlayerHand(std::string playerName, std::stringstream &handInput)
{
    if (this->listOfPlayers.playerExists(playerName))
    {
        this->listOfPlayers.updateHand(playerName, handInput);
    }
}

// Outputs the information of all players to an output file.
void Match::outputResults(std::ofstream &outputFile)
{
    this->listOfPlayers.order();

    outputFile << "####" << std::endl;

    // Verifies if the output file was correctly written.
    erroAssert(!outputFile.fail(), "Error writing on the output file!");

    this->listOfPlayers.outputList(outputFile);
}