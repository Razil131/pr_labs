#include "../include/single_list.hpp"
#include <iostream>

SingleNode::SingleNode(int val) : value(val), next(nullptr) {}

SingleList::SingleList() : head(nullptr), listSize(0) {}

SingleList::SingleList(SingleList &&other) noexcept : head(std::move(other.head)),
                                                      listSize(other.listSize)
{
    other.head = nullptr;
    other.listSize = 0;
}

SingleList &SingleList::operator=(SingleList &&other) noexcept
{
    if (this != &other)
    {
        head = std::move(other.head);
        listSize = other.listSize;
        other.head = nullptr;
        other.listSize = 0;
    }
    return *this;
}

SingleList::~SingleList()
{
}

void SingleList::push_back(int val)
{
    auto newSingleNode = std::make_unique<SingleNode>(val);

    if (head == nullptr)
    {
        head = std::move(newSingleNode);
    }
    else
    {
        SingleNode *current = head.get();
        while (current->next != nullptr)
        {
            current = current->next.get();
        }
        current->next = std::move(newSingleNode);
    }

    listSize++;
}

void SingleList::insert(int index, int val)
{
    if (index < 0 || index > listSize)
        throw std::out_of_range("Index out of range");

    auto newSingleNode = std::make_unique<SingleNode>(val);

    if (index == 0)
    {
        newSingleNode->next = std::move(head);
        head = std::move(newSingleNode);
    }
    else
    {
        SingleNode *current = head.get();
        for (int i = 0; i < index - 1; ++i)
            current = current->next.get();

        newSingleNode->next = std::move(current->next);
        current->next = std::move(newSingleNode);
    }

    listSize++;
}

void SingleList::erase(int index)
{
    if (index < 0 || index >= listSize)
        throw std::out_of_range("Index out of range");

    if (index == 0)
    {
        head = std::move(head->next);
    }
    else
    {
        SingleNode *current = head.get();
        for (int i = 0; i < index - 1; ++i)
            current = current->next.get();

        std::unique_ptr<SingleNode> to_delete = std::move(current->next);
        current->next = std::move(to_delete->next);
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

    SingleNode *current = head.get();
    for (int i = 0; i < index; ++i)
        current = current->next.get();

    return current->value;
}

void SingleList::print() const
{
    SingleNode *current = head.get();
    while (current != nullptr)
    {
        std::cout << current->value << " ";
        current = current->next.get();
    }
    std::cout << std::endl;
}

SingleListIterator SingleList::begin() { return SingleListIterator(head.get()); }

SingleListIterator SingleList::end() { return SingleListIterator(nullptr); }

SingleListIterator::SingleListIterator(SingleNode *node) : current(node) {}

int &SingleListIterator::operator*() { return current->value; }

SingleListIterator &SingleListIterator::operator++()
{
    current = current->next.get();
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