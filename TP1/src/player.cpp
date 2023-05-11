#include "player.hpp"

// Player constructor.
Player::Player(std::string nameAux, double amountAux)
{
    // Analysis tools.
    ESCREVEMEMLOG((long int)&(this->name), sizeof(this->name), 0);

    this->name = nameAux;
    this->amount = amountAux;
}

// Set method for the amount attribute.
void Player::setAmount(double amountAux)
{
    this->amount = amountAux;
}

// Set method for the vector of cards. Sets the attributes of the indexed card.
void Player::setCard(int index, int valueAux, char suitAux)
{
    this->hand[index].setValue(valueAux);
    this->hand[index].setSuit(suitAux);
}

// Overloaded operator > for Player class based on the amount attribute. If both have the same amount, based on the alphabetical order of their names.
bool Player::operator>(Player &rhs)
{
    if (this->amount > rhs.amount)
    {
        return true;
    }
    else if (this->amount < rhs.amount)
    {
        return false;
    }
    else
    {
        if (this->name < rhs.name)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

// ListOfPlayers destructor.
ListOfPlayers::~ListOfPlayers()
{
    PlayerNode *holdVar;
    while (this->first != nullptr)
    {
        holdVar = this->first;
        this->first = this->first->next;
        delete holdVar;
    }
    this->first = nullptr;
    this->last = nullptr;
}

// Get methods for a player, given its name.
Player *ListOfPlayers::getPlayer(std::string nameAux)
{
    PlayerNode *iterator = this->first;

    // Scans through the list looking for the cell with the name passed as argument.
    while (iterator != nullptr)
    {
        if (iterator->player.getName() == nameAux)
        {
            return &(iterator->player);
        }
        iterator = iterator->next;
    }

    // In case no player is found.
    avisoAssert(0, "No player was found!");
    return nullptr;
}

// Insert method.
void ListOfPlayers::insert(std::string nameAux, double amountAux)
{
    // Case in which the list is empty.
    if (this->last == nullptr)
    {
        this->first = new PlayerNode(nameAux, amountAux);
        this->last = this->first;
    }
    // Case in which the list has any element.
    else
    {
        this->last->next = new PlayerNode(nameAux, amountAux);
        this->last->next->before = this->last;
        this->last = this->last->next;
    }
    this->size++;
}

// Remove method.
void ListOfPlayers::remove(std::string nameAux)
{
    PlayerNode *iterator = this->first;

    // Scans through the list looking for the cell with the name passed as argument.
    while (iterator != nullptr)
    {
        if (iterator->player.getName() == nameAux)
        {
            // Removes any pointer to the cell from the list.
            iterator->before->next = iterator->next;
            iterator->next->before = iterator->before;

            delete iterator;
            this->size--;

            return;
        }
        iterator = iterator->next;
    }

    // In case no player is found.
    avisoAssert(0, "No player was found!");
}

// Orders the list. Based on the BubbleSort algorithm.
void ListOfPlayers::order()
{
    for (int i = 0; i < this->size; i++)
    {
        PlayerNode *iterator = this->first->next;

        for (int j = 1; j < this->size - i; j++)
        {
            if (iterator->player > iterator->before->player)
            {
                Player temp = iterator->before->player;
                iterator->before->player = iterator->player;
                iterator->player = temp;
            }

            iterator = iterator->next;
        }
    }
}

// Verifies if a certain player exists in the list.
bool ListOfPlayers::playerExists(std::string nameAux)
{
    PlayerNode *iterator = this->first;
    while (iterator != nullptr)
    {
        if (iterator->player.getName() == nameAux)
        {
            return true;
        }
        iterator = iterator->next;
    }
    return false;
}

// Returns the current amount of a player.
double ListOfPlayers::verifyAmount(std::string nameAux)
{
    PlayerNode *iterator = this->first;

    // Scans through the list looking for the cell with the name passed as argument.
    while (iterator != nullptr)
    {
        if (iterator->player.getName() == nameAux)
        {
            return iterator->player.getAmount();
        }
        iterator = iterator->next;
    }

    // In case no player is found.
    avisoAssert(0, "No player was found!");
    return -1;
}

// Updates the current amount of a player.
void ListOfPlayers::updateAmount(std::string nameAux, double discount)
{
    PlayerNode *iterator = this->first;

    // Scans through the list looking for the cell with the name passed as argument.
    while (iterator != nullptr)
    {
        if (iterator->player.getName() == nameAux)
        {
            iterator->player.setAmount(iterator->player.getAmount() - discount);

            return;
        }
        iterator = iterator->next;
    }

    // In case no player is found.
    avisoAssert(0, "No player was found!");
    return;
}

// Update the player's card hand.
void ListOfPlayers::updateHand(std::string nameAux, std::stringstream &handInput)
{
    PlayerNode *iterator = this->first;

    // Scans through the list looking for the cell with the name passed as argument.
    while (iterator != nullptr)
    {
        if (iterator->player.getName() == nameAux)
        {
            int valueAux;
            char suitAux;
            for (int i = 0; i < 5; i++)
            {
                handInput >> valueAux >> suitAux;

                // Verifies if the string stream was correctly read.
                erroAssert(!handInput.fail(), "Error reading from the string stream!");

                iterator->player.setCard(i, valueAux, suitAux);
            }

            iterator->player.orderHand();
            iterator->player.identifyHand();

            return;
        }
        iterator = iterator->next;
    }

    // In case no player is found.
    avisoAssert(0, "No player was found!");
    return;
}

// Applies a initial bet discount to all players in the list.
void ListOfPlayers::applyInitialBet(double initialBetAux)
{
    PlayerNode *iterator = this->first;
    while (iterator != nullptr)
    {
        this->updateAmount(iterator->player.getName(), initialBetAux);
        iterator = iterator->next;
    }
}

// Verifies the winner of a round and outputs the result to a file.
void ListOfPlayers::verifyWinner(std::string *playerNames, int numOfPlayers, double totalBet, std::ofstream &outputFile)
{
    // Creates references to the players participating in the round.
    Player *players[numOfPlayers];
    for (int i = 0; i < numOfPlayers; i++)
    {
        players[i] = this->getPlayer(playerNames[i]);
    }

    // Compares each players' hand in order to determine the winner(s).
    int count = 0;
    Player *winners[numOfPlayers];
    winners[0] = players[0];
    for (int i = 1; i < numOfPlayers; i++)
    {
        if ((players[i]->getHand()).compare(winners[0]->getHand()) == 1)
        {
            winners[0] = players[i];
            count = 0;
        }
        else if ((players[i]->getHand()).compare(winners[0]->getHand()) == 0)
        {
            count++;
            winners[count] = players[i];
        }
    }

    // Updates the information of the winner(s) and outputs the round results.
    for (int i = 0; i < count + 1; i++)
    {
        this->updateAmount(winners[i]->getName(), -(int)(totalBet / (count + 1)));
    }
    this->outputWinner(outputFile, winners, count, totalBet);
}

// Verifies if the player has enough money to play. Fails if player is not in the list.
int ListOfPlayers::sanityTest(std::string playerName, double playerBet, double initialBet)
{
    if (this->verifyAmount(playerName) < playerBet + initialBet)
    {
        return 0;
    }

    return 1;
}

// Outputs the winner(s) information to a file.
void ListOfPlayers::outputWinner(std::ofstream &outputFile, Player *winners[], int count, double totalBet)
{
    // If there's only one winner.
    if (count == 0)
    {
        outputFile << count + 1 << " " << totalBet << " " << (winners[0]->getHand()).getCategory() << std::endl;
        outputFile << winners[0]->getName();
        outputFile << std::endl;

        // Verifies if the output file was correctly written.
        erroAssert(!outputFile.fail(), "Error writing on the output file!");
    }
    // If there's more than one winner.
    else
    {
        // Orders the winners' vector based on their names.
        for (int i = 0; i < count + 1; i++)
        {
            for (int j = 1; j < count + 1 - i; j++)
            {
                if (winners[j - 1]->getName() > winners[j]->getName())
                {
                    Player *temp = winners[j - 1];
                    winners[j - 1] = winners[j];
                    winners[j] = temp;
                }
            }
        }

        outputFile << count + 1 << " " << (int)(totalBet / (count + 1)) << " " << (winners[0]->getHand()).getCategory() << std::endl;

        // Verifies if the output file was correctly written.
        erroAssert(!outputFile.fail(), "Error writing on the output file!");

        for (int i = 0; i < count + 1; i++)
        {
            outputFile << winners[i]->getName();
            outputFile << std::endl;

            // Verifies if the output file was correctly written.
            erroAssert(!outputFile.fail(), "Error writing on the output file!");
        }
    }
}

// Outputs the name and amount of all players in the list to a given file.
void ListOfPlayers::outputList(std::ofstream &outputFile)
{
    PlayerNode *iterator = this->first;

    while (iterator != nullptr)
    {
        // Outputs name and amount information
        outputFile << iterator->player.getName() << " " << iterator->player.getAmount() << std::endl;

        // Verifies if the output file was correctly written.
        erroAssert(!outputFile.fail(), "Error writing on the output file!");

        iterator = iterator->next;
    }
}