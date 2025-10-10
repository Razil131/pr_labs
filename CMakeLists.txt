cmake_minimum_required(VERSION 3.10.0)
project(lab3 VERSION 0.1.0 LANGUAGES C CXX)

set(SOURCE_FILE
    main.cpp
    ./source/mvector.cpp
    ./source/single_list.cpp
    ./source/duo_list.cpp
    )

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(lab3 ${SOURCE_FILE})


