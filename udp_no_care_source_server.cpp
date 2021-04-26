/*
 * NCYU 109 Network Programming udp no care source server
 * Created by linwebs on 2021/4/26.
 */
#include <iostream>
#include <winsock.h>

#define MAXLINE 1024

using namespace std;

int main() {
	SOCKET sd;
	WSADATA wsadata;
	struct sockaddr_in serv{};
	struct sockaddr_in cli{};

	char str[MAXLINE] = "";

	// server's ip address
	const char server_ip[16] = "127.0.0.1";

	// server's port number
	u_short server_port = 5678;

	// serv bytes
	int serv_len;

	// cli bytes
	int cli_len;

	// send status
	int bind_status;

	// receive status
	int recv_status;

	// Prepare for connect.
	// Include sockaddr_ing struct (serv)
	serv.sin_family = AF_INET;

	// server's ip address
	serv.sin_addr.s_addr = inet_addr(server_ip);

	// server's port number
	// htons: host to network
	serv.sin_port = htons(server_port);

	// Call WSAStartup() to Register "WinSock DLL"
	WSAStartup(0x101, (WSADATA *) &wsadata);

	// Open a TCP socket
	sd = socket(AF_INET, SOCK_DGRAM, 0);

	serv_len = sizeof(serv);
	cli_len = sizeof(cli);

	// connect to server
	bind_status = bind(sd, reinterpret_cast<const sockaddr *>(&serv), serv_len);

	if (bind_status == SOCKET_ERROR) {
		cout << "bind function failed with error: " << WSAGetLastError() << endl;
		closesocket(sd);
		WSACleanup();
		return 1;
	}

	cout << "Ready to receive on " << server_port << " port" << endl;

	while (true) {
		recv_status = recv(sd, str, MAXLINE, 0);

		cout << "Receive: " << str << "(" << recv_status << " bytes)" << endl;

		string str_str = str;

		if (str_str == "exit") {
			break;
		}
	}

	// close UDP socket
	closesocket(sd);

	// finish "WinSock DLL"
	WSACleanup();

	//system("pause");

	return 0;
}