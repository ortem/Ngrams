#pragma once

#include "NgramTree.h"
#include <cstdint>
#define CAPACITY 10267

class HashTable
{
private:
    NgramTree **table;

    uint64_t hash(const char *str) const;

public:
    HashTable();

    void add(string &val);

    void remove(string &val);

    const SuffixList *suffixesOf(string &prefix) const;

    string searchInText(string &text);
};


class FoundSet
{
private:
    uint32_t capacity;

public:
    SuffixNode **set;
    uint32_t current;

    FoundSet(uint32_t capacity);

    void add(SuffixNode *ptr);
};