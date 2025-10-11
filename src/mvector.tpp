#include <iostream>

template <typename T>
mVector<T>::mVector(int capacity) : arr(std::make_unique<T[]>(capacity)),
                                    arr_size(0),
                                    capacity(capacity) {}
template <typename T>
mVector<T>::mVector(mVector &&other) noexcept : arr(std::move(other.arr)),
                                                arr_size(other.arr_size),
                                                capacity(other.capacity)
{
    other.arr = nullptr;
    other.arr_size = 0;
    other.capacity = 0;
}

template <typename T>
mVector<T>::~mVector() {}

template <typename T>
mVector<T> &mVector<T>::operator=(mVector &&other) noexcept
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

template <typename T>
void mVector<T>::push_back(T &val)
{
    if (arr_size < capacity)
    {
        arr[arr_size] = val;
        arr_size++;
    }
    else
    {
        auto new_arr = std::make_unique<T[]>(capacity * 2);
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

template <typename T>
void mVector<T>::push_back(T &&val)
{
    if (arr_size < capacity)
    {
        arr[arr_size] = std::move(val);
        arr_size++;
    }
    else
    {
        auto new_arr = std::make_unique<T[]>(capacity * 2);
        for (int i = 0; i < arr_size; i++)
        {
            new_arr[i] = arr[i];
        }
        new_arr[arr_size] = std::move(val);
        arr = std::move(new_arr);
        capacity *= 2;
        arr_size++;
    }
}

template <typename T>
void mVector<T>::insert(int index, T &val)
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
        auto new_arr = std::make_unique<T[]>(capacity * 2);
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

template <typename T>
void mVector<T>::insert(int index, T &&val)
{
    if (index < 0 || index > arr_size)
        throw std::out_of_range("Index out of range");
    if (arr_size < capacity)
    {
        for (int i = arr_size; i > index; i--)
        {
            arr[i] = arr[i - 1];
        }
        arr[index] = std::move(val);
        arr_size++;
    }
    else
    {
        auto new_arr = std::make_unique<T[]>(capacity * 2);
        for (int i = 0; i < index; i++)
        {
            new_arr[i] = arr[i];
        }
        new_arr[index] = std::move(val);
        for (int i = index; i < arr_size; i++)
        {
            new_arr[i + 1] = arr[i];
        }
        arr = std::move(new_arr);
        capacity *= 2;
        arr_size++;
    }
}

template <typename T>
void mVector<T>::erase(int index)
{
    if (index < 0 || index >= arr_size)
        throw std::out_of_range("Index out of range");
    for (int i = index; i < arr_size - 1; i++)
        arr[i] = arr[i + 1];
    arr_size--;
}

template <typename T>
int mVector<T>::size() const
{
    return arr_size;
}

template <typename T>
int &mVector<T>::operator[](int index)
{
    if (index >= 0 && index < arr_size)
    {
        return arr[index];
    }
    throw std::out_of_range("Index out of range");
}

template <typename T>
void mVector<T>::print() const
{
    for (int i = 0; i < arr_size; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

template <typename T>
mVectorIterator<T> mVector<T>::begin() { return mVectorIterator<T>(arr.get()); }

template <typename T>
mVectorIterator<T> mVector<T>::end() { return mVectorIterator<T>(arr.get() + arr_size); }

template <typename T>
mVectorIterator<T>::mVectorIterator(T *ptr) : ptr(ptr) {}

template <typename T>
T &mVectorIterator<T>::operator*() { return *ptr; }

template <typename T>
mVectorIterator<T> &mVectorIterator<T>::operator++()
{
    ptr++;
    return *this;
}

template <typename T>
mVectorIterator<T> &mVectorIterator<T>::operator--()
{
    ptr--;
    return *this;
}

template <typename T>
bool mVectorIterator<T>::operator!=(const mVectorIterator<T> &other) const
{
    return ptr != other.ptr;
}

template <typename T>
T &mVectorIterator<T>::get()
{
    return *ptr;
}