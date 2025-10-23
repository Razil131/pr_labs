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
    std::map<int, int> stdMap1;

    for (int i = 0; i < 10; ++i)
    {
        stdMap1[i] = static_cast<int>(factorial(i));
    }

    using MapAllocator = MyPoolAllocator<std::pair<const int, int>, 10>;
    std::map<int, int, std::less<int>, MapAllocator> stdMap2{MapAllocator{}};

    for (int i = 0; i < 10; ++i)
    {
        stdMap2[i] = static_cast<int>(factorial(i));
    }

    std::cout << "std::map with custom allocator:\n";
    for (const auto &kv : stdMap2)
    {
        std::cout << kv.first << " " << kv.second << "\n";
    }

    SingleList<int> myList1;

    for (int i = 0; i < 10; ++i)
    {
        myList1.push_back(i);
    }

    using ListAllocator = MyPoolAllocator<int, 10>;
    SingleList<int, ListAllocator> myList2{ListAllocator{}};

    for (int i = 0; i < 10; ++i)
    {
        myList2.push_back(i);
    }

    std::cout << "SingleList with custom allocator:\n";
    for (auto it = myList2.begin(); it != myList2.end(); ++it)
    {
        std::cout << *it << "\n";
    }

    return 0;
}
