#include "HashTable.h"

const uint64_t HashTable::CAPACITY = 10267;
//const uint64_t HashTable::CAPACITY = 11;

HashTable::HashTable()
{
    table = new NgramTree *[CAPACITY];
    for (uint64_t i = 0; i < CAPACITY; i++)
        table[i] = new NgramTree();
}

void HashTable::add(const char *str, uint64_t length, uint64_t num)
{
    //cout << "HashTable: add " << str << " (" << num << ")" << endl;
    const char *suffixStr = str;
    uint64_t prefixSize = 0;
    while (!(*suffixStr == ' ' || prefixSize == length)) {
        suffixStr++;
        prefixSize++;
    }

    uint64_t hashPrefix = HashEngine::hashOfString(str, prefixSize);
    uint64_t hashSuffix = HashEngine::hashOfString(suffixStr, length - prefixSize);
    HString prefix = {str, prefixSize, hashPrefix};
    HString suffix = {suffixStr, length - prefixSize, hashSuffix};

    table[prefix.hash % CAPACITY]->add(prefix, suffix, num);
}

void HashTable::remove(const char *str, uint64_t length, uint64_t num)
{
    //cout << "HashTable: remove " << str << " (" << num << ")" << endl;
    const char *suffixStr = str;
    uint64_t prefixSize = 0;
    while (!(*suffixStr == ' ' || prefixSize == length)) {
        suffixStr++;
        prefixSize++;
    }

    uint64_t hashPrefix = HashEngine::hashOfString(str, prefixSize);
    uint64_t hashSuffix = HashEngine::hashOfString(suffixStr, length - prefixSize);
    HString prefix = {str, prefixSize, hashPrefix};
    HString suffix = {suffixStr, length - prefixSize, hashSuffix};

    table[prefix.hash % CAPACITY]->remove(prefix, suffix, num);
}

const SuffixList *HashTable::suffixesOf(const HString prefix) const
{
    Node *current = table[prefix.hash % CAPACITY]->root;
    while (current) {
        if (HashEngine::isEqual(current->prefix, prefix))
            return &current->suffixes;

        if (current->prefix.hash > prefix.hash)
            current = current->left;
        else
            current = current->right;
    }
    return nullptr;
}

FoundSet::FoundSet(uint64_t capacity)
    : capacity(capacity),
      current(0)
{
    set = new FoundNode[capacity];
}

void FoundSet::add(SuffixNode *ptr, const char *prefix)
{
    if (current < capacity) {
        set[current].node = ptr;
        set[current].prefix = prefix;
    }

    current++;
}