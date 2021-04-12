/*
 * NCYU 109 Network Programming chat server v1
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
	SOCKET cli_sd;
	int cli_len;
	char str[MAXLINE];
	char str_r[MAXLINE];

	struct sockaddr_in serv;
	struct sockaddr_in cli;
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

	cli_len = sizeof(cli);

	cout << "歡迎使用聊天室伺服器(v1)" << endl;

	// accept connect
	cout << "等待 client 端連線" << endl;
	cli_sd = accept(serv_sd, (LPSOCKADDR) &cli, &cli_len);

	cout << "client 已連線" << endl;

	while(true) {
		// receive from client
		rec_len = recv(cli_sd, str, MAXLINE, 0);
		cout << "server 收到: " << str << "(" << rec_len << " bytes)" << endl;

		if(!strcmp(str, "exit")) {
			break;
		}

		//strcpy(str, str_r);

		for (int i = 0; i < rec_len; i++) {
			str_r[i] = str[i];
		}

		// send from server
		send_len = send(cli_sd, str_r, int(strlen(str) + 1), 0);
		cout << "server 回覆: " << str_r << "(" << send_len << " bytes)" << endl;

	}

	// close TCP socket
	closesocket(serv_sd);
	closesocket(cli_sd);

	// finish "WinSock DLL"
	WSACleanup();

	//system("pause");

	return 0;
}