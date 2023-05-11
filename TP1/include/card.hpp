#ifndef CARD_H
#define CARD_H

#include <iostream>

#include "msgassert.hpp"
#include "memlog.hpp"

class Card
{
public:
    // Constructor.
    Card(int valueAux = 0, char suitAux = 0);

    // Set methods.
    void setValue(int valueAux);
    void setSuit(char suitAux);

    // Get methods.
    int getValue() { return this->value; }
    char getSuit() { return this->suit; }

    // Overloaded operators.
    bool operator>(Card &rhs);
    bool operator<(Card &rhs);
    bool operator==(Card &rhs);

private:
    // Attributes.
    int value;
    char suit;
};

class CardHand
{
public:
    // Constructor, destructor.
    CardHand();

    // Get methods.
    int getWeight() { return this->weight; }
    std::string getCategory() { return this->handCategory; }

    // Hand manipulation methods.
    void orderCardHand();
    void identifyCardHand();

    // Overloaded operators.
    Card &operator[](int index) { return this->hand[index]; }
    int compare(CardHand &rhs);

private:
    // Attributes.
    Card hand[5];
    std::string handCategory;
    int weight;
    int higherCard;
    int onePair;
    int twoPair;
    int threeOfAKind;
    int fourOfAKind;
};

#endif