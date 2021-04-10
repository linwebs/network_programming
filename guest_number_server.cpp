/*
 * NCYU 109 Network Programming guest number server
 * Created by linwebs on 2021/4/10.
 */
#include <iostream>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <winsock.h>

#define MAXLINE 1024

using namespace std;

int str_to_int(const string &input);

string reply_msg(int server_number, int now_client);

int guess_next(int max, int min, int last, int result);

string reply_char(int server_number, int now_client);

string reply_int_to_string(int num);

int main() {
	SOCKET serv_sd;
	SOCKET cli_sd;
	int cli_len;
	char str[MAXLINE];
	char str_r[MAXLINE];

	struct sockaddr_in serv{};
	struct sockaddr_in cli{};
	WSADATA wsadata;

	// server's ip address
	const char server_ip[16] = "127.0.0.1";

	// server's port number
	u_short server_port = 5678;

	// receive bytes
	int rec_len;

	// send bytes
	int send_len;

	// bind status
	int bind_status;

	// number
	int server_number;             // server 謎底
	int client_last = 50;          // server 上次猜 client
	int client_min = 1;            // server 猜 client min
	int client_max = 100;          // server 猜 client max
	int client_reply;              // server 猜 client 的結果 [1 => too large, 2 => too small]
	int now_client;                // client 猜 server
	bool first = true;             // 第一次

	cout << "歡迎使用猜數字程式(伺服器端)" << endl;

	// Call WSAStartup() to Register "WinSock DLL"
	if (WSAStartup(0x101, (LPWSADATA) &wsadata) == SOCKET_ERROR) {
		cout << "[錯誤] 無法啟動Windows Sockets，錯誤訊息: " << WSAGetLastError() << endl;
		return -1;
	}

	// Open a TCP socket
	serv_sd = socket(AF_INET, SOCK_STREAM, 0);

	// Prepare for connect.
	// Include sockaddr_ing struct (serv)
	serv.sin_family = AF_INET;

	// server's ip address
	serv.sin_addr.s_addr = inet_addr(server_ip);

	// server's port number
	// htons: host to network
	serv.sin_port = htons(server_port);

	// bind
	bind_status = bind(serv_sd, (LPSOCKADDR) &serv, sizeof(serv));

	if (bind_status == SOCKET_ERROR) {
		cout << "[錯誤] 無法綁定本機位址: " << WSAGetLastError() << endl;
		closesocket(serv_sd);
		WSACleanup();
		return 1;
	}

	// call listen() function to let socket enter listen mode
	listen(serv_sd, 5);

	cli_len = sizeof(cli);

	// accept connect
	cout << "[訊息] 等待客戶端連線" << endl;
	cli_sd = accept(serv_sd, (LPSOCKADDR) &cli, &cli_len);

	cout << "[訊息] 客戶端已連線" << endl;

	// set rand seed
	srand(time(nullptr));

	// get a random number
	server_number = rand() % 100 + 1;
	cout << "[訊息] 伺服器端的隨機數字為: " << server_number << endl;

	while (true) {
		// receive from client
		rec_len = recv(cli_sd, str, MAXLINE, 0);
		//cout << "server recv: " << str << "(" << rec_len << " bytes)" << endl;

		if(rec_len == SOCKET_ERROR) {
			break;
		}

		if (!strcmp(str, "exit")) {
			break;
		} else if (!strcmp(str, "too large")) {
			client_max = client_last - 1;
			int tmp_guess = guess_next(client_max, client_min, client_last, 1);
			if(tmp_guess == client_last) {
				client_last++;
			} else {
				client_last = tmp_guess;
			}
			//cout << "[訊息] client 說太大" << endl;
			continue;
		} else if (!strcmp(str, "too small")) {
			client_min = client_last + 1;
			int tmp_guess = guess_next(client_max, client_min, client_last, 2);
			if(tmp_guess == client_last) {
				client_last++;
			} else {
				client_last = tmp_guess;
			}
			//cout << "[訊息] client 說太小" << endl;
			continue;
		} else if (!strcmp(str, "get answer")) {
			strcpy(str_r, "4");
			send(cli_sd, str_r, int(strlen(str_r) + 1), 0);
			break;
		} else {
			now_client = str_to_int(str);
		}

		// send from server
		client_last;

		strcpy(str_r, reply_char(server_number, now_client).c_str());
		strcat(str_r, reply_int_to_string(client_last).c_str());

		send_len = send(cli_sd, str_r, int(strlen(str_r) + 1), 0);

		if (send_len == SOCKET_ERROR) {
			cout << "[錯誤] 傳送錯誤" << endl;
			break;
		}

		cout << "client 猜" << now_client << "，" << reply_msg(server_number, now_client) << "。server 猜 " << client_last << "。" << endl;
		//cout << "server reply: " << str_r << "(" << send_len << " bytes)" << endl;

	}

	// close TCP socket
	closesocket(serv_sd);
	closesocket(cli_sd);

	// finish "WinSock DLL"
	WSACleanup();

	//system("pause");

	return 0;
}

int str_to_int(const string &input) {
	int output = 0;
	for (auto item:input) {
		if (item >= '0' && item <= '9') {
			output = output * 10 + (item - 48);
		}
	}
	return output;
}

int guess_next(int max, int min, int last, int result) {
	if (result == 1) {
		// too large
		return (last + min) / 2;
	} else if (result == 2) {
		// too small
		return (last + max) / 2;
	} else {
		return 50;
	}
}

string reply_msg(int server_number, int now_client) {
	string result;
	if (now_client < server_number) {
		result = "too small";
	} else if (now_client > server_number) {
		result = "too large";
	} else {
		result = "get answer";
	}
	return result;
}

string reply_char(int server_number, int now_client) {
	string result;
	if (now_client < server_number) {
		result = '2';
	} else if (now_client > server_number) {
		result = '1';
	} else {
		result = '3';
	}
	return result;
}

string reply_int_to_string(int num) {
	string result;
	if (num < 10) {
		result = to_string(num) + "  ";
	} else if (num < 10) {
		result = to_string(num) + " ";
	} else {
		result = to_string(num) + "";
	}
	return result;
}