#include <iostream>
template <typename T>
SingleNode<T>::SingleNode(const T &val) : value(val), next(nullptr) {}

template <typename T>
SingleNode<T>::SingleNode(T &&val) : value(val), next(nullptr) {}

template <typename T>
SingleList<T>::SingleList() : head(nullptr), listSize(0) {}

template <typename T>
SingleList<T>::SingleList(SingleList &&other) noexcept : head(std::move(other.head)),
                                                         listSize(other.listSize)
{
    other.head = nullptr;
    other.listSize = 0;
}

template <typename T>
SingleList<T> &SingleList<T>::operator=(SingleList &&other) noexcept
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

template <typename T>
SingleList<T>::~SingleList()
{
}

template <typename T>
void SingleList<T>::push_back(T &val)
{
    auto newSingleNode = std::make_unique<SingleNode<T>>(val);

    if (head == nullptr)
    {
        head = std::move(newSingleNode);
    }
    else
    {
        SingleNode<T> *current = head.get();
        while (current->next != nullptr)
        {
            current = current->next.get();
        }
        current->next = std::move(newSingleNode);
    }

    listSize++;
}

template <typename T>
void SingleList<T>::push_back(T &&val)
{
    auto newSingleNode = std::make_unique<SingleNode<T>>(std::move(val));

    if (head == nullptr)
    {
        head = std::move(newSingleNode);
    }
    else
    {
        SingleNode<T> *current = head.get();
        while (current->next != nullptr)
        {
            current = current->next.get();
        }
        current->next = std::move(newSingleNode);
    }

    listSize++;
}

template <typename T>
void SingleList<T>::insert(int index, T &val)
{
    if (index < 0 || index > listSize)
        throw std::out_of_range("Index out of range");

    auto newSingleNode = std::make_unique<SingleNode<T>>(val);

    if (index == 0)
    {
        newSingleNode->next = std::move(head);
        head = std::move(newSingleNode);
    }
    else
    {
        SingleNode<T> *current = head.get();
        for (int i = 0; i < index - 1; ++i)
            current = current->next.get();

        newSingleNode->next = std::move(current->next);
        current->next = std::move(newSingleNode);
    }

    listSize++;
}

template <typename T>
void SingleList<T>::insert(int index, T &&val)
{
    if (index < 0 || index > listSize)
        throw std::out_of_range("Index out of range");

    auto newSingleNode = std::make_unique<SingleNode<T>>(std::move(val));

    if (index == 0)
    {
        newSingleNode->next = std::move(head);
        head = std::move(newSingleNode);
    }
    else
    {
        SingleNode<T> *current = head.get();
        for (int i = 0; i < index - 1; ++i)
            current = current->next.get();

        newSingleNode->next = std::move(current->next);
        current->next = std::move(newSingleNode);
    }

    listSize++;
}

template <typename T>
void SingleList<T>::erase(int index)
{
    if (index < 0 || index >= listSize)
        throw std::out_of_range("Index out of range");

    if (index == 0)
    {
        head = std::move(head->next);
    }
    else
    {
        SingleNode<T> *current = head.get();
        for (int i = 0; i < index - 1; ++i)
            current = current->next.get();

        std::unique_ptr<SingleNode<T>> to_delete = std::move(current->next);
        current->next = std::move(to_delete->next);
    }

    listSize--;
}

template <typename T>
int SingleList<T>::size() const
{
    return listSize;
}

template <typename T>
T &SingleList<T>::operator[](int index)
{
    if (index < 0 || index >= listSize)
        throw std::out_of_range("Index out of range");

    SingleNode<T> *current = head.get();
    for (int i = 0; i < index; ++i)
        current = current->next.get();

    return current->value;
}

template <typename T>
void SingleList<T>::print() const
{
    SingleNode<T> *current = head.get();
    while (current != nullptr)
    {
        std::cout << current->value << " ";
        current = current->next.get();
    }
    std::cout << std::endl;
}

template <typename T>
SingleListIterator<T> SingleList<T>::begin() { return SingleListIterator<T>(head.get()); }

template <typename T>
SingleListIterator<T> SingleList<T>::end() { return SingleListIterator<T>(nullptr); }

template <typename T>
SingleListIterator<T>::SingleListIterator(SingleNode<T> *node) : current(node) {}

template <typename T>
T &SingleListIterator<T>::operator*() { return current->value; }

template <typename T>
SingleListIterator<T> &SingleListIterator<T>::operator++()
{
    current = current->next.get();
    return *this;
}

template <typename T>
bool SingleListIterator<T>::operator!=(const SingleListIterator &other) const
{
    return current != other.current;
}

template <typename T>
T &SingleListIterator<T>::get()
{
    return current->value;
}