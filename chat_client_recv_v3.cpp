/*
 * NCYU 109 Network Programming chat client recv v3
 * Created by linwebs on 2021/4/12.
 */
#include <iostream>
#include <winsock.h>

#define MAXLINE 1024

using namespace std;

string get_user(const string &input);

string get_room(const string &input);

string get_msg(const string &input);

int main() {
	SOCKET sd;
	struct sockaddr_in serv{};

	// user name
	string user;
	string now_room;
	string now_user;
	string now_msg;

	// room name
	string room;

	char str[MAXLINE] = "";

	WSADATA wsadata;

	// server's ip address
	const char server_ip[16] = "127.0.0.1";

	// server's port number
	u_short server_port = 5678;

	// receive bytes
	int rec_len;

	// connect status
	int conn_status;

	cout << "歡迎使用聊天室 client 端顯示程式" << endl;

	cout << "請輸入使用者名稱: ";
	getline(cin, user);
	cout << endl;

	cout << "請輸入房間名稱: ";
	getline(cin, room);
	cout << endl;

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

	// connect to server
	conn_status = connect(sd, (LPSOCKADDR) &serv, sizeof(serv));

	if (conn_status == SOCKET_ERROR) {
		cout << "connect function failed with error: " << WSAGetLastError() << endl;
		closesocket(sd);
		WSACleanup();
		return 1;
	}

	while (true) {
		// receive from server
		rec_len = recv(sd, str, MAXLINE, 0);

		if (rec_len <= 0) {
			cout << "[錯誤] 接收訊息錯誤" << endl;
			break;
		}

		// 接收並印出訊息

		// room is correct

		now_user = get_user(str);
		now_room = get_room(str);
		now_msg = get_msg(str);
		//cout << "[user]: " << now_user << "[room]: " << now_room << "[msg] : " << now_msg << endl;

		if (now_room == room) {
			if (now_user == user) {
				// my self
				cout << "[我自己]:\t" << get_msg(str) << endl;
			} else {
				// other people
				cout << "[" << get_user(str) << "]:\t" << get_msg(str) << endl;
			}
		}
		//cout << "[訊息]: " << str << endl;


		if (now_msg == "bye") {
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

string get_user(const string &input) {
	return input.substr(0, input.find(','));
}

string get_room(const string &input) {
	// no room
	string no = input.substr(input.find(',') + 1);
	return no.substr(0, no.find(','));
}

string get_msg(const string &input) {
	string no;
	// no room
	no = input.substr(input.find(',') + 1);
	// no user
	no = no.substr(no.find(',') + 1);
	return no.substr(0, no.find(','));
}