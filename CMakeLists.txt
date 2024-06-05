cmake_minimum_required(VERSION 3.10)

project(dsa-implementations)

add_executable(run_tests.out 
                    unit_tests.cpp
                    binary-search.cpp
                    trie.cpp
                    union-find.cpp
                    graph-algorithms.cpp
                    flow.cpp)