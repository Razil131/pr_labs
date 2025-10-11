#include <iostream>

template <typename T>
DuoNode<T>::DuoNode(const T &val) : value(val), next(nullptr), prev(nullptr) {}

template <typename T>
DuoNode<T>::DuoNode(T &&val) : value(val), next(nullptr), prev(nullptr) {}

template <typename T>
DuoList<T>::DuoList() : head(nullptr), listSize(0) {}

template <typename T>
DuoList<T>::DuoList(DuoList &&other) noexcept : head(std::move(other.head)),
                                                listSize(other.listSize)
{
    other.head = nullptr;
    other.listSize = 0;
}

template <typename T>
DuoList<T> &DuoList<T>::operator=(DuoList &&other) noexcept
{
    if (this != &other)
    {
        head = std::move(other.head);
        listSize = other.listSize;
        other.listSize = 0;
    }
    return *this;
}

template <typename T>
DuoList<T>::~DuoList() {}

template <typename T>
void DuoList<T>::push_back(const T &val)
{
    auto newDuoNode = std::make_unique<DuoNode<T>>(val);

    if (head == nullptr)
    {
        head = std::move(newDuoNode);
    }
    else
    {
        DuoNode<T> *current = head.get();
        while (current->next != nullptr)
        {
            current = current->next.get();
        }
        newDuoNode->prev = current;
        current->next = std::move(newDuoNode);
    }

    listSize++;
}

template <typename T>
void DuoList<T>::push_back(T &&val)
{
    auto newDuoNode = std::make_unique<DuoNode<T>>(std::move(val));

    if (head == nullptr)
    {
        head = std::move(newDuoNode);
    }
    else
    {
        DuoNode<T> *current = head.get();
        while (current->next != nullptr)
        {
            current = current->next.get();
        }
        newDuoNode->prev = current;
        current->next = std::move(newDuoNode);
    }

    listSize++;
}

template <typename T>
void DuoList<T>::insert(int index, const T &val)
{
    if (index < 0 || index > listSize)
        throw std::out_of_range("Index out of range");

    auto newNode = std::make_unique<DuoNode<T>>(val);

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
        DuoNode<T> *current = head.get();
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

template <typename T>
void DuoList<T>::insert(int index, T &&val)
{
    if (index < 0 || index > listSize)
        throw std::out_of_range("Index out of range");

    auto newNode = std::make_unique<DuoNode<T>>(std::move(val));

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
        DuoNode<T> *current = head.get();
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

template <typename T>
void DuoList<T>::erase(int index)
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
        DuoNode<T> *current = head.get();
        for (int i = 0; i < index - 1; ++i)
            current = current->next.get();

        auto to_delete = std::move(current->next);
        current->next = std::move(to_delete->next);
        if (to_delete->next != nullptr)
            to_delete->next->prev = current;
    }

    listSize--;
}

template <typename T>
int DuoList<T>::size() const
{
    return listSize;
}

template <typename T>
T &DuoList<T>::operator[](int index)
{
    if (index < 0 || index >= listSize)
        throw std::out_of_range("Index out of range");

    DuoNode<T> *current = head.get();
    for (int i = 0; i < index; ++i)
        current = current->next.get();

    return current->value;
}

template <typename T>
void DuoList<T>::print() const
{
    DuoNode<T> *current = head.get();
    while (current != nullptr)
    {
        std::cout << current->value << " ";
        current = current->next.get();
    }
    std::cout << std::endl;
}

template <typename T>
DuoListIterator<T> DuoList<T>::begin() { return DuoListIterator<T>(head.get()); }

template <typename T>
DuoListIterator<T> DuoList<T>::end() { return DuoListIterator<T>(nullptr); }

template <typename T>
DuoListIterator<T>::DuoListIterator(DuoNode<T> *node) : current(node) {}

template <typename T>
T &DuoListIterator<T>::operator*() { return current->value; }

template <typename T>
DuoListIterator<T> &DuoListIterator<T>::operator++()
{
    current = current->next.get();
    return *this;
}

template <typename T>
DuoListIterator<T> &DuoListIterator<T>::operator--()
{
    current = current->prev;
    return *this;
}

template <typename T>
bool DuoListIterator<T>::operator!=(const DuoListIterator<T> &other) const
{
    return current != other.current;
}

template <typename T>
T &DuoListIterator<T>::get()
{
    return current->value;
}