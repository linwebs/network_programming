/*
 * NCYU 109 Network Programming HW3
 * Created by linwebs on 2021/3/22.
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
	int status = -1;
	int send_len = 0;
	int recv_head_len = 0;
	int recv_content_len = 0;
	string page;
	string send;
	string recv_head;
	string recv_content;
};

/*
 * �s�����c
 * int next		=> �U�@�Ӷ}�l�M�䪺�s����m
 * string href	=> �s���ɮ�
 */
struct href_struct {
	int next = -1;
	string href;
};

content *winsock_service(const char str[MAXLINE]);

content *get_page(const string &page);

void output(content *result);

bool check_http_status(content *result);

href_struct *find_href(const string &html, int start);

int find_href_tag(const string &html, int start);

int find_href_quot(const string &html, int start);

bool init_winsock_service(const char server_ip[16], u_short server_port);

void finish_winsock_service();

void start_search(const string &page);

SOCKET sd;
WSADATA wsadata;
struct sockaddr_in serv{};
string ip;        // ip address
u_short port;    // port number

int main() {
	string msg;
	cout << "�п�J�n�s�u�� ip ��}(�p: 127.0.0.1):" << endl;
	cin >> ip;
	//ip = "127.0.0.1";

	cout << "�п�J�n�s�u�� port number(�p: 80):" << endl;
	cin >> port;
	//port = 8000;

	// test connect
	if (!init_winsock_service(ip.c_str(), port)) {
		return 0;
	}

	finish_winsock_service();

	cout << "�п�J�_�l����(�p: index.html):" << endl;
	// Input single line
	//getline(cin, msg);	// �Ĥ@����endl�Y��
	//getline(cin, msg);

	// Input single string
	cin >> msg;
	//msg = "index.html";

	if (msg == "exit") {
		cout << "goodbye~" << endl;
	}

	start_search(msg);

	return 0;
}

/*
 * �}�l�j�M����
 * @param page	=> ����
 */
void start_search(const string &page) {
	// result ���c => ���o����
	content *result = get_page(page);
	if (result->status == 0) {
		if (check_http_status(result)) {
			output(result);
			int next = 0;

			// �M��Ҧ��s���ÿ�X
			while (true) {
				href_struct *href = find_href(result->recv_content, next);
				if (href->next == -1) {
					break;
				}
				next = href->next;

				content *sub_result = get_page(href->href);
				if (check_http_status(sub_result)) {
					output(sub_result);
				} else {
					cout << "[���~] �������䤣��: " << href->href << endl;
				}
			}
		} else {
			cout << "[���~] �������䤣��: " << page << endl;
		}
	}
}

/*
 * ���o��@������T
 * @param page	=> ����
 * @return		=> ���o�쪺��T
 */
content *get_page(const string &page) {
	string request = "GET /" + page + " HTTP/1.1\r\nHost: localhost\r\nConnection: close\r\n\r\n";
	auto *result = winsock_service(request.c_str());
	if (result->status == -1) {
		return result;
	}
	auto *result_page = new content;
	result_page->recv_head_len = result->recv_head_len;
	result_page->recv_head = result->recv_head;
	result_page->recv_content_len = result->recv_content_len;
	result_page->recv_content = result->recv_content;
	result_page->status = result->status;
	result_page->send = result->send;
	result_page->send_len = result->send_len;
	result_page->page = page;
	return result_page;
}

/*
 * ��l�� Windows socket �A��
 * @param server_ip		=> ���A���� ip ��} (ipv4 �榡)
 * @param server_port	=> ���A���ݰ�
 * @return				=> ��l�Ʀ��\�P�_
 */
bool init_winsock_service(const char server_ip[16], u_short server_port) {
	// connect status
	int conn_status;

	// Call WSAStartup() to Register "WinSock DLL"
	if (WSAStartup(0x101, (LPWSADATA) &wsadata) == SOCKET_ERROR) {
		cout << "[���~] �L�k�Ұ�Windows Sockets�A���~�T��: " << WSAGetLastError() << endl;
		return false;
	}

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
		cout << "[���~] �L�k�s�u�A���~�T��: " << WSAGetLastError() << endl;
		closesocket(sd);
		WSACleanup();
		return false;
	} else {
		return true;
	}
}

/*
 * Socket �s�u
 * @param str	=> �ǰe�����e
 * @return 		=> ���o�쪺��T
 */
content *winsock_service(const char str[MAXLINE]) {
	// receive content
	auto *result = new content;

	// init service
	if (!init_winsock_service(ip.c_str(), port)) {
		result->status = -1;
		return result;
	}

	// send status
	int send_status;

	// receive string
	char str_head[MAXLINE + 1] = "";
	char str_content[MAXLINE + 1] = "";

	// receive bytes
	int recv_head_len, recv_content_len;

	result->status = 0;

	// send "str" to echo server
	send_status = send(sd, str, int(strlen(str)) + 1, 0);

	if (send_status == SOCKET_ERROR) {
		cout << "[���~] �L�k�ǰe�T���A���~�T��: " << WSAGetLastError() << endl;

		result->status = -1;

		return result;
	}

	result->send = str;
	result->send_len = int(strlen(str) + 1);

	// receive http header
	recv_head_len = recv(sd, str_head, MAXLINE, 0);

	if (recv_head_len == SOCKET_ERROR) {
		cout << "[���~] �L�k�����T���A���~�T��: " << WSAGetLastError() << endl;

		result->status = -1;

		return result;
	}

	// receive http content
	recv_content_len = recv(sd, str_content, MAXLINE, 0);

	if (recv_content_len == SOCKET_ERROR) {
		cout << "[���~] �L�k�����T���A���~�T��: " << WSAGetLastError() << endl;

		result->status = -1;

		return result;
	}

	result->recv_head_len = recv_head_len;
	result->recv_head = str_head;

	result->recv_content_len = recv_content_len;
	result->recv_content = str_content;

	// close service
	finish_winsock_service();

	return result;
}

/*
 * ���� Windows socket �A��
 */
void finish_winsock_service() {
	// close socket
	if (closesocket(sd) == SOCKET_ERROR) {
		cout << "[���~] �L�k���� socket�A���~�T��: " << WSAGetLastError() << endl;
	}

	// finish "WinSock DLL"
	if (WSACleanup() == SOCKET_ERROR) {
		cout << "[���~] �L�k�פ�Windows Sockets�A���~�T��: " << WSAGetLastError() << endl;
	}
}

/*
 * �N���G��X
 * @param result	=> ���浲�G����
 */
void output(content *result) {
	//cout << "[�ǰe���e] " << result->send << "(" << result->send_len << "bytes)" << endl;
	cout << "[����] " << result->page << endl;
	//cout << "[�^�����Y] " << endl << result->recv_head << "(" << result->recv_head_len << "bytes)" << endl;
	cout << "[�^�����e] " << endl << result->recv_content << endl << "(" << result->recv_content_len << "bytes)" << endl << endl;
}

/*
 * �ˬd�����O�_���`�B�@(HTTP ���A�X�O�_�� 200 OK)
 * @param result	=> ���浲�G
 * @return			=> ���`�P�_
 */
bool check_http_status(content *result) {
	int pre = 9;
	size_t found = result->recv_head.find("\r\n");
	if (result->recv_head.substr(pre, found - pre) == "200 OK") {
		return true;
	}
	return false;
}

/*
 * �M�� href ���Ҥ�r
 * @param html	=> ���e
 * @param start	=> �}�l�M��B
 * @return 		=> �M�䵲�G���A
 */
int find_href_tag(const string &html, int start) {
	size_t found = html.find("href", start);
	if (found != std::string::npos) {
		return found;
	}
	return -1;
}

/*
 * �M�� href ���Ҫ��޸�
 * @param html	=> ���e
 * @param start	=> �}�l�M��B
 * @return 		=> �M�䵲�G���A
 */
int find_href_quot(const string &html, int start) {
	size_t found = html.find('"', start);
	if (found != std::string::npos) {
		return found;
	}
	return -1;
}

/*
 * �M���@ href ����
 * @param html	=> ���e
 * @param start	=> �}�l�M��B
 * @return 		=> �M�䵲�G href_struct ���c
 */
href_struct *find_href(const string &html, int start) {
	int href, head, foot;
	auto *result = new href_struct;

	// �M�� href ����
	href = find_href_tag(html, start);

	if (href == -1) {
		result->href = "";
		result->next = -1;
	} else {
		// �M�� href �᪺�Ĥ@�� "
		head = find_href_quot(html, href);

		// �M�� href �᪺�ĤG�� "
		foot = find_href_quot(html, head + 1);

		// ���o��� " ���������e
		result->href = html.substr(head + 1, foot - head - 1);

		// �U�@�Ӷ}�l�M�䪺��m
		result->next = foot + 1;
	}

	return result;
}