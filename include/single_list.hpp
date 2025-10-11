#pragma once
#include <memory>

template <typename T>
class SingleNode
{
public:
    T value;
    std::unique_ptr<SingleNode> next;

    SingleNode(const T &val);
    SingleNode(T &&val);
};

template <typename T>
class SingleListIterator
{
    SingleNode<T> *current;

public:
    SingleListIterator(SingleNode<T> *node);
    T &operator*();
    SingleListIterator &operator++();
    bool operator!=(const SingleListIterator &other) const;
    T &get();
};

template <typename T>
class SingleList
{
private:
    std::unique_ptr<SingleNode<T>> head;
    int listSize;

public:
    SingleList();

    SingleList(SingleList &&other) noexcept;

    SingleList &operator=(SingleList &&other) noexcept;

    ~SingleList();

    void push_back(T &val);

    void push_back(T &&val);

    void insert(int index, T &val);

    void insert(int index, T &&val);

    void erase(int index);

    int size() const;

    T &operator[](int index);

    void print() const;

    SingleListIterator<T> begin();

    SingleListIterator<T> end();
};

#include "../src/single_list.tpp"