/*
 * NCYU 109 Network Programming
 * Chat room client multiple thread client
 * Created by linwebs on 2021/5/24.
 */
#include <iostream>
#include <cstring>
#include <winsock.h>

#define MAX_LINE 1024

using namespace std;

void *thread_main(void *thread_arg);

/**
 * structure of arguments to pass to client thread
 */
struct thread_args {
	SOCKET sd;
};

int main() {
	SOCKET sd;
	char str[MAX_LINE];
	sockaddr_in server{};               // local address
	WSADATA wsadata;                    // structure for WinSock setup communication
	int thread_id;                      // thread_id from CreateThread()
	thread_args *thread_arg;            // pointer to argument structure for thread
	int conn_status;
	int send_status;

	// Call WSAStartup() to Register "WinSock DLL"
	WSAStartup(0x101, (LPWSADATA) &wsadata);

	sd = socket(AF_INET, SOCK_STREAM, 0);
	thread_arg = new thread_args;
	thread_arg->sd = sd;

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_port = htons(5678);

	// connect to server
	conn_status = connect(sd, (LPSOCKADDR) &server, sizeof(server));
	if (conn_status == SOCKET_ERROR) {
		cout << "connect() failed" << endl;
	}

	if (CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE) thread_main, thread_arg, 0, (LPDWORD) &thread_id) ==
		nullptr) {
		cout << "thread_create() failed" << endl;
	}

	while (true) {
		cin >> str;

		send_status = send(sd, str, int(strlen(str) + 1), 0);    // send to server
		if (send_status == SOCKET_ERROR) {
			cout << "send() failed" << endl;
			break;
		}
		cout << "send: " << str << endl;
	}

	// finish "WinSock DLL"
	WSACleanup();

	return 0;
}

/**
 * Main program of a thread
 * @param thread_arg
 * @return
 */
void *thread_main(void *thread_arg) {
	SOCKET sd;
	char str[MAX_LINE];
	int recv_status;

	sd = ((struct thread_args *) thread_arg)->sd;

	while (true) {
		recv_status = recv(sd, str, MAX_LINE, 0);    // receive data from server
		if (recv_status < 0) {
			cout << "recv() failed" << endl;
			break;
		}
		cout << "recv: " << str << endl;
	}

	// close TCP socket
	closesocket(sd);
	WSACleanup();

	free(thread_arg);

	return nullptr;
}