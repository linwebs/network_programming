/*
 * NCYU 109 Network Programming
 * Chat room client multiple thread server
 * Created by linwebs on 2021/5/24.
 */
#include <iostream>
#include <winsock.h>

#define MAX_CLIENT 2

using namespace std;

void *thread_main(void *thread_arg);

/**
 * structure of arguments to pass to client thread
 */
struct thread_args {
	int client_sock[MAX_CLIENT];        // socket descriptor for client
};

int main() {
	int thread_id;                      // thread_id from CreateThread()
	thread_args *thread_arg;            // pointer to argument structure for thread
	int server_sock;                    // socket descriptor for server
	int client_sock[MAX_CLIENT];        // socket descriptor for client
	WSADATA wsadata;                    // structure for WinSock setup communication
	sockaddr_in server_addr{};          // local address
	sockaddr_in client_addr{};          // client address
	int client_length;                  // length of client address data structure

	// load Winsock 2.0 DLL
	if (WSAStartup(0x101, &wsadata) != 0) {
		cout << "WSAStartup() failed" << endl;
		exit(1);
	}

	// create socket for incoming connections
	if ((server_sock = int(socket(PF_INET, SOCK_STREAM, IPPROTO_TCP))) < 0) {
		cout << "socket() failed" << endl;
	}

	// construct local address structure
	memset(&server_addr, 0, sizeof(server_addr));     // zero out structure
	server_addr.sin_family = AF_INET;                      // internet address family
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);       // any incoming interface
	server_addr.sin_port = htons(5678);           // local port

	// bind to the local address
	if (bind(server_sock, (struct sockaddr *) &server_addr, sizeof server_addr) < 0) {
		cout << "bind() failed" << endl;
	}

	// mark the socket so it will listen for incoming connections
	if (listen(server_sock, 3) < 0) {
		cout << "listen() failed" << endl;
	}

	while (true) {

		cout << "Server is waiting for clients." << endl;

		client_length = sizeof(client_addr);

		// wait for a client to connect
		for (int i = 0; i < MAX_CLIENT; i++) {
			if ((client_sock[i] = int(accept(server_sock, (struct sockaddr *) &client_addr, &client_length))) <= 0) {
				cout << "accept() failed" << endl;
			} else {
				cout << "accept [" << i << "]" << endl;
			}
		}

		// create separate memory for client argument
		thread_arg = new thread_args;

		for (int i = 0; i < MAX_CLIENT; i++) {
			thread_arg->client_sock[i] = client_sock[i];
		}


		if (CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE) thread_main, thread_arg, 0, (LPDWORD) &thread_id) ==
			nullptr) {
			cout << "thread_create() failed" << endl;
			//break;
		}

		cout << "New chat room with thread ID: " << thread_id;

		for (int i = 0; i < MAX_CLIENT; i++) {
			cout << " and ";
			if (i == 0) {
				cout << "sockets: ";
			}
			cout << thread_arg->client_sock[i];
		}
		cout << endl;
	}

	return 0;
}

/**
 * Main program of a thread
 * @param thread_arg
 * @return
 */
void *thread_main(void *thread_arg) {
	int client_sock[MAX_CLIENT];    // socket descriptor for client connection

	// extract socket file descriptor from argument
	for (int i = 0; i < MAX_CLIENT; i++) {
		client_sock[i] = ((struct thread_args *) thread_arg)->client_sock[i];
	}

	char buffer[1000];    // buffer for echo string
	int recv_msg_size;    // size of received message

	u_long mode = 1;

	// set non blocking
	for (int i = 0; i < MAX_CLIENT; i++) {
		ioctlsocket(client_sock[i], FIONBIO, &mode);
	}

	int wsa_error;
	bool exit_loop = false;

	// send received string and receive again until end of transmission
	while (true) {
		for (int i = 0; i < MAX_CLIENT; i++) {
			if ((recv_msg_size = recv(client_sock[i], buffer, 1000, 0)) > 0) {
				for (int j = 0; j < MAX_CLIENT; j++) {
					if (j != i) {
						send(client_sock[j], buffer, int(strlen(buffer) + 1), 0);
					}
				}
			}

			wsa_error = WSAGetLastError();

			if (wsa_error != WSAEWOULDBLOCK && wsa_error != 0) {
				cout << "Disconnected! error code: " << wsa_error << endl;
				exit_loop = true;
				break;
			}
		}

		if (exit_loop) {
			break;
		}

		Sleep(1000);
	}

	for (int i = 0; i < MAX_CLIENT; i++) {
		closesocket(client_sock[i]);    // close client socket
	}

	free(thread_arg);

	return nullptr;
}