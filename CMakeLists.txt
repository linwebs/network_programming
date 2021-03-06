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

# week10 basic udp client
add_executable(basic_udp_client basic_udp_client.cpp)
target_link_libraries(basic_udp_client ws2_32 wsock32)

# week10 basic udp server
add_executable(basic_udp_server basic_udp_server.cpp)
target_link_libraries(basic_udp_server ws2_32 wsock32)

# week10 udp multiple server client
add_executable(udp_mult_server_client udp_mult_server_client.cpp)
target_link_libraries(udp_mult_server_client ws2_32 wsock32)

# week10 udp multiple server server 1
add_executable(udp_mult_server_server1 udp_mult_server_server1.cpp)
target_link_libraries(udp_mult_server_server1 ws2_32 wsock32)

# week10 udp multiple server server 2
add_executable(udp_mult_server_server2 udp_mult_server_server2.cpp)
target_link_libraries(udp_mult_server_server2 ws2_32 wsock32)

# week10 udp multiple client server
add_executable(udp_mult_client_server udp_mult_client_server.cpp)
target_link_libraries(udp_mult_client_server ws2_32 wsock32)

# week10 udp multiple client client 1
add_executable(udp_mult_client_client1 udp_mult_client_client1.cpp)
target_link_libraries(udp_mult_client_client1 ws2_32 wsock32)

# week10 udp multiple client client 2
add_executable(udp_mult_client_client2 udp_mult_client_client2.cpp)
target_link_libraries(udp_mult_client_client2 ws2_32 wsock32)

# week10 udp static client client
add_executable(udp_static_client_client udp_static_client_client.cpp)
target_link_libraries(udp_static_client_client ws2_32 wsock32)

# week10 udp static client client
add_executable(udp_client_static_port_client udp_client_static_port_client.cpp)
target_link_libraries(udp_client_static_port_client ws2_32 wsock32)

# week10 udp no care source server
add_executable(udp_no_care_source_server udp_no_care_source_server.cpp)
target_link_libraries(udp_no_care_source_server ws2_32 wsock32)

# week11 exercise 1 tcp send first client
add_executable(tcp_send_first_client tcp_send_first_client.cpp)
target_link_libraries(tcp_send_first_client ws2_32 wsock32)

# week11 exercise 1 tcp send first server
add_executable(tcp_send_first_server tcp_send_first_server.cpp)
target_link_libraries(tcp_send_first_server ws2_32 wsock32)

# week11 exercise 1 tcp recv first client
add_executable(tcp_recv_first_client tcp_recv_first_client.cpp)
target_link_libraries(tcp_recv_first_client ws2_32 wsock32)

# week11 exercise 1 tcp recv first server
add_executable(tcp_recv_first_server tcp_recv_first_server.cpp)
target_link_libraries(tcp_recv_first_server ws2_32 wsock32)

# week11 exercise 1 1 hw8 client
add_executable(hw8_exercise1_1_client hw8_exercise1_1_client.cpp)
target_link_libraries(hw8_exercise1_1_client ws2_32 wsock32)

# week11 exercise 1 1 hw8 server
add_executable(hw8_exercise1_1_server hw8_exercise1_1_server.cpp)
target_link_libraries(hw8_exercise1_1_server ws2_32 wsock32)

# week11 exercise 1 2 hw8 client
add_executable(hw8_exercise1_2_client hw8_exercise1_2_client.cpp)
target_link_libraries(hw8_exercise1_2_client ws2_32 wsock32)

# week11 exercise 1 2 hw8 server
add_executable(hw8_exercise1_2_server hw8_exercise1_2_server.cpp)
target_link_libraries(hw8_exercise1_2_server ws2_32 wsock32)

# week11 exercise 2 1 hw8 client
add_executable(hw8_exercise2_1_client hw8_exercise2_1_client.cpp)
target_link_libraries(hw8_exercise2_1_client ws2_32 wsock32)

# week11 exercise 2 1 hw8 server
add_executable(hw8_exercise2_1_server hw8_exercise2_1_server.cpp)
target_link_libraries(hw8_exercise2_1_server ws2_32 wsock32)

# week11 exercise 2 2 hw8 client
add_executable(hw8_exercise2_2_client hw8_exercise2_2_client.cpp)
target_link_libraries(hw8_exercise2_2_client ws2_32 wsock32)

# week11 exercise 2 2 hw8 server
add_executable(hw8_exercise2_2_server hw8_exercise2_2_server.cpp)
target_link_libraries(hw8_exercise2_2_server ws2_32 wsock32)

# week11 exercise 3 hw8 client
add_executable(hw8_exercise3_client hw8_exercise3_client.cpp)
target_link_libraries(hw8_exercise3_client ws2_32 wsock32)

# week11 exercise 3 hw8 server
add_executable(hw8_exercise3_server hw8_exercise3_server.cpp)
target_link_libraries(hw8_exercise3_server ws2_32 wsock32)

# week11 exercise 4 3 hw8 client
add_executable(hw8_exercise4_3_client hw8_exercise4_3_client.cpp)
target_link_libraries(hw8_exercise4_3_client ws2_32 wsock32)

# week11 exercise 4 3 hw8 server
add_executable(hw8_exercise4_3_server hw8_exercise4_3_server.cpp)
target_link_libraries(hw8_exercise4_3_server ws2_32 wsock32)

# week11 exercise 5 text read write
add_executable(text_read_write text_read_write.cpp)

# week11 exercise 5 send many text client
add_executable(send_many_text_client send_many_text_client.cpp)
target_link_libraries(send_many_text_client ws2_32 wsock32)

# week11 exercise 5 send many text server
add_executable(send_many_text_server send_many_text_server.cpp)
target_link_libraries(send_many_text_server ws2_32 wsock32)

# week11 exercise 6 binary read write
add_executable(binary_read_write binary_read_write.cpp)

# week11 exercise 6 send binary client
add_executable(send_binary_client send_binary_client.cpp)
target_link_libraries(send_binary_client ws2_32 wsock32)

# week11 exercise 6 send binary server
add_executable(send_binary_server send_binary_server.cpp)
target_link_libraries(send_binary_server ws2_32 wsock32)

# week11 exercise 7 udp send many text client
add_executable(udp_send_many_text_client udp_send_many_text_client.cpp)
target_link_libraries(udp_send_many_text_client ws2_32 wsock32)

# week11 exercise 7 udp send many text server
add_executable(udp_send_many_text_server udp_send_many_text_server.cpp)
target_link_libraries(udp_send_many_text_server ws2_32 wsock32)

# week11 exercise 7 udp send binary client
add_executable(udp_send_binary_client udp_send_binary_client.cpp)
target_link_libraries(udp_send_binary_client ws2_32 wsock32)

# week11 exercise 7 udp send binary server
add_executable(udp_send_binary_server udp_send_binary_server.cpp)
target_link_libraries(udp_send_binary_server ws2_32 wsock32)

# week11 exercise 8 udp send many text end client
add_executable(udp_send_many_text_end_client udp_send_many_text_end_client.cpp)
target_link_libraries(udp_send_many_text_end_client ws2_32 wsock32)

# week11 exercise 8 udp send many text end server
add_executable(udp_send_many_text_end_server udp_send_many_text_end_server.cpp)
target_link_libraries(udp_send_many_text_end_server ws2_32 wsock32)

# week12 tcp non block client
add_executable(tcp_non_block_client tcp_non_block_client.cpp)
target_link_libraries(tcp_non_block_client ws2_32 wsock32)

# week12 tcp non block server
add_executable(tcp_non_block_server tcp_non_block_server.cpp)
target_link_libraries(tcp_non_block_server ws2_32 wsock32)

# week12 tcp non block apply1 client
add_executable(tcp_non_block_apply1_client tcp_non_block_apply1_client.cpp)
target_link_libraries(tcp_non_block_apply1_client ws2_32 wsock32)

# week12 tcp non block apply1 server
add_executable(tcp_non_block_apply1_server tcp_non_block_apply1_server.cpp)
target_link_libraries(tcp_non_block_apply1_server ws2_32 wsock32)

# week12 tcp non block apply2 client
add_executable(tcp_non_block_apply2_client tcp_non_block_apply2_client.cpp)
target_link_libraries(tcp_non_block_apply2_client ws2_32 wsock32)

# week12 tcp non block apply2 server
add_executable(tcp_non_block_apply2_server tcp_non_block_apply2_server.cpp)
target_link_libraries(tcp_non_block_apply2_server ws2_32 wsock32)

# week12 tcp non block apply3 client
add_executable(tcp_non_block_apply3_client tcp_non_block_apply3_client.cpp)
target_link_libraries(tcp_non_block_apply3_client ws2_32 wsock32)

# week12 tcp non block apply3 server
add_executable(tcp_non_block_apply3_server tcp_non_block_apply3_server.cpp)
target_link_libraries(tcp_non_block_apply3_server ws2_32 wsock32)

# week13 week13_1 client
add_executable(week13_1_client week13_1_client.cpp)
target_link_libraries(week13_1_client ws2_32 wsock32)

# week13 week13_1 server
add_executable(week13_1_server week13_1_server.cpp)
target_link_libraries(week13_1_server ws2_32 wsock32)

# week13 week13_2 client
add_executable(week13_2_client week13_2_client.cpp)
target_link_libraries(week13_2_client ws2_32 wsock32)

# week13 week13_2 server
add_executable(week13_2_server week13_2_server.cpp)
target_link_libraries(week13_2_server ws2_32 wsock32)

# week13 week13_3 client
add_executable(week13_3_client week13_3_client.cpp)
target_link_libraries(week13_3_client ws2_32 wsock32)

# week13 week13_3 server
add_executable(week13_3_server week13_3_server.cpp)
target_link_libraries(week13_3_server ws2_32 wsock32)

# week13 week13_4 client
add_executable(week13_4_client week13_4_client.cpp)
target_link_libraries(week13_4_client ws2_32 wsock32)

# week13 week13_4 server
add_executable(week13_4_server week13_4_server.cpp)
target_link_libraries(week13_4_server ws2_32 wsock32)

# week13 week13_5 client
add_executable(week13_5_client week13_5_client.cpp)
target_link_libraries(week13_5_client ws2_32 wsock32)

# week13 week13_5 server
add_executable(week13_5_server week13_5_server.cpp)
target_link_libraries(week13_5_server ws2_32 wsock32)

# week14 create thread
add_executable(create_thread create_thread.cpp)
target_link_libraries(create_thread ws2_32 wsock32)

# week14 thread param
add_executable(thread_param thread_param.cpp)
target_link_libraries(thread_param ws2_32 wsock32)

# week14 thread param ex
add_executable(thread_param_ex thread_param_ex.cpp)
target_link_libraries(thread_param_ex ws2_32 wsock32)

# week14 multi thread
add_executable(multi_thread multi_thread.cpp)
target_link_libraries(multi_thread ws2_32 wsock32)

# week14 multi thread ex
add_executable(multi_thread_ex multi_thread_ex.cpp)
target_link_libraries(multi_thread_ex ws2_32 wsock32)

# week14 week 14 1 client
add_executable(week_14_1_client week_14_1_client.cpp)
target_link_libraries(week_14_1_client ws2_32 wsock32)

# week14 week 14 1 server
add_executable(week_14_1_server week_14_1_server.cpp)
target_link_libraries(week_14_1_server ws2_32 wsock32)

# week14 week 14 2 client
add_executable(week_14_2_client week_14_2_client.cpp)
target_link_libraries(week_14_2_client ws2_32 wsock32)

# week14 week 14 2 server
add_executable(week_14_2_server week_14_2_server.cpp)
target_link_libraries(week_14_2_server ws2_32 wsock32)

# week14 week 14 3 client
add_executable(week_14_3_client week_14_3_client.cpp)
target_link_libraries(week_14_3_client ws2_32 wsock32)

# week14 week 14 3 server
add_executable(week_14_3_server week_14_3_server.cpp)
target_link_libraries(week_14_3_server ws2_32 wsock32)

# week15 broadcast basic client
add_executable(broadcast_basic_client broadcast_basic_client.cpp)
target_link_libraries(broadcast_basic_client ws2_32 wsock32)

# week15 broadcast basic server
add_executable(broadcast_basic_server broadcast_basic_server.cpp)
target_link_libraries(broadcast_basic_server ws2_32 wsock32)

# week15 broadcast multiple data server
add_executable(broadcast_multiple_data_server broadcast_multiple_data_server.cpp)
target_link_libraries(broadcast_multiple_data_server ws2_32 wsock32)

# week15 broadcast change channel client
add_executable(broadcast_change_channel_client broadcast_change_channel_client.cpp)
target_link_libraries(broadcast_change_channel_client ws2_32 wsock32)

# week15 broadcast broadcast thread change channel client
add_executable(broadcast_thread_channel_client broadcast_thread_channel_client.cpp)
target_link_libraries(broadcast_thread_channel_client ws2_32 wsock32)

# week15 broadcast broadcast change channel port client
add_executable(broadcast_channel_port_client broadcast_channel_port_client.cpp)
target_link_libraries(broadcast_channel_port_client ws2_32 wsock32)

# week15 broadcast broadcast change channel port server
add_executable(broadcast_channel_port_server broadcast_channel_port_server.cpp)
target_link_libraries(broadcast_channel_port_server ws2_32 wsock32)

# clock
add_executable(clock clock.cpp)