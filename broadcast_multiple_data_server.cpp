/*
 * NCYU 109 Network Programming
 * Broadcast multiple data server
 * Created by linwebs on 2021/5/31.
 */
#include <iostream>
#include <winsock.h>

#define MAX_LINE 20
#define BROADCAST_PORT 5678

using namespace std;

int main() {
	SOCKET server_sd;                   // socket descriptor for server
	int client_length;                  // length of client address data structure
	int send_status;                    // send from server
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
	server_sd = socket(AF_INET, SOCK_DGRAM, 0);

	if (server_sd == SOCKET_ERROR) {
		cout << "socket() failed: " << WSAGetLastError() << endl;
	}

	BOOL broadcast = TRUE;

	// open broadcast
	if (setsockopt(server_sd, SOL_SOCKET, SO_BROADCAST, (const char *) &broadcast, sizeof(broadcast)) < 0) {
		cout << "setsockopt() failed: " << WSAGetLastError() << endl;
	}

	client_length = sizeof(client_addr);

	cout << "server start broadcasting on port: " << BROADCAST_PORT << endl;

	client_addr.sin_family = AF_INET;
	client_addr.sin_addr.s_addr = inet_addr("255.255.255.255");
	client_addr.sin_port = htons(BROADCAST_PORT);

	int i = 1;
	while (true) {
		// 0 1 2 3 4 5 6 8 7 9
		memset(str, i % 10 + '0', sizeof(str));
		send_status = sendto(server_sd, str, strlen(str), 0, (LPSOCKADDR) &client_addr, client_length);
		if (send_status < 0) {
			cout << "sendto() failed: " << WSAGetLastError() << endl;
			break;
		}
		cout << "server broadcast: " << str << endl;

		// a b c d e f g h i j
		memset(str, i % 26 + 'a', sizeof(str));
		send_status = sendto(server_sd, str, strlen(str), 0, (LPSOCKADDR) &client_addr, client_length);
		if (send_status < 0) {
			cout << "sendto() failed: " << WSAGetLastError() << endl;
			break;
		}
		cout << "server broadcast: " << str << endl;

		// A B C D E F G H I J
		memset(str, i % 26 + 'A', sizeof(str));
		send_status = sendto(server_sd, str, strlen(str), 0, (LPSOCKADDR) &client_addr, client_length);
		if (send_status < 0) {
			cout << "sendto() failed: " << WSAGetLastError() << endl;
			break;
		}
		cout << "server broadcast: " << str << endl;

		Sleep(1000);

		i++;
	}

	// close TCP socket
	closesocket(server_sd);

	// finish "WinSock DLL"
	WSACleanup();

	return 0;
}