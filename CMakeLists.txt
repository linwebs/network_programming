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

# week6 guest number client
add_executable(guest_number_client guest_number_client.cpp)
target_link_libraries(guest_number_client ws2_32 wsock32)

# week6 guest number server
add_executable(guest_number_server guest_number_server.cpp)
target_link_libraries(guest_number_server ws2_32 wsock32)

# week8 chat client v1
add_executable(chat_client_v1 chat_client_v1.cpp)
target_link_libraries(chat_client_v1 ws2_32 wsock32)

# week8 chat server v1
add_executable(chat_server_v1 chat_server_v1.cpp)
target_link_libraries(chat_server_v1 ws2_32 wsock32)

# week8 chat client 1 v2
add_executable(chat_client1_v2 chat_client1_v2.cpp)
target_link_libraries(chat_client1_v2 ws2_32 wsock32)

# week8 chat client 2 v2
add_executable(chat_client2_v2 chat_client2_v2.cpp)
target_link_libraries(chat_client2_v2 ws2_32 wsock32)

# week8 chat server v2
add_executable(chat_server_v2 chat_server_v2.cpp)
target_link_libraries(chat_server_v2 ws2_32 wsock32)

# week8 chat client send v3
add_executable(chat_client_send_v3 chat_client_send_v3.cpp)
target_link_libraries(chat_client_send_v3 ws2_32 wsock32)

# week8 chat client recv v3
add_executable(chat_client_recv_v3 chat_client_recv_v3.cpp)
target_link_libraries(chat_client_recv_v3 ws2_32 wsock32)

# week8 chat server v3
add_executable(chat_server_v3 chat_server_v3.cpp)
target_link_libraries(chat_server_v3 ws2_32 wsock32)

# week9 mid 1 server
add_executable(mid_1_server mid_1_server.cpp)
target_link_libraries(mid_1_server ws2_32 wsock32)

# week9 mid 1 client
add_executable(mid_1_client mid_1_client.cpp)
target_link_libraries(mid_1_client ws2_32 wsock32)

# week9 mid 2 server
add_executable(mid_2_server mid_2_server.cpp)
target_link_libraries(mid_2_server ws2_32 wsock32)

# week9 mid 2 client1
add_executable(mid_2_client1 mid_2_client1.cpp)
target_link_libraries(mid_2_client1 ws2_32 wsock32)

# week9 mid 2 client2
add_executable(mid_2_client2 mid_2_client2.cpp)
target_link_libraries(mid_2_client2 ws2_32 wsock32)

# clock
add_executable(clock clock.cpp)