#include "../include/mvector.hpp"
#include <iostream>

mVector::mVector(int capacity) : arr(std::make_unique<int[]>(capacity)),
                                 arr_size(0),
                                 capacity(capacity) {}

mVector::mVector(mVector &&other) noexcept : arr(std::move(other.arr)),
                                             arr_size(other.arr_size),
                                             capacity(other.capacity)
{
    other.arr = nullptr;
    other.arr_size = 0;
    other.capacity = 0;
}

mVector &mVector::operator=(mVector &&other) noexcept
{
    if (this != &other)
    {
        arr = std::move(other.arr);
        arr_size = other.arr_size;
        capacity = other.capacity;
        other.arr = nullptr;
        other.arr_size = 0;
        other.capacity = 0;
    }
    return *this;
}

mVector::~mVector() {}

void mVector::push_back(int val)
{
    if (arr_size < capacity)
    {
        arr[arr_size] = val;
        arr_size++;
    }
    else
    {
        auto new_arr = std::make_unique<int[]>(capacity * 2);
        for (int i = 0; i < arr_size; i++)
        {
            new_arr[i] = arr[i];
        }
        new_arr[arr_size] = val;
        arr = std::move(new_arr);
        capacity *= 2;
        arr_size++;
    }
}

void mVector::insert(int index, int val)
{
    if (index < 0 || index > arr_size)
        throw std::out_of_range("Index out of range");
    if (arr_size < capacity)
    {
        for (int i = arr_size; i > index; i--)
        {
            arr[i] = arr[i - 1];
        }
        arr[index] = val;
        arr_size++;
    }
    else
    {
        auto new_arr = std::make_unique<int[]>(capacity * 2);
        for (int i = 0; i < index; i++)
        {
            new_arr[i] = arr[i];
        }
        new_arr[index] = val;
        for (int i = index; i < arr_size; i++)
        {
            new_arr[i + 1] = arr[i];
        }
        arr = std::move(new_arr);
        capacity *= 2;
        arr_size++;
    }
}

void mVector::erase(int index)
{
    if (index < 0 || index >= arr_size)
        throw std::out_of_range("Index out of range");
    for (int i = index; i < arr_size - 1; i++)
    {
        arr[i] = arr[i + 1];
    }
    arr_size--;
}

int mVector::size() const
{
    return arr_size;
}

int &mVector::operator[](int index)
{
    if (index >= 0 && index < arr_size)
    {
        return arr[index];
    }
    throw std::out_of_range("Index out of range");
}

void mVector::print() const
{
    for (int i = 0; i < arr_size; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

mVectorIterator mVector::begin() { return mVectorIterator(arr.get()); }

mVectorIterator mVector::end() { return mVectorIterator(arr.get() + arr_size); }

mVectorIterator::mVectorIterator(int *ptr) : ptr(ptr) {}

int &mVectorIterator::operator*() { return *ptr; }

mVectorIterator &mVectorIterator::operator++()
{
    ptr++;
    return *this;
}

mVectorIterator &mVectorIterator::operator--()
{
    ptr--;
    return *this;
}

bool mVectorIterator::operator!=(const mVectorIterator &other) const
{
    return ptr != other.ptr;
}

int &mVectorIterator::get()
{
    return *ptr;
}