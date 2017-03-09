#pragma once

#include <string>
#include <list>

#include "HashFunctions.h"

using namespace std;

struct Change{
    char type; // -1 - del; 1 = add
    int num;
};

struct SuffixNode
{
    HString suffix;
    list<Change> chanages;

    SuffixNode *next;
    int isFound = -1; // only for search

    void add(int num);
    void remove(int num);

};

class SuffixList
{
private:
    SuffixNode *head;

public:
    SuffixList();
    SuffixList(const HString suffix);
    SuffixNode *getHead() const;
    void insert(SuffixNode *node, const HString suffix, int num);
    void remove(const HString suffix, int num);
};
