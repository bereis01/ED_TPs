#ifndef STRINGLIST_H
#define STRINGLIST_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>

#include "memlog.hpp"

class StringNode
{
private:
    // Constructor.
    StringNode() : quantity(0), word("") {}
    StringNode(std::string wordAux) : quantity(1), word(wordAux) {}

    // Compares two nodes based on a given order.
    bool biggerThan(StringNode &rhs, int *charOrder);
    bool smallerThan(StringNode &rhs, int *charOrder);

    // Attributes.
    int quantity;
    std::string word;

    friend class StringList;
};

class StringList
{
public:
    // Constructor, destructor.
    StringList(int maxSizeAux);
    ~StringList();

    // Inserts a new word in the list.
    void insert(std::string word);

    // Orders the list.
    void setOrder(std::stringstream &orderStream);
    void order(int median, int minPartSize);

    // Prints each word and its quantity to a given file.
    void print(std::ofstream &outputFile);

    // Analysis tools.
    void loadToMemory();

private:
    // Attributes.
    int size;
    int maxSize;
    int first;
    int last;
    StringNode *list;
    int *charOrder;

    // Auxiliary methods for ordenation. Based on the Quick Sort and Insertion Sort algorithms.
    void quickSort(int firstIndex, int lastIndex, int median, int minPartSize);
    void partition(int firstIndex, int lastIndex, int &i, int &j, int median);
    void insertionSort(int firstIndex, int lastIndex);
    StringNode median(int firstIndex, int lastIndex, int median);
};

#endif