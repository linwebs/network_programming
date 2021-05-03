/*
 * NCYU 109 Network Programming
 * Exercise 1: tcp send first and receive later server
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

	char str_send[MAXLINE] = "I love Algorithm!";
	char str_recv[MAXLINE];

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

	// send bytes
	int send_len;

	// receive bytes
	int recv_len;

	// Include sockaddr_ing struct (serv)
	serv.sin_family = AF_INET;

	// server's ip address
	serv.sin_addr.s_addr = inet_addr(server_ip);

	// server's port number
	// htons: host to network
	serv.sin_port = htons(server_port);

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

	// send to server
	send_len = send(sd_client, str_send, int(strlen(str_send)), 0);

	cout << "send: " << str_send << "(" << send_len << " bytes)" << endl;

	// receive from server
	recv_len = recv(sd_client, str_recv, MAXLINE, 0);

	str_recv[recv_len] = '\0';

	cout << "receive: " << str_recv << "(" << recv_len << " bytes)" << endl;

	// close TCP socket
	closesocket(sd);

	// finish "WinSock DLL"
	WSACleanup();

	//system("pause");

	return 0;
}