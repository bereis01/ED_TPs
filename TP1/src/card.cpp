#include "card.hpp"

// Card constructor.
Card::Card(int valueAux, char suitAux)
{
    this->value = valueAux;
    this->suit = suitAux;
}

// Set method for value attribute.
void Card::setValue(int valueAux)
{
    this->value = valueAux;
}

// Set method for suit attribute.
void Card::setSuit(char suitAux)
{
    this->suit = suitAux;
}

// Overloaded operator > for Card class. Returns the card with the higher value.
bool Card::operator>(Card &rhs)
{
    // Verifies if the cards are valid (initialized with valid values).
    erroAssert(this->value != 0 && this->suit != 0, "Invalid card!");
    erroAssert(rhs.value != 0 && rhs.suit != 0, "Invalid card!");

    if (this->value > rhs.getValue())
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Overloaded operator > for Card class. Returns the card with the lower value.
bool Card::operator<(Card &rhs)
{
    // Verifies if the cards are valid (initialized with valid values).
    erroAssert(this->value != 0 && this->suit != 0, "Invalid card!");
    erroAssert(rhs.value != 0 && rhs.suit != 0, "Invalid card!");

    if (this->value < rhs.getValue())
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Overloaded operator == for Card class. Returns true if both cards are equal in value.
bool Card::operator==(Card &rhs)
{
    // Verifies if the cards are valid (initialized with valid values).
    erroAssert(this->value != 0 && this->suit != 0, "Invalid card!");
    erroAssert(rhs.value != 0 && rhs.suit != 0, "Invalid card!");

    if (this->value == rhs.getValue())
    {
        return true;
    }
    else
    {
        return false;
    }
}

// CardHand constructor.
CardHand::CardHand()
{
    this->handCategory = " ";
    this->weight = 0;
    this->higherCard = 0;
    this->onePair = 0;
    this->twoPair = 0;
    this->threeOfAKind = 0;
    this->fourOfAKind = 0;
}

// Orders the vector of cards. Based on the BubbleSort algorithm.
void CardHand::orderCardHand()
{
    // Verifies if the cards are valid (initialized with valid values).
    for (int i = 0; i < 5; i++)
    {
        // Verifies if the cards are valid (initialized with valid values).
        erroAssert(this->hand[i].getValue() != 0 && this->hand[i].getSuit() != 0, "Invalid card!");
    }

    for (int i = 0; i < 5; i++)
    {
        for (int j = 1; j < 5 - i; j++)
        {
            if (hand[j - 1] > hand[j])
            {
                Card temp = hand[j - 1];
                hand[j - 1] = hand[j];
                hand[j] = temp;
            }
        }
    }
}

// Identify the current card hand based on one of the 10 possible plays of poker. Assumes that the hand of cards is ordered based on the value.
void CardHand::identifyCardHand()
{
    // Verifies if the cards are valid (initialized with valid values).
    for (int i = 0; i < 5; i++)
    {
        // Verifies if the cards are valid (initialized with valid values).
        erroAssert(this->hand[i].getValue() != 0 && this->hand[i].getSuit() != 0, "Invalid card!");
    }

    // Reset the current configuration of the hand.
    this->handCategory = " ";
    this->weight = 0;
    this->higherCard = 0;
    this->onePair = 0;
    this->twoPair = 0;
    this->threeOfAKind = 0;
    this->fourOfAKind = 0;

    // Flags used to determine conditions.
    int flush(1), two(0), three(0), full(0), four(0), sequence(1), royal(0);

    // Verifies if there are four equal cards.
    for (int i = 0; i < 2; i++)
    {
        if (this->hand[i] == this->hand[i + 1] && this->hand[i] == this->hand[i + 2] && this->hand[i] == this->hand[i + 3])
        {
            four = 1;
            this->fourOfAKind = this->hand[i].getValue();

            // Verifies the other card, which will be the "higher card" in case of draws.
            for (int j = 0; j < 5; j++)
            {
                if (this->hand[j].getValue() != this->fourOfAKind)
                {
                    this->higherCard = this->hand[j].getValue();
                }
            }

            break;
        }
    }

    // Verifies if there are three equal cards.
    for (int i = 0; four == 0 && i < 3; i++)
    {
        if (this->hand[i] == this->hand[i + 1] && this->hand[i] == this->hand[i + 2])
        {
            three = 1;
            this->threeOfAKind = this->hand[i].getValue();

            // Verifies if there is a pair (full house condition).
            for (int j = 0; three == 1 && j < 4; j++)
            {
                if (this->hand[j].getValue() != this->threeOfAKind)
                {
                    if (this->hand[j] == this->hand[j + 1])
                    {
                        full = 1;
                        this->onePair = this->hand[j].getValue();
                    }
                }
            }

            // If there's not a full house, determines the "higher card" among the other two.
            if (full != 1)
            {
                for (int j = 0; j < 5; j++)
                {
                    if (higherCard == 0 && this->hand[j].getValue() != this->threeOfAKind)
                    {
                        this->higherCard = this->hand[j].getValue();
                    }
                    else if (this->hand[j].getValue() > this->higherCard && this->hand[j].getValue() != this->threeOfAKind)
                    {
                        this->higherCard = this->hand[j].getValue();
                    }
                }
            }

            break;
        }
    }

    // Verifies if there are two equal cards.
    for (int i = 0; four == 0 && three == 0 && i < 4; i++)
    {
        if (this->hand[i] == this->hand[i + 1])
        {
            two = 1;
            this->onePair = this->hand[i].getValue();

            // Verifies if there is another pair.
            for (int j = 0; two == 1 && j < 4; j++)
            {
                if (this->hand[j].getValue() != this->onePair)
                {
                    if (this->hand[j] == this->hand[j + 1])
                    {
                        two = 2;
                        if (this->onePair > this->hand[j].getValue())
                        {
                            this->twoPair = this->hand[j].getValue();
                        }
                        else
                        {
                            this->twoPair = this->onePair;
                            this->onePair = this->hand[j].getValue();
                        }
                    }
                }
            }

            // If there are two pairs of cards, verifies the other card, which will be the "higher card" in case of draws.
            if (two == 2)
            {
                for (int j = 0; j < 5; j++)
                {
                    if (this->hand[j].getValue() != this->onePair && this->hand[j].getValue() != this->twoPair)
                    {
                        this->higherCard = this->hand[j].getValue();
                    }
                }
            }
            // If there is one pair of cards, verifies the other cards to determine which will be the "higher card" in case of draws.
            else if (two == 1)
            {
                for (int j = 0; j < 5; j++)
                {
                    if (higherCard == 0 && this->hand[j].getValue() != this->onePair)
                    {
                        this->higherCard = this->hand[j].getValue();
                    }
                    else if (this->hand[j].getValue() > this->higherCard && this->hand[j].getValue() != this->onePair)
                    {
                        this->higherCard = this->hand[j].getValue();
                    }
                }
            }

            break;
        }
    }

    // Verifies if there is a flush.
    for (int i = 1; i < 5; i++)
    {
        if (this->hand[i].getSuit() != this->hand[0].getSuit())
        {
            flush = 0;
        }
    }
    if (flush == 1 && full == 0 && four == 0)
    {
        this->higherCard = this->hand[0].getValue();
        for (int i = 1; i < 5; i++)
        {
            if (this->hand[i].getValue() > this->higherCard)
            {
                this->higherCard = this->hand[i].getValue();
            }
        }
    }

    // Verifies if there is a sequence.
    for (int i = 0; i < 4; i++)
    {
        if (this->hand[i].getValue() == 1)
        {
            if (this->hand[i + 1].getValue() != 10 && this->hand[i + 1].getValue() != 2)
            {
                sequence = 0;
                break;
            }
        }
        else
        {
            if (this->hand[i].getValue() != this->hand[i + 1].getValue() - 1)
            {
                sequence = 0;
                break;
            }
        }
    }

    // Verifies if the sequence, if it exists, is royal.
    if (sequence == 1 && this->hand[0].getValue() == 1 && this->hand[1].getValue() == 10)
    {
        royal = 1;
    }

    // Verifies the highest card of the hand, if applicable.
    if (four != 1 && three != 1 && two != 2 && two != 1)
    {
        this->higherCard = this->hand[0].getValue();
        for (int i = 1; i < 5; i++)
        {
            if (this->hand[i].getValue() > this->higherCard)
            {
                this->higherCard = this->hand[i].getValue();
            }
        }
    }

    // Based on the flags, verifies in which category the hand falls in.
    if (royal == 1 && flush == 1)
    {
        this->handCategory = "RSF";
        this->weight = 10;
    }

    else if (sequence == 1 && flush == 1)
    {
        this->handCategory = "SF";
        this->weight = 9;
    }

    else if (four == 1)
    {
        this->handCategory = "FK";
        this->weight = 8;
    }

    else if (full == 1)
    {
        this->handCategory = "FH";
        this->weight = 7;
    }

    else if (flush == 1)
    {
        this->handCategory = "F";
        this->weight = 6;
    }

    else if (sequence == 1)
    {
        this->handCategory = "S";
        this->weight = 5;
    }

    else if (three == 1)
    {
        this->handCategory = "TK";
        this->weight = 4;
    }

    else if (two == 2)
    {
        this->handCategory = "TP";
        this->weight = 3;
    }

    else if (two == 1)
    {
        this->handCategory = "OP";
        this->weight = 2;
    }

    else
    {
        this->handCategory = "HC";
        this->weight = 1;
    }
}

// Compares two card hands based on their characteristics.
int CardHand::compare(CardHand &rhs)
{
    // Verifies if the card hand is valid (initialized with valid values).
    erroAssert(this->weight != 0 && rhs.weight != 0, "Invalid card hand!");

    if (this->weight > rhs.weight)
    {
        return 1;
    }
    else if (this->weight < rhs.weight)
    {
        return -1;
    }
    else
    {
        switch (this->weight)
        {
        case 10:
            return 0;
            break;
        case 9:
            if (this->hand[0] > rhs.hand[0])
            {
                return 1;
            }
            else if (this->hand[0] < rhs.hand[0])
            {
                return -1;
            }
            else
            {
                return 0;
            }
            break;
        case 8:
            if (this->fourOfAKind > rhs.fourOfAKind)
            {
                return 1;
            }
            else if (this->fourOfAKind < rhs.fourOfAKind)
            {
                return -1;
            }
            else
            {
                if (this->higherCard > rhs.higherCard)
                {
                    return 1;
                }
                else if (this->higherCard < rhs.higherCard)
                {
                    return -1;
                }
                else
                {
                    return 0;
                }
            }
            break;
        case 7:
            if (this->threeOfAKind > rhs.threeOfAKind)
            {
                return 1;
            }
            else if (this->threeOfAKind < rhs.threeOfAKind)
            {
                return -1;
            }
            else
            {
                if (this->onePair > rhs.onePair)
                {
                    return 1;
                }
                else if (this->onePair < rhs.onePair)
                {
                    return -1;
                }
                else
                {
                    return 0;
                }
            }
            break;
        case 6:
            if (this->higherCard > rhs.higherCard)
            {
                return 1;
            }
            else if (this->higherCard < rhs.higherCard)
            {
                return -1;
            }
            else
            {
                return 0;
            }
            break;
        case 5:
        {
            int sumThis = this->hand[0].getValue() + this->hand[1].getValue();
            if (this->hand[0].getValue() == 1 && sumThis == 11)
            {
                sumThis += 10;
            }

            int sumRhs = rhs.hand[0].getValue() + rhs.hand[1].getValue();
            if (rhs.hand[0].getValue() == 1 && sumRhs == 11)
            {
                sumThis += 10;
            }

            if (sumThis > sumRhs)
            {
                return 1;
            }
            else if (sumThis < sumRhs)
            {
                return -1;
            }
            else
            {
                return 0;
            }
            break;
        }
        case 4:
            if (this->threeOfAKind > rhs.threeOfAKind)
            {
                return 1;
            }
            else if (this->threeOfAKind < rhs.threeOfAKind)
            {
                return -1;
            }
            else
            {
                if (this->higherCard > rhs.higherCard)
                {
                    return 1;
                }
                else if (this->higherCard < rhs.higherCard)
                {
                    return -1;
                }
                else
                {
                    return 0;
                }
            }
            break;
        case 3:
            if (this->onePair > rhs.onePair)
            {
                return 1;
            }
            else if (this->onePair < rhs.onePair)
            {
                return -1;
            }
            else
            {
                if (this->twoPair > rhs.twoPair)
                {
                    return 1;
                }
                else if (this->twoPair < rhs.twoPair)
                {
                    return -1;
                }
                else
                {
                    if (this->higherCard > rhs.higherCard)
                    {
                        return 1;
                    }
                    else if (this->higherCard < rhs.higherCard)
                    {
                        return -1;
                    }
                    else
                    {
                        return 0;
                    }
                }
            }
            break;
        case 2:
            if (this->onePair > rhs.onePair)
            {
                return 1;
            }
            else if (this->onePair < rhs.onePair)
            {
                return -1;
            }
            else
            {
                if (this->higherCard > rhs.higherCard)
                {
                    return 1;
                }
                else if (this->higherCard < rhs.higherCard)
                {
                    return -1;
                }
                else
                {
                    return 0;
                }
            }
            break;
        case 1:
            if (this->higherCard > rhs.higherCard)
            {
                return 1;
            }
            else if (this->higherCard < rhs.higherCard)
            {
                return -1;
            }
            else
            {
                return 0;
            }
            break;

        default:
            break;
        }
    }
    return -2;
}