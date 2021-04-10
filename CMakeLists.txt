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

# week5
add_executable(http_get http_get.cpp)
target_link_libraries(http_get ws2_32 wsock32)

# week5 hw
add_executable(hw3 hw3.cpp)
target_link_libraries(hw3 ws2_32 wsock32)

# week6 echo client
add_executable(echo_client echo_client.cpp)
target_link_libraries(echo_client ws2_32 wsock32)

# week6 echo server
add_executable(echo_server echo_server.cpp)
target_link_libraries(echo_server ws2_32 wsock32)

# week6 guest number
add_executable(guest_number_client guest_number_client.cpp)
target_link_libraries(guest_number_client ws2_32 wsock32)

add_executable(guest_number_server guest_number_server.cpp)
target_link_libraries(guest_number_server ws2_32 wsock32)

# clock
add_executable(clock clock.cpp)