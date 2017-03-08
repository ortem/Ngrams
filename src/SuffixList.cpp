#include "SuffixList.h"

SuffixList::SuffixList()
    :
    head(nullptr)
{}

SuffixList::SuffixList(const HString suffix)
    : head(new SuffixNode)
{
    head->suffix = suffix;
    head->next = nullptr;
}

SuffixNode *SuffixList::getHead() const
{
    return this->head;
}

void SuffixList::insert(SuffixNode *node, const HString suffix, int num)
{
    if (node) {
        SuffixNode *tmp = node->next;
        node->next = new SuffixNode;
        node->next->suffix = suffix;
        node->next->next = tmp;
    }
        // insert after nullptr == insert before head
    else {
        SuffixNode *tmp = head;
        head = new SuffixNode;
        head->suffix = suffix;
        head->next = tmp;
    }

    node->add(num);

}

void SuffixList::remove(const HString suffix, int num)
{
    SuffixNode *node = head;
    SuffixNode *prev = nullptr;
    while (node) {
        if (HashEngine::isEqual(node->suffix, suffix))
            break;

        prev = node;
        node = node->next;
    }

    if (node && prev || node == head)
        node->remove(num);

}