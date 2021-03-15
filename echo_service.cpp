/*
 * NCYU 109 Network Programming Week 4
 * Simple TCP/IP Services (simptcp)
 * Echo Service
 * Created by linwebs on 2021/3/15.
 */
#include <iostream>
#include <winsock.h>
//#include <string>
//#include <ctime>

#define MAXLINE 1024

using namespace std;

int main() {

	SOCKET sd;
	struct sockaddr_in serv{};
	WSADATA wsadata;

	// send string
	const char str[MAXLINE] = "abc";

	// receive string
	char str_r[MAXLINE];

	// echo server's ip address
	const char server_ip[16] = "127.0.0.1";

	// echo server's port number
	u_short server_port = 7;

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

	// connect to echo server
	conn_status = connect(sd, (LPSOCKADDR) &serv, sizeof(serv));

	if (conn_status == SOCKET_ERROR) {
		cout << "connect function failed with error: " << WSAGetLastError() << endl;
		closesocket(sd);
		WSACleanup();
		return 1;
	}

	// send "how are you" to echo server
	send(sd, str, int(strlen(str) + 1), 0);
	cout << "send: " << str << "(" << strlen(str) + 1 << " bytes)" << endl;

	// receive echo server
	rec_len = recv(sd, str_r, MAXLINE, 0);
	cout << "recv: " << str_r << "(" << rec_len << " bytes)" << endl;

	// close TCP socket
	closesocket(sd);

	// finish "WinSock DLL"
	WSACleanup();

	//system("pause");

	return 0;
}
