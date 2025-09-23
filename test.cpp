#define BOOST_TEST_MODULE ip_filter_test
#include <boost/test/unit_test.hpp>
#include <vector>
#include <string>
#include <fstream>
#include "ip_filter.hpp"

BOOST_AUTO_TEST_SUITE(ip_filter)

BOOST_AUTO_TEST_CASE(test_parse_line)
{
    std::string line = "192.168.0.1\ttext2\ttext3";
    ip_t ip = parse_line(line);

    BOOST_CHECK_EQUAL(std::get<0>(ip), 192);
    BOOST_CHECK_EQUAL(std::get<1>(ip), 168);
    BOOST_CHECK_EQUAL(std::get<2>(ip), 0);
    BOOST_CHECK_EQUAL(std::get<3>(ip), 1);
}

BOOST_AUTO_TEST_CASE(test_sort_ips)
{
    std::vector<ip_t> ips = {
        {1, 1, 1, 1},
        {1, 10, 1, 1},
        {1, 2, 1, 1}};

    sort_ips(ips);

    BOOST_CHECK(ips[0] == ip_t(1, 10, 1, 1));
    BOOST_CHECK(ips[1] == ip_t(1, 2, 1, 1));
    BOOST_CHECK(ips[2] == ip_t(1, 1, 1, 1));
}

BOOST_AUTO_TEST_CASE(test_read_ips)
{
    const char *fname = "test_input.tsv";
    {
        std::ofstream ofs(fname);
        ofs << "10.20.30.40\tzzz\tvvv\n";
        ofs << "1.2.3.4\tooo\tyyy\n";
    }

    auto ips = read_ips(fname);
    std::remove(fname);

    BOOST_REQUIRE_EQUAL(ips.size(), 2);
    BOOST_CHECK(ips[0] == ip_t(10, 20, 30, 40));
    BOOST_CHECK(ips[1] == ip_t(1, 2, 3, 4));
}

BOOST_AUTO_TEST_SUITE_END()