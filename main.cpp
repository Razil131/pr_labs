#include <iostream>
#include <map>
#include "./include/my_allocator.hpp"
#include "./include/single_list.hpp"

long long factorial(int n)
{
    if (n <= 1)
        return 1;
    long long res = 1;
    for (int i = 2; i <= n; ++i)
    {
        res *= i;
    }
    return res;
}

int main()
{
    // 1) Создание экземпляра std::map<int, int>
    std::map<int, int> stdMap1;

    // 2) Заполнение 10 элементами: ключ = 0..9, значение = факториал(ключ)
    for (int i = 0; i < 10; ++i)
    {
        stdMap1[i] = static_cast<int>(factorial(i));
    }

    // 3) Создание экземпляра std::map<int, int> с новым аллокатором, ограниченным 10 элементами
    using MapAllocator = MyPoolAllocator<std::pair<const int, int>, 10>;
    std::map<int, int, std::less<int>, MapAllocator> stdMap2{MapAllocator{}};

    // 4) Заполнение 10 элементами: ключ = 0..9, значение = факториал(ключ)
    for (int i = 0; i < 10; ++i)
    {
        stdMap2[i] = static_cast<int>(factorial(i));
    }

    // 5) Вывод всех значений из stdMap2 (ключ и значение через пробел)
    std::cout << "std::map with custom allocator:\n";
    for (const auto &kv : stdMap2)
    {
        std::cout << kv.first << " " << kv.second << "\n";
    }

    // 6) Создание экземпляра своего контейнера для int
    SingleList<int> myList1;

    // 7) Заполнение 10 элементами от 0 до 9
    for (int i = 0; i < 10; ++i)
    {
        myList1.push_back(i);
    }

    // 8) Создание экземпляра своего контейнера с новым аллокатором, ограниченным 10 элементами
    using ListAllocator = MyPoolAllocator<int, 10>;
    SingleList<int, ListAllocator> myList2{ListAllocator{}};

    // 9) Заполнение 10 элементами от 0 до 9
    for (int i = 0; i < 10; ++i)
    {
        myList2.push_back(i);
    }

    // 10) Вывод всех значений из myList2
    std::cout << "SingleList with custom allocator:\n";
    for (auto it = myList2.begin(); it != myList2.end(); ++it)
    {
        std::cout << *it << "\n";
    }

    return 0;
}

// int main()
// {
//     MyPoolAllocator<int, 16> alloc;
//     SingleList<int, MyPoolAllocator<int, 16>> list(alloc);

//     for (int i = 0; i < 100; ++i)
//     {
//         list.push_back(i);
//     }

//     // Также можно использовать с STL:
//     std::vector<int, MyPoolAllocator<int, 16>> vec(alloc);
//     vec.push_back(42);
// }