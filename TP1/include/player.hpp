#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <fstream>
#include <sstream>

#include "card.hpp"
#include "msgassert.hpp"
#include "memlog.hpp"

class Player
{
public:
    // Constructor.
    Player(std::string nameAux, double amountAux);

    // Set methods.
    void setAmount(double amountAux);
    void setCard(int index, int valueAux, char suitAux);

    // Get methods.
    std::string getName()
    {
        // Analysis tools.
        LEMEMLOG((long int)&(this->name), sizeof(this->name), 0);

        return this->name;
    }
    double getAmount() { return this->amount; }
    int getCardValue(int index) { return this->hand[index].getValue(); }
    char getCardSuit(int index) { return this->hand[index].getSuit(); }
    CardHand &getHand() { return this->hand; }

    // Card hand manipulation methods.
    void orderHand() { this->hand.orderCardHand(); }
    void identifyHand() { this->hand.identifyCardHand(); }

    // Overloaded operators.
    bool operator>(Player &rhs);

private:
    // Attributes.
    std::string name;
    double amount;
    CardHand hand;
};

class PlayerNode
{
public:
    // Constructor.
    PlayerNode(std::string nameAux, double amountAux) : player(nameAux, amountAux), next(nullptr), before(nullptr) {}

private:
    // Attributes.
    Player player;
    PlayerNode *next;
    PlayerNode *before;

    friend class ListOfPlayers;
};

class ListOfPlayers
{
public:
    // Constructor, destructor.
    ListOfPlayers() : size(0), first(nullptr), last(nullptr) {}
    ~ListOfPlayers();

    // Get methods.
    Player *getPlayer(std::string nameAux);
    int getSize() { return this->size; }

    // List manipulation methods.
    void insert(std::string nameAux, double amountAux);
    void remove(std::string nameAux);
    void order();

    // Player manipulation methods.
    bool playerExists(std::string nameAux);
    double verifyAmount(std::string nameAux);
    void updateAmount(std::string nameAux, double discount);
    void updateHand(std::string nameAux, std::stringstream &handInput);

    // Match manipulation methods.
    void applyInitialBet(double initialBetAux);
    void verifyWinner(std::string *playerNames, int numOfPlayers, double totalBet, std::ofstream &outputFile);
    int sanityTest(std::string playerName, double playerBet, double initialBet);

    // Information manipulation methods.
    void outputWinner(std::ofstream &outputFile, Player *winners[], int count, double totalBet);
    void outputList(std::ofstream &outputFile);

private:
    // Attributes.
    int size;
    PlayerNode *first;
    PlayerNode *last;
};

#endif