#pragma once

class mVectorIterator
{
    int *ptr;

public:
    mVectorIterator(int *ptr);
    int &operator*();
    mVectorIterator &operator++();
    mVectorIterator &operator--();
    bool operator!=(const mVectorIterator &other) const;
    int &get();
};

class mVector
{
private:
    int *arr;
    int arr_size;
    int capacity;

public:
    mVector(int capacity);
    mVector(mVector &&other) noexcept;
    mVector &operator=(mVector &&other) noexcept;

    ~mVector();

    void push_back(int val);

    void insert(int index, int val);

    void erase(int index);

    int size() const;

    int &operator[](int index);

    void print() const;

    mVectorIterator begin();

    mVectorIterator end();
};