#include "stringList.hpp"

bool StringNode::biggerThan(StringNode &rhs, int *charOrder)
{
    int index = 0;
    // Traverses both words, comparing each corresponding letter.
    while (1)
    {
        // Determines the weight of each letter.
        int lhsWeight, rhsWeight;
        if (this->word[index] >= 97 && this->word[index] <= 122)
        {
            lhsWeight = charOrder[this->word[index] - 97];
        }
        else
        {
            lhsWeight = this->word[index];
        }
        if (rhs.word[index] >= 97 && rhs.word[index] <= 122)
        {
            rhsWeight = charOrder[rhs.word[index] - 97];
        }
        else
        {
            rhsWeight = rhs.word[index];
        }

        // Compares both, returning a corresponding value.
        if (lhsWeight < rhsWeight)
        {
            return false;
        }
        else if (lhsWeight > rhsWeight)
        {
            return true;
        }
        else
        {
            if ((int)this->word.size() == index + 1 || (int)this->word.size() == 0)
            {
                return false;
            }
            else if ((int)rhs.word.size() == index + 1 || (int)rhs.word.size() == 0)
            {
                return true;
            }
            else
            {
                index++;
            }
        }
    }
}

bool StringNode::smallerThan(StringNode &rhs, int *charOrder)
{
    int index = 0;
    // Traverses both words, comparing each corresponding letter.
    while (1)
    {
        // Determines the weight of each letter.
        int lhsWeight, rhsWeight;
        if (this->word[index] >= 97 && this->word[index] <= 122)
        {
            lhsWeight = charOrder[this->word[index] - 97];
        }
        else
        {
            lhsWeight = this->word[index];
        }
        if (rhs.word[index] >= 97 && rhs.word[index] <= 122)
        {
            rhsWeight = charOrder[rhs.word[index] - 97];
        }
        else
        {
            rhsWeight = rhs.word[index];
        }

        // Compares both, returning a corresponding value.
        if (lhsWeight < rhsWeight)
        {
            return true;
        }
        else if (lhsWeight > rhsWeight)
        {
            return false;
        }
        else
        {
            if ((int)rhs.word.size() == index + 1 || (int)rhs.word.size() == 0)
            {
                return false;
            }
            else if ((int)this->word.size() == index + 1 || (int)this->word.size() == 0)
            {
                return true;
            }
            else
            {
                index++;
            }
        }
    }
}

StringList::StringList(int maxSizeAux)
{
    this->size = 0;
    this->first = 0;
    this->last = 0;

    // Guarantees that the maximum size parameter has a valid value.
    if (maxSizeAux <= 0)
    {
        this->maxSize = 0;
        this->list = nullptr;
        std::cerr << "Error: Invalid parameter for StringList constructor! Maximum size is an invalid size!" << std::endl;
    }
    else
    {
        this->maxSize = maxSizeAux;
        this->list = new StringNode[maxSizeAux];
    }

    // Initializes the ordenation vector based on the alphabetical order.
    {
        this->charOrder = new int[26];
        for (int i = 0; i < 26; i++)
        {
            charOrder[i] += i + 97;
        }
    }
}

StringList::~StringList()
{
    // Releases allocated memory.
    delete[] this->list;
    delete[] this->charOrder;
}

void StringList::insert(std::string wordAux)
{
    // Case in which the list is empty.
    if (this->size == 0)
    {
        this->list[this->first] = StringNode(wordAux);
        size++;

        // Analysis tools.
        ESCREVEMEMLOG((long int)&(this->list[this->first].word), sizeof(std::string), 0);
    }
    else
    {
        // Verifies if the word is already in the list, increasing its quantity if so.
        for (int i = 0; i < this->size; i++)
        {
            // Analysis tools.
            LEMEMLOG((long int)&(this->list[i].word), sizeof(std::string), 0);

            if (wordAux == this->list[i].word)
            {
                this->list[i].quantity++;
                return;
            }
        }
        // If it is not.
        if (this->size < this->maxSize)
        {
            this->last++;
            this->list[this->last] = StringNode(wordAux);

            this->size++;

            // Analysis tools.
            ESCREVEMEMLOG((long int)&(this->list[this->last].word), sizeof(std::string), 0);
        }
        // Case in which the list is full.
        else
        {
            std::cerr << "Error: The list is currently full!" << std::endl;
        }
    }
}

void StringList::setOrder(std::stringstream &orderStream)
{
    // Rearranges the ordenation vector based on the order weights passed as parameter.
    int weight = 97;
    char charHold;
    while (orderStream >> charHold)
    {
        // Verifies if the stream was correctly read/written.
        if (orderStream.bad())
        {
            throw std::runtime_error(std::string("Error: Stream not appropriately read/written!"));
        }

        if (charHold >= 65 && charHold <= 90)
        {
            this->charOrder[(int)charHold - 65] = weight;
            weight++;
        }
        else if (charHold >= 97 && charHold <= 122)
        {
            this->charOrder[(int)charHold - 97] = weight;
            weight++;
        }
    }
}

void StringList::order(int median, int minPartSize)
{
    // Calls the algorithm for sorting.
    this->quickSort(this->first, this->last, median, minPartSize);
}

void StringList::print(std::ofstream &outputFile)
{
    // Traverses the list, printing each cell's information.
    for (int i = 0; i < this->size; i++)
    {
        outputFile << this->list[i].word << " " << this->list[i].quantity << std::endl;

        // Verifies if the output file was correctly written.
        if (outputFile.bad())
        {
            throw std::runtime_error(std::string("Error: Output file not appropriately written!"));
        }

        // Analysis tools.
        LEMEMLOG((long int)&(this->list[i].word), sizeof(std::string), 0);
    }

    outputFile << "#FIM" << std::endl;

    // Verifies if the output file was correctly written.
    if (outputFile.bad())
    {
        throw std::runtime_error(std::string("Error: Output file not appropriately written!"));
    }
}

void StringList::quickSort(int firstIndex, int lastIndex, int median, int minPartSize)
{
    if (lastIndex - firstIndex + 1 <= minPartSize)
    {
        // Uses another algorithm if the partition size is below a given value;
        insertionSort(firstIndex, lastIndex);
    }
    else
    {
        // Orders the current partition.
        int i, j;
        partition(firstIndex, lastIndex, i, j, median);

        // Orders the newly created partitions recursively.
        if (firstIndex < j)
        {
            quickSort(firstIndex, j, median, minPartSize);
        }
        if (i < lastIndex)
        {
            quickSort(i, lastIndex, median, minPartSize);
        }
    }
}

void StringList::partition(int firstIndex, int lastIndex, int &i, int &j, int median)
{
    // Sets both auxiliary "pointers".
    i = firstIndex;
    j = lastIndex;

    // Sets the pivot.
    StringNode pivot = this->median(firstIndex, lastIndex, median);

    // Exchanges cells.
    while (i <= j)
    {
        // Analysis tools.
        LEMEMLOG((long int)&(this->list[i].word), sizeof(std::string), 0);

        while (this->list[i].smallerThan(pivot, this->charOrder))
        {
            i++;

            // Analysis tools.
            LEMEMLOG((long int)&(this->list[i].word), sizeof(std::string), 0);
        }

        // Analysis tools.
        LEMEMLOG((long int)&(this->list[j].word), sizeof(std::string), 0);

        while (this->list[j].biggerThan(pivot, this->charOrder))
        {
            j--;

            // Analysis tools.
            LEMEMLOG((long int)&(this->list[j].word), sizeof(std::string), 0);
        }

        if (i <= j)
        {
            StringNode nodeHold = this->list[i];
            this->list[i] = this->list[j];
            this->list[j] = nodeHold;

            // Analysis tools.
            ESCREVEMEMLOG((long int)&(this->list[i].word), sizeof(std::string), 0);
            ESCREVEMEMLOG((long int)&(this->list[j].word), sizeof(std::string), 0);

            i++;
            j--;
        }
    }
}

void StringList::insertionSort(int firstIndex, int lastIndex)
{
    // Orders a given partition based on the insertion sort algorithm.
    for (int i = firstIndex + 1; i <= lastIndex; i++)
    {
        StringNode nodeHold = this->list[i];

        // Analysis tools.
        LEMEMLOG((long int)&(this->list[i].word), sizeof(std::string), 0);

        int j = i - 1;

        // Analysis tools.
        LEMEMLOG((long int)&(this->list[j].word), sizeof(std::string), 0);

        while (j >= 0 && !this->list[j].smallerThan(nodeHold, this->charOrder))
        {
            // Analysis tools.
            ESCREVEMEMLOG((long int)&(this->list[j + 1].word), sizeof(std::string), 0);

            this->list[j + 1] = this->list[j];
            j--;

            // Analysis tools.
            LEMEMLOG((long int)&(this->list[j].word), sizeof(std::string), 0);
        }
        this->list[j + 1] = nodeHold;

        // Analysis tools.
        ESCREVEMEMLOG((long int)&(this->list[j + 1].word), sizeof(std::string), 0);
    }
}

StringNode StringList::median(int firstIndex, int lastIndex, int median)
{
    // Initializes control variables.
    int indexHold = firstIndex;
    int numOfComp = 0;

    // Guarantees that there will be a correct amount of elements.
    if (lastIndex - firstIndex + 1 < median || 1 >= median)
    {
        // Analysis tools.
        LEMEMLOG((long int)&(this->list[indexHold].word), sizeof(std::string), 0);

        return this->list[indexHold];
    }

    // Calculates the median.
    for (int i = firstIndex; i < firstIndex + median; i++)
    {
        for (int j = firstIndex; j < firstIndex + median; j++)
        {
            // Analysis tools.
            LEMEMLOG((long int)&(this->list[i].word), sizeof(std::string), 0);
            LEMEMLOG((long int)&(this->list[j].word), sizeof(std::string), 0);

            if (i != j && !this->list[i].smallerThan(this->list[j], this->charOrder))
            {
                numOfComp++;
            }
        }

        if (numOfComp == (median - 1) / 2)
        {
            indexHold = i;
            break;
        }

        numOfComp = 0;
    }

    return this->list[indexHold];
}

void StringList::loadToMemory()
{
    for (int i = 0; i < this->size; i++)
    {
        StringNode nodeHold = this->list[i];

        // Analysis tools.
        LEMEMLOG((long int)&(this->list[i].word), sizeof(std::string), 0);
    }
}