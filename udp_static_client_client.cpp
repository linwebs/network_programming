/*
 * NCYU 109 Network Programming udp static client client
 * Created by linwebs on 2021/4/26.
 */
#include <iostream>
#include <winsock.h>

#define MAXLINE 1024
#define SEND_TIMES 10

using namespace std;

int main() {
	SOCKET sd;
	WSADATA wsadata;
	struct sockaddr_in serv{};

	char str[MAXLINE] = "I love NP!";

	// server's ip address
	const char server_ip[16] = "127.0.0.1";

	// server's port number
	u_short server_port = 5678;

	// send bytes
	int serv_len;

	// connect status
	int connect_status;

	// send status
	int send_status;

	// Call WSAStartup() to Register "WinSock DLL"
	WSAStartup(0x101, (WSADATA *) &wsadata);

	// Open a TCP socket
	sd = socket(AF_INET, SOCK_DGRAM, 0);

	// Prepare for connect.
	// Include sockaddr_ing struct (serv)
	serv.sin_family = AF_INET;

	// server's ip address
	serv.sin_addr.s_addr = inet_addr(server_ip);

	// server's port number
	// htons: host to network
	serv.sin_port = htons(server_port);

	serv_len = sizeof(serv);

	connect_status = connect(sd, reinterpret_cast<const sockaddr *>(&serv), serv_len);

	if (connect_status == SOCKET_ERROR) {
		cout << "connect to function failed with error: " << WSAGetLastError() << endl;
		closesocket(sd);
		WSACleanup();
		return 1;
	}

	for (int i = 0; i < SEND_TIMES; i++) {

		// connect to server
		send_status = send(sd, str, int(strlen(str) + 1), 0);

		if (send_status == SOCKET_ERROR) {
			cout << "send to function failed with error: " << WSAGetLastError() << endl;
			closesocket(sd);
			WSACleanup();
			return 1;
		}

		cout << "Client send: " << str << endl;

		Sleep(100);
	}

	// close UDP socket
	closesocket(sd);

	// finish "WinSock DLL"
	WSACleanup();

	//system("pause");

	return 0;
}