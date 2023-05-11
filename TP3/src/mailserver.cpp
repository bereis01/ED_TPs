#include "mailserver.hpp"

MailServer::MailServer(int sizeAux)
{
    // Guarantees that a valid size was provided.
    if (sizeAux <= 0)
    {
        throw std::logic_error("Error: Invalid mail server size provided!");
    }

    this->size = sizeAux;
    this->server = new MailBox[sizeAux];
}

MailServer::~MailServer()
{
    // Deallocates the allocated memory.
    delete[] this->server;
}

std::string MailServer::insert(int userID, int messageID, std::string messageText)
{
    // Calculates the user hash index.
    int userHash = this->hash(userID);

    // Inserts a given message based on its ID to the corresponding user (binary search tree).
    this->server[userHash].insert(nullptr, this->server[userHash].root, messageID, userID, messageText);
    return "OK: MENSAGEM " + std::to_string(messageID) + " PARA " + std::to_string(userID) + " ARMAZENADA EM " + std::to_string(userHash);
}

std::string MailServer::remove(int userID, int messageID)
{
    // Calculates the user hash index.
    int userHash = this->hash(userID);

    // Removes a given message based on its ID from the corresponding user (binary search tree).
    if (this->server[userHash].remove(this->server[userHash].root, messageID, userID))
    {
        return "OK: MENSAGEM APAGADA";
    }
    else
    {
        return "ERRO: MENSAGEM INEXISTENTE";
    }
}

std::string MailServer::search(int userID, int messageID)
{
    // Calculates the user hash index.
    int userHash = this->hash(userID);

    // Returns the result of a query for a given message from a given user (binary search tree).
    return "CONSULTA " + std::to_string(userID) + " " + std::to_string(messageID) + ": " + this->server[userHash].search(this->server[userHash].root, messageID, userID);
}

int MailServer::hash(int key)
{
    // Hash function.
    return abs(key % this->size);
}