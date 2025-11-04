cmake_minimum_required(VERSION 3.10.0)
project(lab6 VERSION 0.1.0 LANGUAGES C CXX)

set(SOURCE_FILE
    main.cpp
    ./src/Controller.cpp
    ./src/Document.cpp
    ./src/DocumentIO.cpp
    )

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(lab6 ${SOURCE_FILE})

