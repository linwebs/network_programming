cmake_minimum_required(VERSION 3.17)
project(network_programming)

set(CMAKE_CXX_STANDARD 17)

# Week3
add_executable(week3 dns_search.cpp)
target_link_libraries(week3 ws2_32 wsock32)

add_executable(hw1 hw1.cpp)
target_link_libraries(hw1 ws2_32 wsock32)