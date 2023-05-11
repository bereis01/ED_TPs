#include "mailbox.hpp"

Mail::Mail(int messageKeyAux, int userKeyAux, std::string messageAux)
{
    this->messageKey = messageKeyAux;
    this->userKey = userKeyAux;
    this->message = messageAux;
    this->parent = nullptr;
    this->left = nullptr;
    this->right = nullptr;
}

MailBox::~MailBox()
{
    // Traverses recursively the tree, deallocating each allocated node.
    this->clear(this->root);
}

void MailBox::clear(Mail *&rootAux)
{
    // Traverses recursively the tree, deallocating each allocated node.
    if (rootAux != nullptr)
    {
        // Analysis tools.
        LEMEMLOG((long int)&(rootAux->messageKey), sizeof(int), 0);

        this->clear(rootAux->left);
        this->clear(rootAux->right);

        delete rootAux;
    }
}

void MailBox::insert(Mail *parentAux, Mail *&rootAux, int messageKeyAux, int userKeyAux, std::string messageAux)
{
    // If the node is currently not allocated, inserts the new node.
    if (rootAux == nullptr)
    {
        rootAux = new Mail(messageKeyAux, userKeyAux, messageAux);
        rootAux->parent = parentAux;

        // Analysis tools.
        ESCREVEMEMLOG((long int)&(rootAux->messageKey), sizeof(int), 0);
    }
    // Else, recursively traverses the tree in search for a spot.
    else
    {
        // Analysis tools.
        LEMEMLOG((long int)&(rootAux->messageKey), sizeof(int), 0);

        // If the key is bigger than the node's, traverses to the left.
        if (messageKeyAux < rootAux->messageKey)
        {
            this->insert(rootAux, rootAux->left, messageKeyAux, userKeyAux, messageAux);
        }
        // Else, traverses to the right.
        else
        {
            this->insert(rootAux, rootAux->right, messageKeyAux, userKeyAux, messageAux);
        }
    }
}

bool MailBox::remove(Mail *&rootAux, int messageKeyAux, int userKeyAux)
{
    // If the node is currently not allocated, the searched node is not in the list.
    if (rootAux == nullptr)
    {
        return false;
    }
    // If the given key is found, removes the node.
    else if (rootAux->messageKey == messageKeyAux && rootAux->userKey == userKeyAux)
    {
        // Analysis tools.
        LEMEMLOG((long int)&(rootAux->messageKey), sizeof(int), 0);

        this->removeAuxiliary(rootAux);

        return true;
    }
    // Else, recursively traverses the tree in search for the node to remove.
    else
    {
        // Analysis tools.
        LEMEMLOG((long int)&(rootAux->messageKey), sizeof(int), 0);

        // If the key is bigger than the node's, traverses to the left.
        if (messageKeyAux < rootAux->messageKey)
        {
            return this->remove(rootAux->left, messageKeyAux, userKeyAux);
        }
        // Else, traverses to the right.
        else
        {
            return this->remove(rootAux->right, messageKeyAux, userKeyAux);
        }
    }
}

void MailBox::removeAuxiliary(Mail *&rootAux)
{
    // Case in which the node doesn't have any childs.
    if (rootAux->left == nullptr && rootAux->right == nullptr)
    {
        delete rootAux;
        rootAux = nullptr;
    }
    // Case in which the node has only the right child.
    else if (rootAux->left == nullptr && rootAux->right != nullptr)
    {
        Mail *mailForDeletion = rootAux;
        rootAux = rootAux->right;

        delete mailForDeletion;
    }
    // Case in which the node has only the left child.
    else if (rootAux->left != nullptr && rootAux->right == nullptr)
    {
        Mail *mailForDeletion = rootAux;
        rootAux = rootAux->left;

        delete mailForDeletion;
    }
    // Case in which the node has both childs.
    else
    {
        // Finds the direct predecessor of the node.
        Mail *predecessor = rootAux;
        predecessor = predecessor->left;
        while (predecessor->right != nullptr)
        {
            predecessor = predecessor->right;
        }

        // Case in which the predecessor has one left child.
        if (predecessor->left != nullptr)
        {
            Mail *mailForDeletion = rootAux;

            if (predecessor != rootAux->left)
            {
                predecessor->parent->right = predecessor->left;
                predecessor->left = rootAux->left;
            }
            predecessor->right = rootAux->right;
            rootAux = predecessor;

            delete mailForDeletion;
        }
        // Case in which the predecessor has no childs.
        else
        {
            Mail *mailForDeletion = rootAux;

            if (predecessor != rootAux->left)
            {
                predecessor->parent->right = nullptr;
                predecessor->left = rootAux->left;
            }
            predecessor->right = rootAux->right;
            rootAux = predecessor;

            delete mailForDeletion;
        }
    }
}

std::string MailBox::search(Mail *&rootAux, int messageKeyAux, int userKeyAux)
{
    // If the node is currently not allocated, the key is not in the tree.
    if (rootAux == nullptr)
    {
        return "MENSAGEM INEXISTENTE";
    }
    // If the given key is found.
    else if (rootAux->messageKey == messageKeyAux && rootAux->userKey == userKeyAux)
    {
        // Analysis tools.
        LEMEMLOG((long int)&(rootAux->messageKey), sizeof(int), 0);

        return rootAux->message;
    }
    // Else, recursively traverses the tree in search for the key.
    else
    {
        // Analysis tools.
        LEMEMLOG((long int)&(rootAux->messageKey), sizeof(int), 0);

        // If the key is bigger than the node's, traverses to the left.
        if (messageKeyAux < rootAux->messageKey)
        {
            return this->search(rootAux->left, messageKeyAux, userKeyAux);
        }
        // Else, traverses to the right.
        else
        {
            return this->search(rootAux->right, messageKeyAux, userKeyAux);
        }
    }
}