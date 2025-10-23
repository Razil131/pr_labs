cmake_minimum_required(VERSION 3.10.0)
project(lab4 VERSION 0.1.0 LANGUAGES C CXX)

set(SOURCE_FILE
    main.cpp
    ./src/single_list.tpp
    ./include/single_list.hpp
    ./src/my_allocator.tpp
    ./include/my_allocator.hpp
    )

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(lab4 main.cpp)

