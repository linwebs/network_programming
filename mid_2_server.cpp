/*
 * NCYU 109 Network Programming mid 2 server
 * Created by linwebs on 2021/4/19.
 */
#include <iostream>
#include <cstring>
#include <winsock.h>

#define MAXLINE 1024

using namespace std;

int main() {
	SOCKET serv_sd;
	SOCKET cli1_sd;
	SOCKET cli2_sd;
	int cli1_len;
	int cli2_len;

	char str[MAXLINE];

	string last_char = "";

	bool is_init = true;

	int client1_error_time = 0;
	int client2_error_time = 0;

	struct sockaddr_in serv{};
	struct sockaddr_in cli1{};
	struct sockaddr_in cli2{};

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

	// Call WSAStartup() to Register "WinSock DLL"
	WSAStartup(0x101, (LPWSADATA) &wsadata);

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
		cout << "bind function failed with error: " << WSAGetLastError() << endl;
		closesocket(serv_sd);
		WSACleanup();
		return 1;
	}

	// call listen() function to let socket enter listen mode
	listen(serv_sd, 5);

	cli1_len = sizeof(cli1);
	cli2_len = sizeof(cli2);

	cout << "Server waits." << endl;

	// accept connect
	//cout << "等待 client 1 連線" << endl;
	cli1_sd = accept(serv_sd, (LPSOCKADDR) &cli1, &cli1_len);
	cout << "One client connects." << endl;

	//cout << "等待 client 2 連線" << endl;
	cli2_sd = accept(serv_sd, (LPSOCKADDR) &cli2, &cli2_len);
	cout << "Two clients connect." << endl;

	while (true) {
		// receive from client 1
		while (true) {
			rec_len = recv(cli1_sd, str, MAXLINE, 0);

			if (rec_len <= 0) {
				break;
			}

			cout << "1->2:" << str << endl;

			if (is_init) {
				last_char = str;

				last_char = last_char.substr(last_char.size() - 3, 3);

				string output = "正確，尾字是";
				output += last_char;

				cout << output << endl;

				is_init = false;

				// send msg from server to client 2
				send_len = send(cli2_sd, str, int(strlen(str) + 1), 0);

				if (send_len == SOCKET_ERROR) {
					cout << "[1->2] send error" << WSAGetLastError() << endl;
				}

				break;
			} else {
				string first_char = str;
				first_char = first_char.substr(0, 3);

				if (last_char == first_char) {
					last_char = str;

					last_char = last_char.substr(last_char.size() - 3, 3);

					string output = "正確，尾字是";
					output += last_char;

					cout << output << endl;

					// send msg from server to client 2
					send_len = send(cli2_sd, str, int(strlen(str) + 1), 0);

					if (send_len == SOCKET_ERROR) {
						cout << "[1->2] send error" << WSAGetLastError() << endl;
					}

					break;
				} else {
					string output = "沒有對正確，client1犯規一次";

					if (++client1_error_time >= 3) {
						output = "client1犯規超過三次，client1輸了";
					}

					// send msg from server to client 2
					send_len = send(cli1_sd, output.c_str(), int(output.size() + 1), 0);

					if (send_len == SOCKET_ERROR) {
						cout << "[client->1] send error" << WSAGetLastError() << endl;
					}

					cout << output << endl;

					if (client1_error_time >= 3) {
						break;
					}
				}
			}
		}

		if (client1_error_time >= 3) {
			//cout << "client1犯規超過三次，client2輸了" << endl;

			strcpy(str, "client1犯規超過三次，client1輸了");

			// send msg from server to client 2
			send_len = send(cli2_sd, str, int(strlen(str) + 1), 0);

			if (send_len == SOCKET_ERROR) {
				cout << "[1->2] send error" << WSAGetLastError() << endl;
			}

			break;
		}


		// receive from client 2
		while (true) {
			rec_len = recv(cli2_sd, str, MAXLINE, 0);

			if (rec_len <= 0) {
				break;
			}

			cout << "2->1:" << str << endl;

			string first_char = str;
			first_char = first_char.substr(0, 3);

			if (last_char == first_char) {
				last_char = str;

				last_char = last_char.substr(last_char.size() - 3, 3);

				string output = "正確，尾字是";
				output += last_char;

				cout << output << endl;

				// send msg from server to client 1
				send_len = send(cli1_sd, str, int(strlen(str) + 1), 0);

				if (send_len == SOCKET_ERROR) {
					cout << "[2->1] send error" << WSAGetLastError() << endl;
				}

				break;
			} else {
				string output = "沒有對正確，client2犯規一次";

				if (++client2_error_time >= 3) {
					output = "client2犯規超過三次，client2輸了";
				}

				// send msg from server to client 2
				send_len = send(cli2_sd, output.c_str(), int(output.size() + 1), 0);

				if (send_len == SOCKET_ERROR) {
					cout << "[client->2] send error" << WSAGetLastError() << endl;
				}

				cout << output << endl;

				if (client2_error_time >= 3) {
					break;
				}
			}
		}

		if (client2_error_time >= 3) {
			//cout << "client2犯規超過三次，client2輸了" << endl;

			strcpy(str, "client2犯規超過三次，client2輸了");

			// send msg from server to client 2
			send_len = send(cli1_sd, str, int(strlen(str) + 1), 0);

			if (send_len == SOCKET_ERROR) {
				cout << "[2->1] send error" << WSAGetLastError() << endl;
			}

			break;
		}
	}

	// close TCP socket
	closesocket(serv_sd);
	closesocket(cli1_sd);
	closesocket(cli2_sd);

	// finish "WinSock DLL"
	WSACleanup();

	//system("pause");

	return 0;
}