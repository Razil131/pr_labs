template <typename T, typename Allocator>
void SingleList<T, Allocator>::destroy_all()
{
    while (head)
    {
        Node *next = head->next;
        NodeTraits::destroy(alloc, head);
        NodeTraits::deallocate(alloc, head, 1);
        head = next;
    }
}

template <typename T, typename Allocator>
SingleList<T, Allocator>::SingleList(const Allocator &alloc)
    : alloc(alloc), head(nullptr), listsize(0)
{
}

template <typename T, typename Allocator>
SingleList<T, Allocator>::~SingleList()
{
    destroy_all();
}

template <typename T, typename Allocator>
void SingleList<T, Allocator>::push_back(const T &value)
{
    Node *new_node = NodeTraits::allocate(alloc, 1);
    NodeTraits::construct(alloc, new_node, value);
    new_node->next = nullptr;

    if (!head)
    {
        head = new_node;
    }
    else
    {
        Node *curr = head;
        while (curr->next)
            curr = curr->next;
        curr->next = new_node;
    }
    ++listsize;
}