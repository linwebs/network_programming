/*
 * NCYU 109 Network Programming
 * Chat room server multiple thread client
 * Created by linwebs on 2021/5/24.
 */
#include <iostream>
#include <cstring>
#include <winsock.h>

#define MAX_LINE 1024

using namespace std;

int main() {
	SOCKET sd1, sd2;
	sockaddr_in server{};
	char str[1024] = "I love NP!";
	WSADATA wsadata;
	int conn_status;
	int send_status;
	int recv_status;

	// Call WSAStartup() to Register "WinSock DLL"
	WSAStartup(0x101, (LPWSADATA) &wsadata);

	sd1 = socket(AF_INET, SOCK_STREAM, 0);
	sd2 = socket(AF_INET, SOCK_STREAM, 0);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_port = htons(5678);

	// connect to server
	conn_status = connect(sd1, (LPSOCKADDR) &server, sizeof(server));
	if (conn_status == SOCKET_ERROR) {
		cout << "connect() failed" << endl;
	}
	conn_status = connect(sd2, (LPSOCKADDR) &server, sizeof(server));
	if (conn_status == SOCKET_ERROR) {
		cout << "connect() failed" << endl;
	}

	while (true) {
		strcpy(str, "I love NP!\n");
		send_status = send(sd1, str, int(strlen(str) + 1), 0);    // send to server
		if (send_status == SOCKET_ERROR) {
			cout << "send() failed" << endl;
			break;
		}
		cout << "send: " << str;

		Sleep(1000);

		recv_status = recv(sd1, str, MAX_LINE, 0);    // receive data from server
		if (recv_status == SOCKET_ERROR) {
			cout << "recv() failed" << endl;
			break;
		}
		cout << "recv: " << str;

		strcpy(str, "I love Algorithm!\n");
		send_status = send(sd2, str, int(strlen(str) + 1), 0);    // send to server
		if (send_status == SOCKET_ERROR) {
			cout << "send() failed" << endl;
			break;
		}
		cout << "send: " << str;

		Sleep(1000);

		recv_status = recv(sd2, str, MAX_LINE, 0);    // receive data from server
		if (recv_status == SOCKET_ERROR) {
			cout << "recv() failed" << endl;
			break;
		}
		cout << "recv: " << str;
	}

	// close TCP socket
	closesocket(sd1);
	closesocket(sd2);

	// finish "WinSock DLL"
	WSACleanup();

	return 0;
}