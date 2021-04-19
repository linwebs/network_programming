/*
 * NCYU 109 Network Programming mid 1 server
 * Created by linwebs on 2021/4/19.
 */
#include <iostream>
#include <chrono>
#include <cctype>
#include <cstring>
#include <ctime>
#include <winsock.h>

#define MAXLINE 1024

using namespace std;

/*
 * 執行內容
 * int status			=> 執行狀態
 * int recv_head_len	=> 接收到的標頭長度
 * int recv_content_len	=> 接收到的內容長度
 * string page			=> 取得的頁面
 * string recv_head		=> 接收到的標頭長度
 * string recv_content	=> 接收到的內容長度
 */
struct content {
	int status = -1;
	int recv_head_len = 0;
	int recv_content_len = 0;
	string page;
	string recv_head;
	string recv_content;
};

content *get_page(const string &page);

int main() {
	SOCKET serv_sd;
	SOCKET cli_sd;
	SOCKET http_sd;
	int cli_len;
	char str[MAXLINE];
	char str_r[MAXLINE];

	struct sockaddr_in serv{};
	struct sockaddr_in cli{};
	struct sockaddr_in http{};
	WSADATA wsadata;

	// server's ip address
	const char server_ip[16] = "127.0.0.1";

	// server's port number
	u_short server_port = 1234;

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

	cli_len = sizeof(cli);

	// accept connect
	cout << "Server is waiting for client." << endl;
	cli_sd = accept(serv_sd, (LPSOCKADDR) &cli, &cli_len);

	if (cli_sd == SOCKET_ERROR) {
		cout << "can't accept: " << WSAGetLastError() << endl;
	}

	while (true) {
		// receive from client
		rec_len = recv(cli_sd, str, MAXLINE, 0);

		cout << "Recv:" << str << endl;
		//cout << "server recv: " << str << "(" << rec_len << " bytes)" << endl;

		if (rec_len == SOCKET_ERROR) {
			cout << "receive error: " << WSAGetLastError() << endl;
			break;
		}

		// (1) time
		if (!strcmp(str, "time")) {
			auto time = chrono::system_clock::now();

			time_t now_time = std::chrono::system_clock::to_time_t(time);

			string result_str = ctime(&now_time);

			strcpy(str_r, result_str.c_str());

			cout << "Send time to client." << endl;
		} else if (rec_len > 8) {
			string recv_str = str;

			//cout << "rec_len" << rec_len << endl;

			if (recv_str.substr(0, 6) == "ask://") {
				// (2) ask
				recv_str = recv_str.substr(6);
				strcpy(str_r, recv_str.c_str());


				struct in_addr sAddr{};
				LPHOSTENT hp;

				sAddr.s_addr = inet_addr(recv_str.c_str());

				hp = gethostbyaddr((LPSTR) &sAddr, sizeof(sAddr), AF_INET);

				if (hp == nullptr) {
					// other
					cout << "get hp error, code:" << WSAGetLastError() << endl;
					strcpy(str_r, "");

					cout << "Send nothing." << endl;
				} else {
					//printf("host name:%s\n", hp->h_name);
					//printf("host nickname:%s\n", hp->h_aliases[0]);
					// printf("host IP:%s\n\n", inet_ntoa(*(LPIN_ADDR) (hp->h_addr)));
					strcpy(str_r, (hp->h_name));

					cout << "Send domain name to client." << endl;
				}
			} else if (recv_str.substr(0, 7) == "http://") {
				// (3) http
				recv_str = recv_str.substr(7);
				strcpy(str_r, recv_str.c_str());

				// Open a TCP socket
				http_sd = socket(AF_INET, SOCK_STREAM, 0);

				// Prepare for connect.
				// Include sockaddr_ing struct (serv)
				http.sin_family = AF_INET;

				// server's ip address
				http.sin_addr.s_addr = inet_addr(recv_str.c_str());

				// server's port number
				// htons: host to network
				http.sin_port = htons(80);

				int conn_status = connect(http_sd, (LPSOCKADDR) &http, sizeof(http));

				if (conn_status == SOCKET_ERROR) {
					cout << "connect error: " << WSAGetLastError() << endl;
					closesocket(http_sd);
					WSACleanup();
					break;
				}

				string request = "GET / HTTP/1.1\r\nHost: " + recv_str + "\r\nConnection: close\r\n\r\n";

				int send_status = send(http_sd, request.c_str(), int(request.size()) + 1, 0);

				if (send_status == SOCKET_ERROR) {
					cout << "send error: " << WSAGetLastError() << endl;
					break;
				}

				char str_http[MAXLINE] = "";

				int rec_http_len = recv(http_sd, str_http, MAXLINE, 0);

				if (rec_http_len == SOCKET_ERROR) {
					cout << "receive error: " << WSAGetLastError() << endl;
					break;
				}

				strcpy(str_r, str_http);


				cout << "Send web page to client." << endl;

			} else {
				// other

				strcpy(str_r, "");

				cout << "Send nothing." << endl;
			}
		} else if (!strcmp(str, "end")) {
			// (4) end

			strcpy(str_r, "Test completes.");

			cout << "Complete service for the client." << endl;
		} else {
			// other

			strcpy(str_r, "");

			cout << "Send nothing." << endl;
		}

		// send from server
		send_len = send(cli_sd, str_r, int(strlen(str_r) + 1), 0);

		if (send_len == SOCKET_ERROR) {
			cout << "send error: " << WSAGetLastError() << endl;
			break;
		}

		//cout << "server reply: " << str_r << "(" << send_len << " bytes)" << endl;

		if (!strcmp(str, "end")) {
			closesocket(cli_sd);

			// call listen() function to let socket enter listen mode
			listen(serv_sd, 5);

			cli_len = sizeof(cli);

			// accept connect
			cout << endl << "Server is waiting for client." << endl;
			cli_sd = accept(serv_sd, (LPSOCKADDR) &cli, &cli_len);

			if (cli_sd == SOCKET_ERROR) {
				cout << "can't accept: " << WSAGetLastError() << endl;
			}
		}
	}

	// close TCP socket
	closesocket(serv_sd);

	// finish "WinSock DLL"
	WSACleanup();

	//system("pause");

	return 0;
}