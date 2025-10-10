#include "../include/duo_list.hpp"
#include <iostream>

DuoNode::DuoNode(int val) : value(val), next(nullptr), prev(nullptr) {}

DuoList::DuoList() : head(nullptr), listSize(0) {}

DuoList::DuoList(DuoList &&other) noexcept : head(std::move(other.head)),
                                             listSize(other.listSize)
{
    other.head = nullptr;
    other.listSize = 0;
}

DuoList &DuoList::operator=(DuoList &&other) noexcept
{
    if (this != &other)
    {
        head = std::move(other.head);
        listSize = other.listSize;
        other.listSize = 0;
    }
    return *this;
}

DuoList::~DuoList() {}

void DuoList::push_back(int val)
{
    auto newDuoNode = std::make_unique<DuoNode>(val);

    if (head == nullptr)
    {
        head = std::move(newDuoNode);
    }
    else
    {
        DuoNode *current = head.get();
        while (current->next != nullptr)
        {
            current = current->next.get();
        }
        newDuoNode->prev = current;
        current->next = std::move(newDuoNode);
    }

    listSize++;
}

void DuoList::insert(int index, int val)
{
    if (index < 0 || index > listSize)
        throw std::out_of_range("Index out of range");

    auto newNode = std::make_unique<DuoNode>(val);

    if (index == 0)
    {
        if (head != nullptr)
        {
            head->prev = newNode.get();
            newNode->next = std::move(head);
        }
        head = std::move(newNode);
    }
    else
    {
        DuoNode *current = head.get();
        for (int i = 0; i < index - 1; ++i)
            current = current->next.get();

        newNode->next = std::move(current->next);
        newNode->prev = current;

        if (current->next != nullptr)
            current->next->prev = newNode.get();

        current->next = std::move(newNode);
    }

    listSize++;
}

void DuoList::erase(int index)
{
    if (index < 0 || index >= listSize)
        throw std::out_of_range("Index out of range");

    if (index == 0)
    {
        if (head->next)
            head->next->prev = nullptr;
        head = std::move(head->next);
    }
    else
    {
        DuoNode *current = head.get();
        for (int i = 0; i < index - 1; ++i)
            current = current->next.get();

        auto to_delete = std::move(current->next);
        current->next = std::move(to_delete->next);
        if (to_delete->next != nullptr)
            to_delete->next->prev = current;
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

    DuoNode *current = head.get();
    for (int i = 0; i < index; ++i)
        current = current->next.get();

    return current->value;
}

void DuoList::print() const
{
    DuoNode *current = head.get();
    while (current != nullptr)
    {
        std::cout << current->value << " ";
        current = current->next.get();
    }
    std::cout << std::endl;
}

DuoListIterator DuoList::begin() { return DuoListIterator(head.get()); }

DuoListIterator DuoList::end() { return DuoListIterator(nullptr); }

DuoListIterator::DuoListIterator(DuoNode *node) : current(node) {}

int &DuoListIterator::operator*() { return current->value; }

DuoListIterator &DuoListIterator::operator++()
{
    current = current->next.get();
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