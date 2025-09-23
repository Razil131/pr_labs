#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <tuple>

using ip_t = std::tuple<int, int, int, int>;

void printip(const ip_t &ip)
{
    std::cout << std::get<0>(ip) << '.'
              << std::get<1>(ip) << '.'
              << std::get<2>(ip) << '.'
              << std::get<3>(ip) << std::endl;
}

ip_t parse_line(const std::string &line_raw)
{
    std::string line = line_raw.substr(0, line_raw.find('\t'));

    int n1 = std::stoi(line.substr(0, line.find('.')));
    line = line.substr(line.find('.') + 1);

    int n2 = std::stoi(line.substr(0, line.find('.')));
    line = line.substr(line.find('.') + 1);

    int n3 = std::stoi(line.substr(0, line.find('.')));
    line = line.substr(line.find('.') + 1);

    int n4 = std::stoi(line);

    return std::make_tuple(n1, n2, n3, n4);
}

std::vector<ip_t> read_ips(const std::string &filename)
{
    std::ifstream file(filename);
    std::vector<ip_t> ips;
    std::string line;

    while (std::getline(file, line))
    {
        ips.push_back(parse_line(line));
    }

    return ips;
}

void sort_ips(std::vector<ip_t> &ips)
{
    std::sort(ips.begin(), ips.end(), [](const ip_t &a, const ip_t &b)
              { return a > b; });
}

void print_ips(const std::vector<ip_t> &ips)
{
    for (const auto &ip : ips)
        printip(ip);
}