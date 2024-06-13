cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

project(dsa-implementations)

add_executable(run_tests.out 
                    unit_tests.cpp
                    binary-search.cpp
                    trie.cpp
                    union-find.cpp
                    graph-algorithms.cpp
                    flow.cpp
                    string-search.cpp)