/*
 * NCYU 109 Network Programming chat client send v3
 * Created by linwebs on 2021/4/12.
 */
#include <iostream>
#include <winsock.h>

#define MAXLINE 1024

using namespace std;

int main() {
	SOCKET sd;
	struct sockaddr_in serv{};

	// input msg
	string input;

	// user name
	string user;

	// room name
	string room;

	// separate symbol
	string separate = ",";

	char str[MAXLINE] = "";

	WSADATA wsadata;

	// server's ip address
	const char server_ip[16] = "127.0.0.1";

	// server's port number
	u_short server_port = 5678;

	// connect status
	int conn_status;

	cout << "歡迎使用聊天室 client 端傳送程式" << endl;

	cout << "請輸入使用者名稱: ";
	getline(cin, user);
	cout << endl;

	cout << "請輸入房間名稱: ";
	getline(cin, room);
	cout << endl;

	// Call WSAStartup() to Register "WinSock DLL"
	WSAStartup(0x101, (LPWSADATA) &wsadata);

	// Prepare for connect.
	// Include sockaddr_ing struct (serv)
	serv.sin_family = AF_INET;

	// server's ip address
	serv.sin_addr.s_addr = inet_addr(server_ip);

	// server's port number
	// htons: host to network
	serv.sin_port = htons(server_port);

	while (true) {
		// Open a TCP socket
		sd = socket(AF_INET, SOCK_STREAM, 0);

		cout << "[輸入] 請輸入文字: (輸入 bye 離開程式)" << endl;

		getline(cin, input);

		// connect to server
		conn_status = connect(sd, (LPSOCKADDR) &serv, sizeof(serv));

		if (conn_status == SOCKET_ERROR) {
			cout << "connect function failed with error: " << WSAGetLastError() << endl;
			closesocket(sd);
			WSACleanup();
			return 1;
		}
		strcpy(str, user.c_str());
		strcat(str, separate.c_str());
		strcat(str, room.c_str());
		strcat(str, separate.c_str());
		strcat(str, input.c_str());

		// send to server
		send(sd, str, int(strlen(str) + 1), 0);
		cout << "[" << user << "於" << room << "傳送] : " << input << endl;

		cout << "--------------------------------" << endl;

		if (input == "bye") {
			break;
		}
	}

	// close TCP socket
	closesocket(sd);

	// finish "WinSock DLL"
	WSACleanup();

	//system("pause");

	return 0;
}