#include "../include/single_list.hpp"
#include <iostream>

SingleNode::SingleNode(int val) : value(val), next(nullptr) {}

SingleList::SingleList() : head(nullptr), listSize(0) {}

SingleList::SingleList(SingleList &&other) noexcept : head(other.head),
                                                      listSize(other.listSize)
{
    other.head = nullptr;
    other.listSize = 0;
}

SingleList &SingleList::operator=(SingleList &&other) noexcept
{
    if (this != &other)
    {
        SingleNode *current = head;
        while (current != nullptr)
        {
            SingleNode *cur_next = current->next;
            delete current;
            current = cur_next;
        }
        head = other.head;
        listSize = other.listSize;
        other.head = nullptr;
        other.listSize = 0;
    }
    return *this;
}

SingleList::~SingleList()
{
    SingleNode *current = head;
    while (current != nullptr)
    {
        SingleNode *next = current->next;
        delete current;
        current = next;
    }
}

void SingleList::push_back(int val)
{
    SingleNode *newSingleNode = new SingleNode(val);

    if (head == nullptr)
    {
        head = newSingleNode;
    }
    else
    {
        SingleNode *current = head;
        while (current->next != nullptr)
        {
            current = current->next;
        }
        current->next = newSingleNode;
    }

    listSize++;
}

void SingleList::insert(int index, int val)
{
    if (index < 0 || index > listSize)
        throw std::out_of_range("Index out of range");

    SingleNode *newSingleNode = new SingleNode(val);

    if (index == 0)
    {
        newSingleNode->next = head;
        head = newSingleNode;
    }
    else
    {
        SingleNode *current = head;
        for (int i = 0; i < index - 1; ++i)
            current = current->next;

        newSingleNode->next = current->next;
        current->next = newSingleNode;
    }

    listSize++;
}

void SingleList::erase(int index)
{
    if (index < 0 || index >= listSize)
        throw std::out_of_range("Index out of range");

    if (index == 0)
    {
        SingleNode *to_delete = head;
        head = head->next;
        delete to_delete;
    }
    else
    {
        SingleNode *current = head;
        for (int i = 0; i < index - 1; ++i)
            current = current->next;

        SingleNode *to_delete = current->next;
        current->next = to_delete->next;
        delete to_delete;
    }

    listSize--;
}

int SingleList::size() const
{
    return listSize;
}

int &SingleList::operator[](int index)
{
    if (index < 0 || index >= listSize)
        throw std::out_of_range("Index out of range");

    SingleNode *current = head;
    for (int i = 0; i < index; ++i)
        current = current->next;

    return current->value;
}

void SingleList::print() const
{
    SingleNode *current = head;
    while (current != nullptr)
    {
        std::cout << current->value << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

SingleListIterator SingleList::begin() { return SingleListIterator(head); }

SingleListIterator SingleList::end() { return SingleListIterator(nullptr); }

SingleListIterator::SingleListIterator(SingleNode *node) : current(node) {}

int &SingleListIterator::operator*() { return current->value; }

SingleListIterator &SingleListIterator::operator++()
{
    current = current->next;
    return *this;
}

bool SingleListIterator::operator!=(const SingleListIterator &other) const
{
    return current != other.current;
}

int &SingleListIterator::get()
{
    return current->value;
}