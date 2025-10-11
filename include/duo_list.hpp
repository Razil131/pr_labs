#pragma once
#include <memory>

template <typename T>
class DuoNode
{
public:
    T value;
    std::unique_ptr<DuoNode<T>> next;
    DuoNode<T> *prev;

    DuoNode(const T &val);
    DuoNode(T &&val);
};

template <typename T>
class DuoListIterator
{
    DuoNode<T> *current;

public:
    DuoListIterator(DuoNode<T> *node);
    T &operator*();
    DuoListIterator<T> &operator++();
    DuoListIterator<T> &operator--();
    bool operator!=(const DuoListIterator &other) const;
    T &get();
};

template <typename T>
class DuoList
{
private:
    std::unique_ptr<DuoNode<T>> head;
    int listSize;

public:
    DuoList();
    DuoList(DuoList &&other) noexcept;
    DuoList &operator=(DuoList &&other) noexcept;

    ~DuoList();

    void push_back(const T &val);

    void push_back(T &&val);

    void insert(int index, const T &val);

    void insert(int index, T &&val);

    void erase(int index);

    int size() const;

    T &operator[](int index);

    void print() const;

    DuoListIterator<T> begin();

    DuoListIterator<T> end();
};

#include "../src/duo_list.tpp"