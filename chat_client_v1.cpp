/*
 * NCYU 109 Network Programming chat client v1
 * Created by linwebs on 2021/3/29.
 */
#include <iostream>
#include <winsock.h>

#define MAXLINE 1024

using namespace std;

int main() {
	SOCKET sd;
	struct sockaddr_in serv;

	string input = "";
	char str[MAXLINE] = "";
	char str_r[MAXLINE];

	WSADATA wsadata;

	// server's ip address
	const char server_ip[16] = "127.0.0.1";

	// server's port number
	u_short server_port = 5678;

	// receive bytes
	int rec_len;

	// connect status
	int conn_status;

	// Call WSAStartup() to Register "WinSock DLL"
	WSAStartup(0x101, (LPWSADATA) &wsadata);

	// Open a TCP socket
	sd = socket(AF_INET, SOCK_STREAM, 0);

	// Prepare for connect.
	// Include sockaddr_ing struct (serv)
	serv.sin_family = AF_INET;

	// server's ip address
	serv.sin_addr.s_addr = inet_addr(server_ip);

	// server's port number
	// htons: host to network
	serv.sin_port = htons(server_port);

	// connect to server
	conn_status = connect(sd, (LPSOCKADDR) &serv, sizeof(serv));

	if (conn_status == SOCKET_ERROR) {
		cout << "connect function failed with error: " << WSAGetLastError() << endl;
		closesocket(sd);
		WSACleanup();
		return 1;
	}

	cout << "歡迎使用聊天室(v1)" << endl;

	while (true) {
		cout << "請輸入文字: (輸入exit離開程式)" << endl;

		getline(cin, input);

		strcpy(str, input.c_str());

		// send to server
		send(sd, str, int(strlen(str) + 1), 0);
		cout << "client 傳送: " << str << "(" << strlen(str) + 1 << " bytes)" << endl;

		if (input == "exit") {
			break;
		}

		// receive from server
		rec_len = recv(sd, str_r, MAXLINE, 0);
		cout << "client 接收: " << str_r << "(" << rec_len << " bytes)" << endl;

	}

	// close TCP socket
	closesocket(sd);

	// finish "WinSock DLL"
	WSACleanup();

	//system("pause");

	return 0;
}