#pragma once

class SingleNode
{
public:
    int value;
    SingleNode *next;

    SingleNode(int val);
};

class SingleListIterator
{
    SingleNode *current;

public:
    SingleListIterator(SingleNode *node);
    int &operator*();
    SingleListIterator &operator++();
    bool operator!=(const SingleListIterator &other) const;
    int &get();
};

class SingleList
{
private:
    SingleNode *head;
    int listSize;

public:
    SingleList();

    SingleList(SingleList &&other) noexcept;

    SingleList &operator=(SingleList &&other) noexcept;

    ~SingleList();

    void push_back(int val);

    void insert(int index, int val);

    void erase(int index);

    int size() const;

    int &operator[](int index);

    void print() const;

    SingleListIterator begin();

    SingleListIterator end();
};
