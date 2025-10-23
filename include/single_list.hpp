#pragma once
#include <memory>
#include <cstddef>

template <typename T>
struct SingleNode
{
    T value;
    SingleNode *next;

    template <typename... Args>
    SingleNode(Args &&...args) // perfect forwarding
        : value(std::forward<Args>(args)...), next(nullptr)
    {
    }
};

template <typename T>
class SingleListIterator
{
    SingleNode<T> *current;

public:
    SingleListIterator(SingleNode<T> *node) : current(node) {}

    T &operator*() const { return current->value; }

    SingleListIterator &operator++()
    {
        current = current->next;
        return *this;
    }

    bool operator!=(const SingleListIterator &other) const
    {
        return current != other.current;
    }
};

template <typename T, typename Allocator = std::allocator<T>>
class SingleList
{
    using Node = SingleNode<T>;
    using NodeAlloc = typename std::allocator_traits<Allocator>::template rebind_alloc<Node>;
    using NodeTraits = std::allocator_traits<NodeAlloc>;

    NodeAlloc alloc;
    Node *head = nullptr;
    std::size_t listsize = 0;

    void destroy_all();

public:
    // using value_type = T;
    // using allocator_type = Allocator;
    using size_type = std::size_t;
    using iterator = SingleListIterator<T>;

    explicit SingleList(const Allocator &alloc = Allocator());
    ~SingleList();

    // ЗАПРЕЩАЕМ копирование и перемещение
    SingleList(const SingleList &) = delete;
    SingleList &operator=(const SingleList &) = delete;

    void push_back(const T &value);

    size_type size() const { return listsize; }
    bool empty() const { return listsize == 0; }

    iterator begin() { return iterator(head); }
    iterator end() { return iterator(nullptr); }
};

#include "../src/single_list.tpp"