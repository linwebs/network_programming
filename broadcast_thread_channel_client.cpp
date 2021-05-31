/*
 * NCYU 109 Network Programming
 * Broadcast thread change channel client
 * Created by linwebs on 2021/5/31.
 */
#include <iostream>
#include <winsock.h>

#define MAX_LINE 1024
#define BROADCAST_PORT 5678

using namespace std;

void *thread_main(void *thread_arg);

SOCKET client_sd;                   // socket descriptor
int client_length;                  // length of client address data structure
int now_channel;                    // now channel
sockaddr_in client_addr{};          // client address
char str[MAX_LINE];

int main() {
	int thread_id;                      // thread_id from CreateThread()
	WSADATA wsadata;                    // structure for WinSock setup communication
	sockaddr_in server_addr{};          // local address

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

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = 0;
	server_addr.sin_port = htons(BROADCAST_PORT);

	if (bind(client_sd, (LPSOCKADDR) &server_addr, sizeof(server_addr)) < 0) {
		cout << "bind() failed: " << WSAGetLastError() << endl;
		return 1;
	}

	cout << "client start listen broadcasting on port: " << BROADCAST_PORT << endl;

	now_channel = 0;

	if (CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE) thread_main, nullptr, 0, (LPDWORD) &thread_id) ==
		nullptr) {
		cout << "thread_create() failed" << endl;
	}

	while (true) {
		//cout << "Switch to channel(1~3): ";
		cin >> now_channel;
		cout << "Enter channel: " << now_channel << endl;

		if (now_channel < 1 || now_channel > 3) {
			break;
		}
	}

	// close TCP socket
	closesocket(client_sd);

	// finish "WinSock DLL"
	WSACleanup();

	return 0;
}

/**
 * Main program of a thread
 * @param thread_arg
 * @return
 */
void *thread_main(void *) {
	int recv_status;                    // receive from server

	while (true) {
		client_length = sizeof(client_addr);

		// receive data from server
		recv_status = recvfrom(client_sd, str, MAX_LINE, 0, (LPSOCKADDR) &client_addr, &client_length);

		if (recv_status < 0) {
			cout << "recvfrom() failed: " << WSAGetLastError() << endl;
			return nullptr;
		}

		switch (now_channel) {
			case 1:
				if (str[0] >= '0' && str[0] <= '9') {
					cout << "client from " << inet_ntoa(client_addr.sin_addr) << ": " << str << endl;
				}
				break;
			case 2:
				if (str[0] >= 'a' && str[0] <= 'z') {
					cout << "client from " << inet_ntoa(client_addr.sin_addr) << ": " << str << endl;
				}
				break;
			case 3:
				if (str[0] >= 'A' && str[0] <= 'Z') {
					cout << "client from " << inet_ntoa(client_addr.sin_addr) << ": " << str << endl;
				}
				break;
			default:
				cout << "" << endl;
		}
	}
}