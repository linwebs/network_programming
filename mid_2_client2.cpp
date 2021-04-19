/*
 * NCYU 109 Network Programming mid 2 client 2
 * Created by linwebs on 2021/4/19.
 */
#include <iostream>
#include <winsock.h>

#define MAXLINE 1024

using namespace std;

int main() {
	SOCKET sd;
	struct sockaddr_in serv{};

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

	cout << "Connect to server." << endl;

	while (true) {
		// receive from server
		rec_len = recv(sd, str_r, MAXLINE, 0);
		cout << "[Client 1]:" << str_r << endl;

		string recv_str = str_r;

		if(recv_str.substr(0, 6) == "client") {
			break;
		}

		cout << "[client 2]:";

		getline(cin, input);

		strcpy(str, input.c_str());

		// send to server
		send(sd, str, int(strlen(str) + 1), 0);
		//cout << "client 2 傳送: " << str << "(" << strlen(str) + 1 << " bytes)" << endl;
	}

	// close TCP socket
	closesocket(sd);

	// finish "WinSock DLL"
	WSACleanup();

	//system("pause");

	return 0;
}