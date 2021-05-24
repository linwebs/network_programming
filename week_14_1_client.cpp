/*
 * NCYU 109 Network Programming
 * Server multiple thread client
 * Created by linwebs on 2021/5/24.
 */
#include <iostream>
#include <cstring>
#include <winsock.h>
#define MAX_LINE 1024

using namespace std;

int main() {
	SOCKET sd;
	sockaddr_in server{};
	char str[1024] = "I love NP!";
	WSADATA wsadata;
	int conn_status;
	int send_status;
	int recv_status;

	// Call WSAStartup() to Register "WinSock DLL"
	WSAStartup(0x101, (LPWSADATA) &wsadata);

	sd = socket(AF_INET, SOCK_STREAM, 0);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_port = htons(5678);

	// connect to server
	conn_status = connect(sd, (LPSOCKADDR) &server, sizeof(server));
	if (conn_status == SOCKET_ERROR) {
		cout << "connect() failed" << endl;
	}

	while (true) {
		strcpy(str, "How are you?\n");
		send_status = send(sd, str, int(strlen(str)+1), 0);	// send to server
		if(send_status == SOCKET_ERROR) {
			break;
		}
		cout << "send: " << str;

		Sleep(1000);

		recv_status = recv(sd, str, MAX_LINE, 0);	// receive data from server
		if(recv_status == SOCKET_ERROR) {
			break;
		}
		cout << "recv: " << str;
	}

	// close TCP socket
	closesocket(sd);

	// finish "WinSock DLL"
	WSACleanup();

	return 0;
}