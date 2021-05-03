/*
 * NCYU 109 Network Programming
 * Exercise 6: tcp send binary server
 * Created by linwebs on 2021/5/3.
 */
#include <iostream>
#include <winsock.h>

#define MAXSIZE 1024
#define LISTEN_NUM 5

using namespace std;

int main() {
	SOCKET sd;
	SOCKET sd_client;
	WSADATA wsadata;
	struct sockaddr_in serv{};
	struct sockaddr_in client{};

	FILE *file_out;

	char buffer[MAXSIZE];

	// server's ip address
	const char server_ip[16] = "127.0.0.1";

	// server's port number
	u_short server_port = 5678;

	// bind status
	int bind_status;

	// listen status
	int listen_status;

	// serv bytes
	int serv_len;

	// client bytes
	int client_len;

	// file size
	int file_size = 0;

	// Include sockaddr_ing struct (serv)
	serv.sin_family = AF_INET;

	// server's ip address
	serv.sin_addr.s_addr = inet_addr(server_ip);

	// server's port number
	// htons: host to network
	serv.sin_port = htons(server_port);

	// write and overwrite the file
	file_out = fopen("out.jpg", "w+b");

	// Call WSAStartup() to Register "WinSock DLL"
	WSAStartup(0x101, (LPWSADATA) &wsadata);

	// Open a TCP socket
	sd = socket(AF_INET, SOCK_STREAM, 0);

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

	listen_status = listen(sd, LISTEN_NUM);

	cout << "listen: " << listen_status << endl;

	client_len = sizeof(client);

	sd_client = accept(sd, (struct sockaddr *) &client, &client_len);

	// receive from server
	while (true) {
		file_size = recv(sd_client, buffer, MAXSIZE, 0);

		if (file_size <= 0) {
			break;
		}

		fwrite(buffer, 1, file_size, file_out);

		cout << "receive: " << file_size << " bytes" << endl;
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