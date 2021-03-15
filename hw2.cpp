/*
 * NCYU 109 Network Programming HW2
 * Created by Linwebs on 2021/3/15.
 */

#include <iostream>
#include <winsock.h>

// �w�q�^�Ǧr���̤j�ƶq
#define MAXLINE 1024

using namespace std;

/*
 * ���槹�����G
 * int status	=> ���檬�A
 * int send_len	=> �ǰe�����e����
 * int recv_len	=> �����쪺���e����
 * string send	=> �ǰe�����e
 * string recv	=> �����쪺���e
 */
struct content {
	int status;
	int send_len;
	int recv_len;
	string send;
	string recv;
};

void welcome_msg();

void choose_service();

void func_echo();

void func_discard();

void func_daytime();

void func_quote();

void func_chargen();

content *simpletcp_service(const char str[MAXLINE], const char server_ip[16], u_short server_port);

void output(content *result);

int main() {
	welcome_msg();
	choose_service();
	return 0;
}

/*
 * �w��e��
 */
void welcome_msg() {
	cout << "+++++++++++++++++++++++++++++" << endl;
	cout << "| �п�J�A�Ȫ��N��(1~5)�H����A�� |" << endl;
	cout << "| 1. �^���A�� (Echo)          |" << endl;
	cout << "| 2. ���A�� (Discard)       |" << endl;
	cout << "| 3. ����ɶ��A�� (Daytime)    |" << endl;
	cout << "| 4. �C��@�y (QUOTE)         |" << endl;
	cout << "| 5. �r�����;� (CHARGEN)      |" << endl;
	cout << "+++++++++++++++++++++++++++++" << endl;
}

/*
 * ��ܪA��
 */
void choose_service() {
	char service;
	cin >> service;
	switch (service) {
		case '1':
			func_echo();
			break;
		case '2':
			func_discard();
			break;
		case '3':
			func_daytime();
			break;
		case '4':
			func_quote();
			break;
		case '5':
			func_chargen();
			break;
		default:
			cout << "[���~] ��J���榡���~�A�Э��s��J" << endl;
	}
}

/*
 * ���� 1�^���A�� (Echo)
 */
void func_echo() {
	content *result = simpletcp_service("I love NCYU CSIE", "127.0.0.1", 7);
	output(result);
}

/*
 * ���� 2���A�� (Discard)
 */
void func_discard() {
	cout << "[�T��] ������A�ȡA�Y�ݵ����A�Ф�������{��" << endl;
	content *result = simpletcp_service("I love NCYU CSIE", "127.0.0.1", 9);
	output(result);
}

/*
 * ���� 3����ɶ��A�� (Daytime)
 */
void func_daytime() {
	content *result = simpletcp_service("", "127.0.0.1", 13);
	output(result);
}

/*
 * ���� 4�C��@�y (QUOTE)
 */
void func_quote() {
	content *result = simpletcp_service("", "127.0.0.1", 17);
	output(result);
}

/*
 * ���� 5�r�����;� (CHARGEN)
 */
void func_chargen() {
	content *result = simpletcp_service("", "127.0.0.1", 19);
	output(result);
}

/*
 * ���槹���N���G��X
 * content *result ���浲�G����
 */
void output(content *result) {
	cout << "++++++++++" << endl;
	cout << "| ���浲�G |" << endl;
	cout << "++++++++++" << endl;
	if (result->status == 0) {
		cout << "[�ǰe���e] " << endl;
		cout << result->send << endl;
		cout << "[�ǰe���e����] " << result->send_len << "bytes" << endl;
		cout << "[�^�����e] " << endl;
		cout << result->recv << endl;
		cout << "[�^�����e����] " << result->recv_len << "bytes" << endl;
	} else {
		cout << "[���~] �L�k�s�u�A���~�T��: " << result->recv << endl;
	}
}

/*
 * �s�u�� Simple TCP Service
 * const char str[MAXLINE] �ǰe�����e
 * const char server_ip[16] ���A���� ip ��} (ipv4 �榡)
 * u_short server_port ���A���ݰ�
 *
 * �^�� content ����
 */
content *simpletcp_service(const char str[MAXLINE], const char server_ip[16], u_short server_port) {
	SOCKET sd;
	struct sockaddr_in serv{};
	WSADATA wsadata;

	// send string
	//const char str[MAXLINE] = "abc";

	// receive string
	char str_r[MAXLINE + 1] = "";

	// echo server's ip address
	//const char server_ip[16] = "127.0.0.1";

	// echo server's port number
	//u_short server_port = 7;

	// receive bytes
	int rec_len;

	// connect status
	int conn_status;

	auto *result = new content;

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
		//cout << "connect function failed with error: " << WSAGetLastError() << endl;
		result->status = 1;
		result->recv = to_string(WSAGetLastError());
		closesocket(sd);
		WSACleanup();
		return result;
	}


	// send "how are you" to echo server
	send(sd, str, int(strlen(str) + 1), 0);
	// cout << "send: " << str << "(" << strlen(str) + 1 << " bytes)" << endl;

	result->status = 0;
	result->send = str;
	result->send_len = int(strlen(str) + 1);

	// receive echo server
	rec_len = recv(sd, str_r, MAXLINE, 0);
	if (rec_len == SOCKET_ERROR) {
		cout << "error";
	}

	// cout << "recv: " << str_r << "(" << rec_len << " bytes)" << endl;

	result->recv = str_r;
	result->recv_len = rec_len;
	// close TCP socket
	closesocket(sd);

	// finish "WinSock DLL"
	WSACleanup();

	return result;
}