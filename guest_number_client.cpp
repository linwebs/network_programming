/*
 * NCYU 109 Network Programming echo client
 * Created by linwebs on 2021/3/29.
 */
#include <iostream>
#include <winsock.h>

#define MAXLINE 1024

using namespace std;

int str_to_int(const string &);

//string reply_msg(int, const string &);
string reply_msg(int client_number, int now_server);

int get_server_num(string recv);

int main() {
	SOCKET sd;
	struct sockaddr_in serv{};

	string input;
	char str[MAXLINE] = "";
	char str_r[MAXLINE] = "";

	WSADATA wsadata;

	// server's ip address
	const char server_ip[16] = "127.0.0.1";

	// server's port number
	u_short server_port = 5678;

	// receive bytes
	int rec_len;

	// connect status
	int conn_status;

	// round
	int round = 0;

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

	// number
	string client_number_str;
	int client_number;

	if (conn_status == SOCKET_ERROR) {
		cout << "[錯誤] 無法連線，錯誤訊息: " << WSAGetLastError() << endl;
		closesocket(sd);
		WSACleanup();
		return 1;
	}
	cout << "請輸入一個數字(範圍1~100): ";
	cin >> client_number_str;
	client_number = str_to_int(client_number_str);

	while (true) {
		cout << "[回合" << ++round << "] 請輸入猜的數字：";

		cin >> input;

		strcpy(str, input.c_str());

		// send to server
		send(sd, str, int(strlen(str) + 1), 0);
		//cout << "client send: " << str << "(" << strlen(str) + 1 << " bytes)" << endl;

		if (input == "exit") {
			break;
		}

		// receive from server
		rec_len = recv(sd, str_r, MAXLINE, 0);
		//cout << "client recv: " << str_r << "(" << rec_len << " bytes)" << endl;

		if (rec_len > 0) {
			if (str_r[0] == '1') {
				cout << "server 說太大。server猜" << get_server_num(str_r) << "。請回覆：" << reply_msg(client_number, get_server_num(str_r)) << endl;
				//cout << "[Test] " << client_number << "  " << str_r << endl;
			} else if (str_r[0] == '2') {
				cout << "server 說太小。server猜" << get_server_num(str_r) << "。請回覆：" << reply_msg(client_number, get_server_num(str_r)) << endl;
				//cout << "[Test] " << client_number << "  " << str_r << endl;
			} else if (str_r[0] == '3') {
				cout << "server 說你猜對了。" << endl;
				break;
			} else if (str_r[0] == '4') {
				cout << "server 說: YA，我贏了~" << endl;
				break;
			} else {
				cout << "[錯誤] 伺服器回應錯誤" << endl;
				break;
			}
		}

		// server 猜中了


		getline(cin, input);

		cout << "回覆 > ";

		getline(cin, input);

		strcpy(str, input.c_str());

		// send to server
		send(sd, str, int(strlen(str) + 1), 0);

		// server 猜中了
		if (input == "get answer") {
			cout << "server 說: YA，我贏了~" << endl;
			break;
		}

	}

	// send exit
	strcpy(str, "exit");

	send(sd, str, int(strlen(str) + 1), 0);

	// close TCP socket
	closesocket(sd);

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

/*
string reply_msg(int ans, const string &recv) {
	string result = "too small";
	int recv_num = 0;
	for (int i = 1; i <= 3; i++) {
		recv_num = recv_num * 10 + (recv[i] - 48);
	}

	if (recv_num < ans) {
		result = "too small";
	} else if (recv_num > ans) {
		result = "too large";
	} else {
		result = "get answer";
	}

	return result;
}
*/
string reply_msg(int client_number, int now_server) {
	string result;
	if (now_server < client_number) {
		result = "too small";
	} else if (now_server > client_number) {
		result = "too large";
	} else {
		result = "get answer";
	}
	return result;
}

int get_server_num(string recv) {
	int recv_num = 0;
	for (int i = 1; i <= 3; i++) {
		if (recv[i] >= '0' && recv[i] <= '9') {
			recv_num = recv_num * 10 + (recv[i] - 48);
		}
	}
	return recv_num;
}