#include <iostream>
#include "./include/mvector.hpp"
#include "./include/single_list.hpp"
#include "./include/duo_list.hpp"

void vec_test()
{
    mVector *vec = new mVector(1);
    for (int i = 0; i < 10; i++)
    {
        vec->push_back(i);
    }
    vec->print();
    vec->erase(2);
    vec->erase(3);
    vec->erase(4);
    vec->print();
    vec->insert(0, 10);
    vec->print();
    vec->insert(vec->size() / 2, 20);
    vec->print();
    vec->push_back(30);
    vec->print();
    delete vec;
}

void sl_test()
{
    SingleList *vec = new SingleList();
    for (int i = 0; i < 10; i++)
    {
        vec->push_back(i);
    }
    vec->print();
    vec->erase(2);
    vec->erase(3);
    vec->erase(4);
    vec->print();
    vec->insert(0, 10);
    vec->print();
    vec->insert(vec->size() / 2, 20);
    vec->print();
    vec->push_back(30);
    vec->print();
    delete vec;
}

void dl_test()
{
    DuoList *vec = new DuoList();
    for (int i = 0; i < 10; i++)
    {
        vec->push_back(i);
    }
    vec->print();
    vec->erase(2);
    vec->erase(3);
    vec->erase(4);
    vec->print();
    vec->insert(0, 10);
    vec->print();
    vec->insert(vec->size() / 2, 20);
    vec->print();
    vec->push_back(30);
    vec->print();
    delete vec;
}

int main(int, char **)
{
    std::cout << "Vector:" << std::endl;
    vec_test();
    std::cout << "SingleList:" << std::endl;
    sl_test();
    std::cout << "DuoList:" << std::endl;
    dl_test();
    return 0;
}
