/*
 * NCYU 109 Network Programming
 * Server multiple thread server
 * Created by linwebs on 2021/5/24.
 */
#include <iostream>
#include <winsock.h>

#define MAX_CLIENT 10

using namespace std;

void *thread_main(void *thread_arg);

/**
 * structure of arguments to pass to client thread
 */
struct thread_args {
	int client_index;
	int client_sock[MAX_CLIENT];        // socket descriptor for client
	int client_total;
	int sock;
};

int main() {
	int thread_id;                      // thread_id from CreateThread()
	thread_args *thread_arg;            // pointer to argument structure for thread
	int server_sock;                    // socket descriptor for server
	int sock;                           // socket descriptor for client
	WSADATA wsadata;                    // structure for WinSock setup communication
	sockaddr_in server_addr{};          // local address
	sockaddr_in client_addr{};          // client address
	int client_length;                  // length of client address data structure

	thread_arg = new thread_args;

	for (int &i : thread_arg->client_sock) {
		i = 0;
	}
	thread_arg->client_total = 0;

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

	cout << "Server is waiting for clients." << endl;

	while (true) {
		client_length = sizeof(client_addr);
		int i;
		for (i = 0; i < MAX_CLIENT; i++) {
			if (thread_arg->client_sock[i] == 0) {
				break;
			}
		}
		thread_arg->client_index = i;

		// wait for a client to connect
		if ((sock = int(accept(server_sock, (struct sockaddr *) &client_addr, &client_length))) <= 0) {
			cout << "accept() failed" << endl;
		}

		thread_arg->sock = sock;
		thread_arg->client_sock[i] = sock;
		thread_arg->client_total++;

		// create separate memory for client argument
		if (CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE) thread_main, thread_arg, 0, (LPDWORD) &thread_id) ==
			nullptr) {
			cout << "thread_create() failed" << endl;
		}

		cout << "New client with thread ID: " << thread_id << " and socket: " << thread_arg->client_sock[i] << " (Current Client: " << thread_arg->client_total << ")" << endl;
	}

	free(thread_arg);

	return 0;
}

/**
 * Main program of a thread
 * @param thread_arg
 * @return
 */
void *thread_main(void *thread_arg) {
	//int client_sock[MAX_CLIENT];    // socket descriptor for client connection
	//int client_total;
	int client_index;
	int client_sock_i;

	// extract socket file descriptor from argument
	client_sock_i = ((struct thread_args *) thread_arg)->sock;
	client_index = ((struct thread_args *) thread_arg)->client_index;

	char buffer[1000];    // buffer for echo string
	int recv_msg_size;    // size of received message

	// send received string and receive again until end of transmission
	while (true) {
		recv_msg_size = recv(client_sock_i, buffer, 1000, 0);
		if (recv_msg_size <= 0) {
			((struct thread_args *) thread_arg)->client_total--;
			((struct thread_args *) thread_arg)->client_sock[client_index] = 0;
			cout << "Connection[socket: " << client_sock_i << "] closed.(Current Client: " << ((struct thread_args *) thread_arg)->client_total << ")" << endl;
			break;
		}
		send(client_sock_i, buffer, int(strlen(buffer) + 1), 0);
	}

	closesocket(client_sock_i);    // close client socket
	((struct thread_args *) thread_arg)->client_sock[client_index] = 0;

	return nullptr;
}