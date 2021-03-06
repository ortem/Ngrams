#pragma once

#include <string>
#include <list>

#include "HashFunctions.h"

using namespace std;

struct Change
{
    int type; // -1 - del; 1 = add
    int num;
};

struct ChangeNode
{
    Change change;
    ChangeNode *next;
};

class ChangeList
{
private:
    ChangeNode *head;
    ChangeNode *last;
public:
    ChangeList();
    //ChangeList()
    ChangeNode *getHead() const;
    void insert(ChangeNode *node, Change change);
    void add(int num);
    void remove(int num);
    int lastChangeBefore(int num); // -1 for delete (or 'no add before'), 1 for add
};

struct SuffixNode
{
    HString suffix;
    ChangeList changes;

    SuffixNode *next;
    int isFound = -1; // only for search

    void add(int num);
    void remove(int num);
    int lastChangeBefore(int num); // -1 for delete (or 'no add before'), 1 for add
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
