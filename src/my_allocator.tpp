template <typename T, std::size_t BlockSize>
T *MyPoolAllocator<T, BlockSize>::allocate(std::size_t n)
{
    if (n > max_size())
        throw std::bad_alloc{};

    const std::size_t bytes_needed = n * sizeof(T);

    if (n == 1 && !free_list().empty()) // если есть в free_list свободное место берем из него
    {
        T *ptr = reinterpret_cast<T *>(free_list().back());
        free_list().pop_back();
        return ptr;
    }

    for (auto &block : blocks()) // ищем подходящий блок
    {
        if (block.capacity - block.used >= bytes_needed)
        {
            T *result = reinterpret_cast<T *>(block.data + block.used);
            block.used += bytes_needed;
            return result;
        }
    }

    std::size_t new_block_size = std::max(BlockSize * sizeof(T), bytes_needed);
    blocks().emplace_back(new_block_size); // нету блока подходящего :(

    T *result = reinterpret_cast<T *>(blocks().back().data);
    blocks().back().used = bytes_needed;
    return result;
}

template <typename T, std::size_t BlockSize>
void MyPoolAllocator<T, BlockSize>::deallocate(T *ptr, std::size_t n) noexcept
{
    if (n == 1)
    {
        free_list().push_back(reinterpret_cast<std::byte *>(ptr));
    }
}