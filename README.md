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
* UDP server 多對一連線
      * [udp_mult_client_client1](udp_mult_client_client1.cpp) UDP server 多對一連線 1 號 client 端
    * [udp_mult_client_client2](udp_mult_client_client2.cpp) UDP server 多對一連線 2 號 client 端
    * [udp_mult_client_server](udp_mult_client_server.cpp) UDP server 多對一連線 server 端
* UDP 傳送對象固定
  * [udp_static_client_client](udp_static_client_client.cpp) UDP 傳送對象固定 client 端
* UDP 傳送端固定連接埠
  * [udp_client_static_port_client](udp_client_static_port_client.cpp) UDP 傳送端固定連接埠 client 端
* UDP 接收端不關心傳送來源
  * [udp_no_care_source_server](udp_no_care_source_server.cpp) UDP 接收端不關心傳送來源 server 端
* [hw5.pdf](hw_pdf/hw5.pdf) HW5 說明文件

## 其餘項目

* [clock](clock.cpp) C++執行時間計算程式
