#pragma once

#include <memory>

template <typename T>
class mVectorIterator
{
    T *ptr;

public:
    mVectorIterator(T *ptr);
    T &operator*();
    mVectorIterator &operator++();
    mVectorIterator &operator--();
    bool operator!=(const mVectorIterator &other) const;
    T &get();
};

template <typename T>
class mVector
{
private:
    std::unique_ptr<T[]> arr;
    int arr_size;
    int capacity;

public:
    mVector(int capacity);
    mVector(mVector &&other) noexcept;
    mVector &operator=(mVector &&other) noexcept;

    ~mVector();

    void push_back(T &val);

    void push_back(T &&val);

    void insert(int index, T &val);

    void insert(int index, T &&val);

    void erase(int index);

    int size() const;

    int &operator[](int index);

    void print() const;

    mVectorIterator<T> begin();

    mVectorIterator<T> end();
};

#include "../src/mvector.tpp"
