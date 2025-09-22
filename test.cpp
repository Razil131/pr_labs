#define BOOST_TEST_MODULE test

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(test)

BOOST_AUTO_TEST_CASE(test_test)
{
    BOOST_CHECK(1 == 1);
}

BOOST_AUTO_TEST_SUITE_END()
