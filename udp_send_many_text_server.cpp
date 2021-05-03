/*
 * NCYU 109 Network Programming
 * Exercise 7: udp send many text server
 * Created by linwebs on 2021/5/3.
 */
#include <iostream>
#include <winsock.h>

#define MAXLINE 1024
#define LISTEN_NUM 5

using namespace std;

int main() {
	SOCKET sd;
	SOCKET sd_client;
	WSADATA wsadata;
	struct sockaddr_in serv{};
	struct sockaddr_in client{};

	FILE *file_out;

	char str_recv[MAXLINE];

	// server's ip address
	const char server_ip[16] = "127.0.0.1";

	// server's port number
	u_short server_port = 5678;

	// bind status
	int bind_status;

	// serv bytes
	int serv_len;

	// receive bytes
	int recv_len = 0;

	// Include sockaddr_ing struct (serv)
	serv.sin_family = AF_INET;

	// server's ip address
	serv.sin_addr.s_addr = inet_addr(server_ip);

	// server's port number
	// htons: host to network
	serv.sin_port = htons(server_port);

	// write and overwrite the file
	file_out = fopen("out.txt", "w+t");

	// Call WSAStartup() to Register "WinSock DLL"
	WSAStartup(0x101, (LPWSADATA) &wsadata);

	// Open a TCP socket
	sd = socket(AF_INET, SOCK_DGRAM, 0);

	cout << "sd: " << sd << endl;

	serv_len = sizeof(serv);

	// bind client
	bind_status = bind(sd, (struct sockaddr *) &serv, serv_len);

	if (bind_status == SOCKET_ERROR) {
		cout << "bind function failed with error: " << WSAGetLastError() << endl;
		closesocket(sd);
		WSACleanup();
		return 1;
	}

	cout << "bind: " << bind_status << endl;

	// receive from server
	while (true) {
		recv_len = recv(sd, str_recv, MAXLINE, 0);

		if (recv_len <= 0) {
			break;
		}

		fwrite(str_recv, 1, recv_len, file_out);

		cout << "receive: " << recv_len << " bytes" << endl;
	}

	// close file
	fclose(file_out);

	// close TCP socket
	closesocket(sd);

	// finish "WinSock DLL"
	WSACleanup();

	//system("pause");

	return 0;
}