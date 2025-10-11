cmake_minimum_required(VERSION 3.10.0)
project(lab3 VERSION 0.1.0 LANGUAGES C CXX)

set(SOURCE_FILE
    main.cpp
    ./src/single_list.tpp
    ./src/duo_list.tpp
    ./src/mvector.tpp
    ./include/duo_list.hpp
    ./include/mvector.hpp
    ./include/single_list.hpp
    )

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(lab3 ${SOURCE_FILE})


