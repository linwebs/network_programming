/*
 * NCYU 109 Network Programming
 * Exercise 8: udp send many text client
 * Created by linwebs on 2021/5/3.
 */
#include <iostream>
#include <cstdio>
#include <winsock.h>

#define MAXLINE 1024

using namespace std;

int main() {
	SOCKET sd;
	WSADATA wsadata;
	struct sockaddr_in serv{};

	FILE *file_in;

	char str_send[MAXLINE] = "";

	// server's ip address
	const char server_ip[16] = "127.0.0.1";

	// server's port number
	u_short server_port = 5678;

	// connect status
	int conn_status;

	// serv bytes
	int serv_len;

	// send bytes
	int send_len;

	// send sum bytes
	int send_sum;

	// Include sockaddr_ing struct (serv)
	serv.sin_family = AF_INET;

	// server's ip address
	serv.sin_addr.s_addr = inet_addr(server_ip);

	// server's port number
	// htons: host to network
	serv.sin_port = htons(server_port);

	// read file
	file_in = fopen("in.jpg", "rb");

	// Call WSAStartup() to Register "WinSock DLL"
	WSAStartup(0x101, (LPWSADATA) &wsadata);

	// Open a TCP socket
	sd = socket(AF_INET, SOCK_DGRAM, 0);

	cout << "sd: " << sd << endl;

	serv_len = sizeof(serv);

	// connect to server
	conn_status = connect(sd, (struct sockaddr *) &serv, serv_len);

	if (conn_status == SOCKET_ERROR) {
		cout << "connect function failed with error: " << WSAGetLastError() << endl;
		closesocket(sd);
		WSACleanup();
		return 1;
	}

	cout << "connect: " << conn_status << endl;

	send_sum = 0;

	// loop get string from file
	while (true) {
		send_len = fread(str_send, 1, MAXLINE, file_in);

		if (send_len <= 0) {
			break;
		}

		send_sum += send_len;

		// send to server
		send_len = send(sd, str_send, send_len, 0);

		cout << "send: " << send_len << " bytes" << endl;
	}

	send(sd, "end", 4, 0);

	cout << "file transmission complete. (sum: " << send_sum << " bytes)" << endl;

	itoa(send_sum, str_send, 10);
	send(sd, str_send, sizeof(str_send), 0);

	// close file
	fclose(file_in);

	// close TCP socket
	closesocket(sd);

	// finish "WinSock DLL"
	WSACleanup();

	//system("pause");

	return 0;
}