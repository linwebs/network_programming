/*
 * NCYU 109 Network Programming
 * Broadcast basic client
 * Created by linwebs on 2021/5/31.
 */
#include <iostream>
#include <winsock.h>

#define MAX_LINE 1024
#define BROADCAST_PORT 5678

using namespace std;

int main() {
	SOCKET client_sd;                   // socket descriptor
	int server_length;                  // length of client address data structure
	int recv_status;                    // receive from server
	WSADATA wsadata;                    // structure for WinSock setup communication
	sockaddr_in server_addr{};          // local address
	sockaddr_in client_addr{};          // client address
	char str[MAX_LINE];

	// load Winsock 2.0 DLL
	if (WSAStartup(0x101, &wsadata) != 0) {
		cout << "WSAStartup() failed: " << WSAGetLastError() << endl;
		exit(1);
	}

	// create UDP socket
	client_sd = socket(AF_INET, SOCK_DGRAM, 0);

	if (client_sd == SOCKET_ERROR) {
		cout << "socket() failed: " << WSAGetLastError() << endl;
	}

	BOOL broadcast = TRUE;

	// open broadcast
	if (setsockopt(client_sd, SOL_SOCKET, SO_BROADCAST, (const char *) &broadcast, sizeof(broadcast)) < 0) {
		cout << "setsockopt() failed: " << WSAGetLastError() << endl;
	}

	client_addr.sin_family = AF_INET;
	client_addr.sin_addr.s_addr = 0;
	client_addr.sin_port = htons(BROADCAST_PORT);

	if (bind(client_sd, (LPSOCKADDR) &client_addr, sizeof(client_addr)) < 0) {
		cout << "bind() failed: " << WSAGetLastError() << endl;
		return 1;
	}

	server_length = sizeof(server_addr);

	cout << "client start listen broadcasting on port: " << BROADCAST_PORT << endl;

	while (true) {
		recv_status = recvfrom(client_sd, str, MAX_LINE, 0, (LPSOCKADDR) &server_addr, &server_length);

		if (recv_status < 0) {
			cout << "recvfrom() failed: " << WSAGetLastError() << endl;
			break;
		}

		cout << "client from " << inet_ntoa(server_addr.sin_addr) << ": " << str << endl;
	}

	// close TCP socket
	closesocket(client_sd);

	// finish "WinSock DLL"
	WSACleanup();

	return 0;
}