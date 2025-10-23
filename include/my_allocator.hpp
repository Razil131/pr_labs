#pragma once
#include <cstddef>
#include <vector>
#include <limits>
#include <new>
#include <type_traits>

template <typename T, std::size_t BlockSize = 32>
class MyPoolAllocator
{
public:
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using propagate_on_container_copy_assignment = std::false_type;
    using propagate_on_container_move_assignment = std::false_type;
    using propagate_on_container_swap = std::false_type;
    using is_always_equal = std::false_type;

    template <typename U>
    struct rebind
    {
        using other = MyPoolAllocator<U, BlockSize>;
    };

    MyPoolAllocator() = default;

    template <typename U>
    MyPoolAllocator(const MyPoolAllocator<U, BlockSize> &) noexcept {}

    T *allocate(std::size_t n);
    void deallocate(T *ptr, std::size_t n) noexcept;

    size_type max_size() const noexcept
    {
        return std::numeric_limits<size_type>::max() / sizeof(T);
    }

    template <typename U, std::size_t BS>
    friend bool operator==(const MyPoolAllocator &a, const MyPoolAllocator<U, BS> &b) noexcept
    {
        return std::is_same_v<T, U> && BlockSize == BS;
    }

    template <typename U, std::size_t BS>
    friend bool operator!=(const MyPoolAllocator &a, const MyPoolAllocator<U, BS> &b) noexcept
    {
        return !(a == b);
    }

private:
    struct Block
    {
        std::byte *data;
        std::size_t capacity;
        std::size_t used;

        explicit Block(std::size_t bytes)
            : capacity(bytes), used(0)
        {
            data = static_cast<std::byte *>(::operator new(capacity));
        }

        ~Block()
        {
            ::operator delete(data);
        }

        Block(const Block &) = delete;
        Block &operator=(const Block &) = delete;

        Block(Block &&other) noexcept
            : data(other.data), capacity(other.capacity), used(other.used)
        {
            other.data = nullptr;
            other.capacity = 0;
            other.used = 0;
        }

        Block &operator=(Block &&other) noexcept
        {
            if (this != &other)
            {
                ::operator delete(data);
                data = other.data;
                capacity = other.capacity;
                used = other.used;
                other.data = nullptr;
                other.capacity = 0;
                other.used = 0;
            }
            return *this;
        }
    };

    static std::vector<Block> &blocks()
    {
        static std::vector<Block> instance;
        return instance;
    }

    static std::vector<std::byte *> &free_list()
    {
        static std::vector<std::byte *> instance;
        return instance;
    }
};

#include "../src/my_allocator.tpp"