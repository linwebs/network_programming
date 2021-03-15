cmake_minimum_required(VERSION 3.17)
project(network_programming)

set(CMAKE_CXX_STANDARD 17)

# week3
add_executable(w3_dns_search dns_search.cpp)
target_link_libraries(w3_dns_search ws2_32 wsock32)

# week3 hw
add_executable(hw1 hw1.cpp)
target_link_libraries(hw1 ws2_32 wsock32)

# week3 example code
add_executable(w3_gethostbyaddr gethostbyaddr.cpp)
target_link_libraries(w3_gethostbyaddr ws2_32 wsock32)

# week4
add_executable(echo_service echo_service.cpp)
target_link_libraries(echo_service ws2_32 wsock32)

# week4 hw
add_executable(hw2 hw2.cpp)
target_link_libraries(hw2 ws2_32 wsock32)

# clock
add_executable(clock clock.cpp)