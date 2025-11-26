cmake_minimum_required(VERSION 3.10.0)
project(bayan VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost REQUIRED COMPONENTS system filesystem program_options CONFIG)

if(Boost_FOUND)
    message(STATUS "Boost finded: ${Boost_VERSION}")
    message(STATUS "Boost include dirs: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost libraries: ${Boost_LIBRARIES}")
endif()

set(SOURCES
    main.cpp
    src/FileMatcher.cpp
    src/FileScanner.cpp
    src/FileGrouper.cpp
    src/Application.cpp
    src/CRC32Hash.cpp
    src/MD5Hash.cpp
    src/FileHasher.cpp
    src/DuplicateFinder.cpp
)

add_executable(bayan ${SOURCES})

target_include_directories(bayan PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${Boost_INCLUDE_DIRS}
)

target_link_libraries(bayan PRIVATE ${Boost_LIBRARIES})

