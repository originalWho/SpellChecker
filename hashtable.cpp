#include "hashtable.h"

int HashTable::dictionaryCount = 0;

HashTable::HashTable()
{

}

HashTable::~HashTable()
{

}

QList<QString> HashTable::getWords(int key) const
{
    return words.values(key);
}

