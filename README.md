# 國立嘉義大學109學年度網路程式設計課程

NCYU 109 Network Programming Design  
Created by Linwebs.

## 環境

* [CMake 3.17.5](CMakeLists.txt)
* MinGW w64 6.0
* GCC 8.1.0
* CLion 2021.1

## Week3

* [dns_search](dns_search.cpp) 利用IP查詢hostname
* [hw1](hw1.cpp) HW-連續查詢ip
* [hw1.pdf](hw_pdf/hw1.pdf) HW1 說明文件

## Week4

* [echo_service](echo_service.cpp) Simple TCP Echo Service
* [hw2](hw2.cpp) HW-5種服務的示範程式
* [hw2.pdf](hw_pdf/hw2.pdf) HW2 說明文件

## Week5

* [http_get](http_get.cpp) HTTP GET Request
* [hw3](hw3.cpp) HW-簡易的網頁爬蟲程式
* [hw3.pdf](hw_pdf/hw3.pdf) HW3 說明文件

# Week6

* [echo_client](echo_client.cpp) client 端程式
* [echo_server](echo_server.cpp) server 端程式
* [guest_number_client](guest_number_client.cpp) 猜數字 client 端程式
* [guest_number_server](guest_number_server.cpp) 猜數字 server 端程式

# Week8

* Ver.1
	* [chat_client_v1](chat_client_v1.cpp) 聊天室 client 端程式 (v1)
	* [chat_server_v1](chat_server_v1.cpp) 聊天室 server 端程式 (v1)
* Ver.2
	* [chat_client1_v2](chat_client1_v2.cpp) 聊天室 1 號 client 端程式 (v2)
	* [chat_client2_v2](chat_client2_v2.cpp) 聊天室 2 號 client 端程式 (v2)
	* [chat_server_v2](chat_server_v2.cpp) 聊天室 server 端程式 (v2)
* Ver.3(HW)
	* [chat_client_send_v3](chat_client_send_v3.cpp) 聊天室 client 端傳送程式 (v3)
	* [chat_client_recv_v3](chat_client_recv_v3.cpp) 聊天室 client 端接收程式 (v3)
	* [chat_server_v3](chat_server_v3.cpp) 聊天室 server 端程式 (v3)
* [hw4.pdf](hw_pdf/hw4.pdf) HW4 說明文件

# Week9

* [mid_1_server](mid_1_server.cpp) 期中考 1 server
* [mid_1_client](mid_1_client.cpp) 期中考 1 client
* [mid_2_server](mid_2_server.cpp) 期中考 2 server
* [mid_2_client1](mid_2_client1.cpp) 期中考 2 client1
* [mid_2_client2](mid_2_client2.cpp) 期中考 2 client2
* [mid.pdf](hw_pdf/mid.pdf) 109-2 NP midterm 說明文件

# Week10

* 基本 UDP 連線
	* [basic_udp_client](basic_udp_client.cpp) 基本 UDP 連線 client 端
	* [basic_udp_server](basic_udp_server.cpp) 基本 UDP 連線 server 端
* UDP client 一對多連線
	* [udp_mult_server_client](udp_mult_server_client.cpp) UDP client 一對多連線 client 端
	* [udp_mult_server_server1](udp_mult_server_server1.cpp) UDP client 一對多連線 1 號 server 端
	* [udp_mult_server_server2](udp_mult_server_server2.cpp) UDP client 一對多連線 2 號 server 端
* UDP server 多對一連線 * [udp_mult_client_client1](udp_mult_client_client1.cpp) UDP server 多對一連線 1 號 client 端
	* [udp_mult_client_client2](udp_mult_client_client2.cpp) UDP server 多對一連線 2 號 client 端
	* [udp_mult_client_server](udp_mult_client_server.cpp) UDP server 多對一連線 server 端
* UDP 傳送對象固定
	* [udp_static_client_client](udp_static_client_client.cpp) UDP 傳送對象固定 client 端
* UDP 傳送端固定連接埠
	* [udp_client_static_port_client](udp_client_static_port_client.cpp) UDP 傳送端固定連接埠 client 端
* UDP 接收端不關心傳送來源
	* [udp_no_care_source_server](udp_no_care_source_server.cpp) UDP 接收端不關心傳送來源 server 端
* [hw5.pdf](hw_pdf/hw5.pdf) HW5 說明文件

# Week11

* 練習1
	* 先送後收
		* [tcp_send_first_client](tcp_send_first_client.cpp) 先送後收 client 端
		* [tcp_send_first_server](tcp_send_first_server.cpp) 先送後收 server 端
	* 先收後送
		* [tcp_recv_first_client](tcp_recv_first_client.cpp) 先收後送 client 端
		* [tcp_recv_first_server](tcp_recv_first_server.cpp) 先收後送 server 端
	* 繳交
		* [hw8_exercise1_1_client](hw8_exercise1_1_client.cpp) 練習一 1 client 端
		* [hw8_exercise1_1_server](hw8_exercise1_1_server.cpp) 練習一 1 server 端
		* [hw8_exercise1_2_client](hw8_exercise1_2_client.cpp) 練習一 2 client 端
		* [hw8_exercise1_2_server](hw8_exercise1_2_server.cpp) 練習一 2 server 端
* 練習2
	* 繳交
		* [hw8_exercise2_1_client](hw8_exercise2_1_client.cpp) 練習二 1 client 端
		* [hw8_exercise2_1_server](hw8_exercise2_1_server.cpp) 練習二 1 server 端
		* [hw8_exercise2_2_client](hw8_exercise2_2_client.cpp) 練習二 2 client 端
		* [hw8_exercise2_2_server](hw8_exercise2_2_server.cpp) 練習二 2 server 端
* 練習3
	* 繳交
		* [hw8_exercise3_client](hw8_exercise3_client.cpp) 練習三 client 端
		* [hw8_exercise3_server](hw8_exercise3_server.cpp) 練習三 server 端
* 練習4
	* 繳交
		* [hw8_exercise4_3_client](hw8_exercise4_3_client.cpp) 練習四 client 端
		* [hw8_exercise4_3_server](hw8_exercise4_3_server.cpp) 練習四 server 端
* 練習5
	* 連續傳送大量文字
		* [text_read_write](text_read_write.cpp) 文字檔讀寫
		* [send_many_text_client](send_many_text_client.cpp) 連續傳送大量文字 client 端
		* [send_many_text_server](send_many_text_server.cpp) 連續傳送大量文字 server 端
* 練習6
	* 傳送二位元檔案
		* [binary_read_write](binary_read_write.cpp) 文字檔讀寫
		* [send_binary_client](send_binary_client.cpp) 傳送二位元檔案 client 端
		* [send_binary_server](send_binary_server.cpp) 傳送二位元檔案 server 端
* 練習7
	* UDP 連續傳送大量文字
		* [udp_send_many_text_client](udp_send_many_text_client.cpp) UDP 連續傳送大量文字 client 端
		* [udp_send_many_text_server](udp_send_many_text_server.cpp) UDP 連續傳送大量文字 server 端
	* UDP 傳送二位元檔案
		* [udp_send_binary_client](udp_send_binary_client.cpp) UDP 傳送二位元檔案 client 端
		* [udp_send_binary_server](udp_send_binary_server.cpp) UDP 傳送二位元檔案 server 端
* 練習8
	* UDP 連續傳送大量文字並結束
		* [udp_send_many_text_end_client](udp_send_many_text_end_client.cpp) UDP 連續傳送大量文字並結束 client 端
		* [udp_send_many_text_end_server](udp_send_many_text_end_server.cpp) UDP 連續傳送大量文字並結束 server 端

# Week12

* 非攔阻模式
	* [tcp_non_block_client](tcp_non_block_client.cpp) 非攔阻模式 client
	* [tcp_non_block_server](tcp_non_block_server.cpp) 非攔阻模式 server
* 非攔阻模式應用1
	* [tcp_non_block_apply1_client](tcp_non_block_apply1_client.cpp) 非攔阻模式應用1 client
	* [tcp_non_block_apply1_server](tcp_non_block_apply1_server.cpp) 非攔阻模式應用1 server
* 非攔阻模式應用2
	* [tcp_non_block_apply2_client](tcp_non_block_apply2_client.cpp) 非攔阻模式應用2 client
	* [tcp_non_block_apply2_server](tcp_non_block_apply2_server.cpp) 非攔阻模式應用2 server
* 非攔阻模式應用3
	* [tcp_non_block_apply3_client](tcp_non_block_apply3_client.cpp) 非攔阻模式應用3 client
	* [tcp_non_block_apply3_server](tcp_non_block_apply3_server.cpp) 非攔阻模式應用3 server

# Week13

* 一送一收，觀察檢查表的運作
	* [week13_1_client](week13_1_client.cpp) 一送一收 client
	* [week13_1_server](week13_1_server.cpp) 一送一收 server
* 兩個 client，server 會 echo
	* [week13_2_client](week13_2_client.cpp) 兩個 client，server 會 echo client
	* [week13_2_server](week13_2_server.cpp) 兩個 client，server 會 echo server
* 服務多個 client 的 echo server
	* [week13_3_client](week13_3_client.cpp) 服務多個 client 的 echo server client
	* [week13_3_server](week13_3_server.cpp) 服務多個 client 的 echo server server
* 使用 writefds 來傳送
	* [week13_4_client](week13_4_client.cpp) 使用 writefds 來傳送 client
	* [week13_4_server](week13_4_server.cpp) 使用 writefds 來傳送 server
* 使用 timeout
	* [week13_5_client](week13_5_client.cpp) 使用 timeout client
	* [week13_5_server](week13_5_server.cpp) 使用 timeout server

# Week14

* 產生 thread
	* [create_thread](create_thread.cpp) 產生 thread
* 產生 thread 傳遞參數
	* [thread_param](thread_param.cpp) 產生 thread 傳遞參數
* 產生 thread 傳遞參數 1~10
	* [thread_param_ex](thread_param_ex.cpp) 產生 thread 傳遞參數 1~10
* multiple thread 交換資料
	* [multi_thread](multi_thread.cpp) multiple thread 交換資料
* multiple thread 交換資料 1 加到 100
	* [multi_thread_ex](multi_thread_ex.cpp) multiple thread 交換資料 1 加到 100
* Echo Server 多工 
	* [week_14_1_client](week_14_1_client.cpp) Echo Server 多工 client
	* [week_14_1_server](week_14_1_server.cpp) Echo Server 多工 server
* 聊天室 Server 多工
	* [week_14_2_client](week_14_2_client.cpp) 聊天室 Server 多工 client
	* [week_14_2_server](week_14_2_server.cpp) 聊天室 Server 多工 server
* 聊天室 Client 多工
	* [week_14_3_client](week_14_3_client.cpp) 聊天室 Client 多工 client
	* [week_14_3_server](week_14_3_server.cpp) 聊天室 Client 多工 server

## 其餘項目

* [clock](clock.cpp) C++執行時間計算程式
