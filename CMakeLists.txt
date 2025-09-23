cmake_minimum_required(VERSION 3.10)
project(lab2 VERSION 0.1.0 LANGUAGES CXX)

find_package(Boost REQUIRED COMPONENTS unit_test_framework)

add_executable(main main.cpp ip_filter.cpp)
set_target_properties(main PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

add_executable(testing ip_filter.cpp test.cpp)
set_target_properties(testing PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
)

target_include_directories(testing PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(testing PRIVATE ${Boost_LIBRARIES})

if (MSVC)
    target_compile_options(main PRIVATE /W4)
    target_compile_options(testing PRIVATE /W4)
else()
    target_compile_options(main PRIVATE -Wall -Wextra -pedantic -Werror)
    target_compile_options(testing PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

enable_testing()
add_test(NAME testing COMMAND testing)
