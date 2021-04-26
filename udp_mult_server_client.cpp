/*
 * NCYU 109 Network Programming udp multiple client client
 * Created by linwebs on 2021/4/26.
 */
#include <iostream>
#include <winsock.h>

#define MAXLINE 1024
#define SEND_TIMES 10

using namespace std;

SOCKET sd;
WSADATA wsadata;
struct sockaddr_in serv1{};
struct sockaddr_in serv2{};

char str1[MAXLINE] = "I love NP!";
char str2[MAXLINE] = "I love Algorithm!";

// server's ip address
const char server1_ip[16] = "127.0.0.1";
const char server2_ip[16] = "127.0.0.1";

// server's port number
u_short server1_port = 5678;
u_short server2_port = 5679;

// server bytes
int serv1_len;
int serv2_len;

// send status
int send_status;


int send_to_1(char str[MAXLINE]);

int send_to_2(char str[MAXLINE]);

int main() {

	// Call WSAStartup() to Register "WinSock DLL"
	WSAStartup(0x101, (WSADATA *) &wsadata);

	// Open a TCP socket
	sd = socket(AF_INET, SOCK_DGRAM, 0);

	// Prepare for connect.
	// Include sockaddr_ing struct (serv)
	serv1.sin_family = AF_INET;
	serv2.sin_family = AF_INET;

	// server's ip address
	serv1.sin_addr.s_addr = inet_addr(server1_ip);
	serv2.sin_addr.s_addr = inet_addr(server2_ip);

	// server's port number
	// htons: host to network
	serv1.sin_port = htons(server1_port);
	serv2.sin_port = htons(server2_port);

	serv1_len = sizeof(serv1);
	serv2_len = sizeof(serv2);

	for (int i = 0; i < SEND_TIMES; i++) {

		send_to_1(str1);

		Sleep(500);

		send_to_2(str2);

		Sleep(500);
	}

	char exit_char[MAXLINE] = "exit";

	send_to_1(exit_char);
	Sleep(500);
	send_to_2(exit_char);

	// close UDP socket
	closesocket(sd);

	// finish "WinSock DLL"
	WSACleanup();

	//system("pause");

	return 0;
}

int send_to_1(char str[MAXLINE]) {
	// send to server 1
	send_status = sendto(sd, str, int(strlen(str) + 1), 0, reinterpret_cast<const sockaddr *>(&serv1), serv1_len);

	if (send_status == SOCKET_ERROR) {
		cout << "send to function failed with error: " << WSAGetLastError() << endl;
		closesocket(sd);
		WSACleanup();
		return 1;
	}

	cout << "Send to " << server1_port << " port: " << str << endl;
}

int send_to_2(char str[MAXLINE]) {
	// send to server 1
	send_status = sendto(sd, str, int(strlen(str) + 1), 0, reinterpret_cast<const sockaddr *>(&serv2), serv2_len);

	if (send_status == SOCKET_ERROR) {
		cout << "send to function failed with error: " << WSAGetLastError() << endl;
		closesocket(sd);
		WSACleanup();
		return 1;
	}

	cout << "Send to " << server2_port << " port: " << str << endl;
}