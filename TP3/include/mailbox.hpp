#ifndef MAILBOX_H
#define MAILBOX_H

#include <iostream>

#include "memlog.hpp"

// Binary search tree node representing a mail.
class Mail
{
private:
    // Constructor.
    Mail(int messageKeyAux, int userKeyAux, std::string messageAux);

    // Attributes.
    int messageKey;
    int userKey;
    std::string message;
    Mail *parent;
    Mail *left;
    Mail *right;

    friend class MailBox;
};

// Binary search tree modelling a mail box.
class MailBox
{
private:
    // Constructor, destructor.
    MailBox() : root(nullptr) {}
    ~MailBox();

    // Auxiliary method for the destructor.
    void clear(Mail *&rootAux);

    // Inserts a new cell into the tree.
    void insert(Mail *parentAux, Mail *&rootAux, int messageKeyAux, int userKeyAux, std::string messageAux);

    // Removes a given cell from the tree.
    bool remove(Mail *&rootAux, int messageKeyAux, int userKeyAux);

    // Auxiliary method for the remove functionality.
    void removeAuxiliary(Mail *&rootAux);

    // Searches for a given cell.
    std::string search(Mail *&rootAux, int messageKeyAux, int userKeyAux);

    // Attributes.
    Mail *root;

    friend class MailServer;
};

#endif