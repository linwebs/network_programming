/*
 * Created by linwebs on 2021/3/22.
 */
#include <iostream>
#include <winsock.h>

// 定義回傳字元最大數量
#define MAXLINE 1024

using namespace std;

/*
 * 執行完畢結果
 * int status	=> 執行狀態
 * int send_len	=> 傳送的內容長度
 * int recv_len	=> 接收到的內容長度
 * string send	=> 傳送的內容
 * string recv	=> 接收到的內容
 */
struct content {
	int status;
	int send_len;
	int recv_len;
	string send;
	string recv;
};

content *simpletcp_service(const char str[MAXLINE]);

void output(content *result);

bool init_simpletcp_service(const char server_ip[16], u_short server_port);

void finish_simpletcp_service();

SOCKET sd;
WSADATA wsadata;
struct sockaddr_in serv{};

int main() {
	string msg, ip;
	u_short port;
	cout << "請輸入要連線的 ip address:" << endl;
	cin >> ip;
	cout << "請輸入要連線的 port number:" << endl;
	cin >> port;
	if (init_simpletcp_service(ip.c_str(), port)) {
		getline(cin, msg);
		//	while (true) {
		cout << "請輸入要傳送的訊息:" << endl;
		if (msg == "exit") {
			cout << "goodbye~" << endl;
			//break;
		}
		msg = "GET / HTTP/1.1\r\nHost: localhost\r\nConnection: close\r\n\r\n";
		//getline(cin, msg);
		content *result = simpletcp_service(msg.c_str());
		if (result->status == 0) {
			output(result);
			//cout << "test 1" << endl;
		} else {
			//cout << "test 2" << endl;
			//	break;
		}
		//	}
		finish_simpletcp_service();
	}
	return 0;
}

bool init_simpletcp_service(const char server_ip[16], u_short server_port) {
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
		cout << "[錯誤] 無法連線，錯誤訊息: " << WSAGetLastError() << endl;
		closesocket(sd);
		WSACleanup();
		return false;
	} else {
		return true;
	}
}

/*
 * 連線至 Simple TCP Service
 * const char str[MAXLINE] 傳送的內容
 * const char server_ip[16] 伺服器端 ip 位址 (ipv4 格式)
 * u_short server_port 伺服器端埠號
 *
 * 回傳 content 指標
 */
content *simpletcp_service(const char str[MAXLINE]) {
	// send status
	int send_status;

	// receive string
	char str_r[MAXLINE + 1] = "";
	char str_r2[MAXLINE + 1] = "";

	// receive bytes
	int rec_len, rec_len2;

	auto *result = new content;

	// send "how are you" to echo server
	send_status = send(sd, str, int(strlen(str)) + 1, 0);

	if (send_status == SOCKET_ERROR) {
		cout << "[錯誤] 無法傳送訊息，錯誤訊息: " << WSAGetLastError() << endl;

		result->status = 1;
		result->recv = to_string(WSAGetLastError());

		return result;
	}
	//cout << "test 3" << endl;

	result->status = 0;
	result->send = str;
	result->send_len = int(strlen(str) + 1);

	//cout << "test 4" << endl;
	// receive echo server
	rec_len = recv(sd, str_r, MAXLINE, 0);
	rec_len2 = recv(sd, str_r2, MAXLINE, 0);
	//cout << "test 5" << endl;
	if (rec_len == SOCKET_ERROR) {
		cout << "[錯誤] 無法接收訊息，錯誤訊息: " << WSAGetLastError() << endl;

		result->status = 1;
		result->recv = to_string(WSAGetLastError());

		return result;
	}
	//cout << "test 6" << endl;

	// cout << "recv: " << str_r << "(" << rec_len << " bytes)" << endl;
	result->recv = strcat(str_r, str_r2);
	result->recv_len = rec_len + rec_len2;

	return result;
}

void finish_simpletcp_service() {
	int close_socket_status;

	// close TCP socket
	close_socket_status = closesocket(sd);

	if (close_socket_status == SOCKET_ERROR) {
		cout << "[錯誤] 無法關閉 socket，錯誤訊息: " << WSAGetLastError() << endl;
	}

	// finish "WinSock DLL"
	WSACleanup();
}

/*
 * 執行完畢將結果輸出
 * content *result 執行結果指標
 */
void output(content *result) {
	if (result->status == 0) {
		cout << "[傳送內容] " << result->send << "(" << result->send_len << "bytes)" << endl;
		cout << "[回應內容] " << result->recv << "(" << result->recv_len << "bytes)" << endl;
	}
}