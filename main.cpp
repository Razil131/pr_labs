#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <tuple>

inline void printip(std::tuple<int, int, int, int> ip)
{
    std::cout << std::get<0>(ip) << '.' << std::get<1>(ip) << '.' << std::get<2>(ip) << '.' << std::get<3>(ip) << std::endl;
}

int main()
{
    std::ifstream file("../ip_filter.tsv");

    std::string line;
    std::tuple<int, int, int, int> ip;
    using ip_t = decltype(ip);
    auto ips = std::vector<ip_t>();
    while (std::getline(file, line))
    {
        line = line.substr(0, line.find('\t'));

        int n1 = std::stoi(line.substr(0, line.find('.')));
        line = line.substr(line.find('.') + 1);

        int n2 = std::stoi(line.substr(0, line.find('.')));
        line = line.substr(line.find('.') + 1);

        int n3 = std::stoi(line.substr(0, line.find('.')));
        line = line.substr(line.find('.') + 1);

        int n4 = std::stoi(line);

        ips.emplace_back(n1, n2, n3, n4);
    }

    file.close();
    std::sort(ips.begin(), ips.end(), [](ip_t a, ip_t b)
              { return a > b; });

    for (auto ip : ips)
        printip(ip);

    auto print_if = [&](auto pred)
    {
        for (const auto &ip : ips)
            if (pred(ip))
                printip(ip);
    };

    print_if([](const ip_t &ip)
             { return std::get<0>(ip) == 1; });

    print_if([](const ip_t &ip)
             { return std::get<0>(ip) == 46 && std::get<1>(ip) == 70; });

    print_if([](const ip_t &ip)
             { return std::get<0>(ip) == 46 || std::get<1>(ip) == 46 ||
                      std::get<2>(ip) == 46 || std::get<3>(ip) == 46; });

    return 0;
}
