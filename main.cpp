#include "lib.h"

#include <iostream>

int main(int, char **)
{
    std::cout << "Version: 1.0." << version() << std::endl;
    std::cout << "Hello, world!" << std::endl;
    system("pause");
    return 0;
}
