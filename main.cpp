#include "ip_filter.hpp"

int main()
{
    auto ips = read_ips("../ip_filter.tsv");

    sort_ips(ips);

    print_ips(ips);

    auto print_if = [&](auto pred)
    { for (const auto &ip : ips) if (pred(ip)) printip(ip); };

    print_if([](const ip_t &ip)
             { return std::get<0>(ip) == 1; });

    print_if([](const ip_t &ip)
             { return std::get<0>(ip) == 46 && std::get<1>(ip) == 70; });

    print_if([](const ip_t &ip)
             { return std::get<0>(ip) == 46 || std::get<1>(ip) == 46 ||
                      std::get<2>(ip) == 46 || std::get<3>(ip) == 46; });

    return 0;
}
