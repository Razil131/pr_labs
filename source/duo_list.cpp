#include "../include/duo_list.hpp"
#include <iostream>

DuoNode::DuoNode(int val) : value(val), next(nullptr), prev(nullptr) {}

DuoList::DuoList() : head(nullptr), listSize(0) {}

DuoList::DuoList(DuoList &&other) noexcept : head(other.head),
                                             listSize(other.listSize)
{
    other.head = nullptr;
    other.listSize = 0;
}

DuoList &DuoList::operator=(DuoList &&other) noexcept
{
    if (this != &other)
    {
        DuoNode *current = head;
        while (current != nullptr)
        {
            DuoNode *cur_next = current->next;
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

DuoList::~DuoList()
{
    DuoNode *current = head;
    while (current != nullptr)
    {
        DuoNode *next = current->next;
        delete current;
        current = next;
    }
}

void DuoList::push_back(int val)
{
    DuoNode *newDuoNode = new DuoNode(val);

    if (head == nullptr)
    {
        head = newDuoNode;
    }
    else
    {
        DuoNode *current = head;
        while (current->next != nullptr)
        {
            current = current->next;
        }
        current->next = newDuoNode;
        newDuoNode->prev = current;
    }

    listSize++;
}

void DuoList::insert(int index, int val)
{
    if (index < 0 || index > listSize)
        throw std::out_of_range("Index out of range");

    DuoNode *newNode = new DuoNode(val);

    if (index == 0)
    {
        newNode->next = head;
        if (head != nullptr)
            head->prev = newNode;
        head = newNode;
    }
    else
    {
        DuoNode *current = head;
        for (int i = 0; i < index - 1; ++i)
            current = current->next;

        newNode->next = current->next;
        newNode->prev = current;

        if (current->next != nullptr)
            current->next->prev = newNode;

        current->next = newNode;
    }

    listSize++;
}

void DuoList::erase(int index)
{
    if (index < 0 || index >= listSize)
        throw std::out_of_range("Index out of range");

    if (index == 0)
    {
        DuoNode *to_delete = head;
        head = head->next;
        if (head != nullptr)
            head->prev = nullptr;
        delete to_delete;
    }
    else
    {
        DuoNode *current = head;
        for (int i = 0; i < index - 1; ++i)
            current = current->next;

        DuoNode *to_delete = current->next;
        current->next = to_delete->next;
        if (to_delete->next != nullptr)
            to_delete->next->prev = current;

        delete to_delete;
    }

    listSize--;
}

int DuoList::size() const
{
    return listSize;
}

int &DuoList::operator[](int index)
{
    if (index < 0 || index >= listSize)
        throw std::out_of_range("Index out of range");

    DuoNode *current = head;
    for (int i = 0; i < index; ++i)
        current = current->next;

    return current->value;
}

void DuoList::print() const
{
    DuoNode *current = head;
    while (current != nullptr)
    {
        std::cout << current->value << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

DuoListIterator DuoList::begin() { return DuoListIterator(head); }

DuoListIterator DuoList::end() { return DuoListIterator(nullptr); }

DuoListIterator::DuoListIterator(DuoNode *node) : current(node) {}

int &DuoListIterator::operator*() { return current->value; }

DuoListIterator &DuoListIterator::operator++()
{
    current = current->next;
    return *this;
}

DuoListIterator &DuoListIterator::operator--()
{
    current = current->prev;
    return *this;
}

bool DuoListIterator::operator!=(const DuoListIterator &other) const
{
    return current != other.current;
}

int &DuoListIterator::get()
{
    return current->value;
}