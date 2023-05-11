#ifndef MAILSERVER_H
#define MAILSERVER_H

#include <iostream>

#include "mailbox.hpp"
#include "memlog.hpp"

// Hash table modelling a mail server. Each entry is a binary search tree.
class MailServer
{
public:
    // Constructor.
    MailServer(int sizeAux);
    ~MailServer();

    // Inserts a new mail into the server for a given user.
    std::string insert(int userID, int messageID, std::string messageText);

    // Removes a certain mail based on a given user.
    std::string remove(int userID, int messageID);

    // Searches for a certain mail based on a given user.
    std::string search(int userID, int messageID);

private:
    // Attributes.
    int size;
    MailBox *server;

    // Hash function. Determines the index of a given key.
    int hash(int key);
};

#endif