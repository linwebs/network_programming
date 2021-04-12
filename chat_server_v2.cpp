/*
 * NCYU 109 Network Programming chat server v2
 * Created by linwebs on 2021/4/12.
 */
#include <iostream>
#include <cctype>
#include <cstring>
#include <winsock.h>

#define MAXLINE 1024

using namespace std;

int main() {
	SOCKET serv_sd;
	SOCKET cli1_sd;
	SOCKET cli2_sd;
	int cli1_len;
	int cli2_len;
	char str[MAXLINE];

	struct sockaddr_in serv{};
	struct sockaddr_in cli1{};
	struct sockaddr_in cli2{};
	WSADATA wsadata;

	// server's ip address
	const char server_ip[16] = "127.0.0.1";

	// server's port number
	u_short server_port = 5678;

	// receive bytes
	int rec_len;

	// send bytes
	int send_len;

	// bind status
	int bind_status;

	// Call WSAStartup() to Register "WinSock DLL"
	WSAStartup(0x101, (LPWSADATA) &wsadata);

	// Open a TCP socket
	serv_sd = socket(AF_INET, SOCK_STREAM, 0);

	// Prepare for connect.
	// Include sockaddr_ing struct (serv)
	serv.sin_family = AF_INET;

	// server's ip address
	serv.sin_addr.s_addr = inet_addr(server_ip);

	// server's port number
	// htons: host to network
	serv.sin_port = htons(server_port);

	// bind
	bind_status = bind(serv_sd, (LPSOCKADDR) &serv, sizeof(serv));

	if (bind_status == SOCKET_ERROR) {
		cout << "bind function failed with error: " << WSAGetLastError() << endl;
		closesocket(serv_sd);
		WSACleanup();
		return 1;
	}

	// call listen() function to let socket enter listen mode
	listen(serv_sd, 5);

	cli1_len = sizeof(cli1);
	cli2_len = sizeof(cli2);

	cout << "歡迎使用聊天室伺服器(v2)" << endl;

	// accept connect
	cout << "等待 client 1 連線" << endl;
	cli1_sd = accept(serv_sd, (LPSOCKADDR) &cli1, &cli1_len);
	cout << "client 1 已連線" << endl;

	cout << "等待 client 2 連線" << endl;
	cli2_sd = accept(serv_sd, (LPSOCKADDR) &cli2, &cli2_len);
	cout << "client 2 已連線" << endl;

	while(true) {
		// receive from client 1
		rec_len = recv(cli1_sd, str, MAXLINE, 0);

		if(rec_len <= 0) {
			break;
		}

		cout << "[1->2]: " << str << "(" << rec_len << " bytes)" << endl;

		// send msg from server to client 2
		send_len = send(cli2_sd, str, int(strlen(str) + 1), 0);

		if(!strcmp(str, "bye")) {
			break;
		}

		if(send_len == SOCKET_ERROR) {
			cout << "[1->2] 傳送失敗" << endl;
		}

		// receive from client 1
		rec_len = recv(cli2_sd, str, MAXLINE, 0);

		if(rec_len <= 0) {
			break;
		}

		cout << "[2->1]: " << str << "(" << rec_len << " bytes)" << endl;

		// send from server
		send_len = send(cli1_sd, str, int(strlen(str) + 1), 0);

		if(send_len == SOCKET_ERROR) {
			cout << "[2->1] 傳送失敗" << endl;
		}

		if(!strcmp(str, "bye")) {
			break;
		}
	}

	// close TCP socket
	closesocket(serv_sd);
	closesocket(cli1_sd);
	closesocket(cli2_sd);

	// finish "WinSock DLL"
	WSACleanup();

	//system("pause");

	return 0;
}