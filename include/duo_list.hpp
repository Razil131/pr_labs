#pragma once
#include <memory>

class DuoNode
{
public:
    int value;
    std::unique_ptr<DuoNode> next;
    DuoNode *prev;

    DuoNode(int val);
};

class DuoListIterator
{
    DuoNode *current;

public:
    DuoListIterator(DuoNode *node);
    int &operator*();
    DuoListIterator &operator++();
    DuoListIterator &operator--();
    bool operator!=(const DuoListIterator &other) const;
    int &get();
};

class DuoList
{
private:
    std::unique_ptr<DuoNode> head;
    int listSize;

public:
    DuoList();
    DuoList(DuoList &&other) noexcept;
    DuoList &operator=(DuoList &&other) noexcept;

    ~DuoList();

    void push_back(int val);

    void insert(int index, int val);

    void erase(int index);

    int size() const;

    int &operator[](int index);

    void print() const;

    DuoListIterator begin();

    DuoListIterator end();
};
