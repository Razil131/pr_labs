#pragma once

#include <tuple>
#include <vector>
#include <string>

using ip_t = std::tuple<int, int, int, int>;

void printip(const ip_t &ip);
ip_t parse_line(const std::string &line_raw);
std::vector<ip_t> read_ips(const std::string &filename);
void sort_ips(std::vector<ip_t> &ips);
void print_ips(const std::vector<ip_t> &ips);