#include<cstdio>
#include<winsock.h>

#define MAXRECV 1024
#define MAXCLI 10

int main() {
	WSADATA wsadata;
	SOCKET serv_sd, new_socket, cli_sd[MAXCLI];
	struct sockaddr_in serv{}, cli{};

	int activity, cli_len, n, client_num = 0;
	int ready_to_send[MAXCLI];
	fd_set readfds, writefds;  //set of socket descriptors
	char str[MAXRECV];

	TIMEVAL timeout{};

	for (int i = 0; i < MAXCLI; i++) {
		ready_to_send[i] = 0;
		cli_sd[i] = 0;
	}

	WSAStartup(0x101, &wsadata); //呼叫 WSAStartup() 註冊 WinSock DLL 的使用

	serv_sd = socket(AF_INET, SOCK_STREAM, 0);// 開啟 TCP socket

	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = INADDR_ANY;
	serv.sin_port = htons(5678);

	bind(serv_sd, (LPSOCKADDR) &serv, sizeof(serv));

	listen(serv_sd, 3);

	while (true) {
		printf("[1]clear the socket fd set. \n");
		FD_ZERO(&readfds);
		FD_ZERO(&writefds);

		printf("[2]add server socket to fd set \n");
		FD_SET(serv_sd, &readfds);

		printf("[2]add client socket to fd set \n");
		for (int i = 0; i < MAXCLI; i++) {
			if (cli_sd[i] > 0) {
				if (ready_to_send[i] == 0) {
					FD_SET(cli_sd[i], &readfds);
				} else {
					FD_SET(cli_sd[i], &writefds);
				}
			}
		}

		// wait for an activity on any of the sockets, timeout is NULL , so wait indefinitely
		printf("[3]call select() and waiting \n");

		// set timeout
		timeout.tv_sec = 5;
		timeout.tv_usec = 0;

		activity = select(0, &readfds, &writefds, NULL, &timeout);

		printf("[4]wake up from select():%d\n", activity);

		if (activity == SOCKET_ERROR) {
			printf("select call failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}

		if (activity == 0) {
			printf("select() is waiting for 5 sec.\n");
		}

		// check serv_sd->accept(), add new client into cli_sd[]
		if (FD_ISSET(serv_sd, &readfds)) {
			cli_len = sizeof(cli);
			new_socket = accept(serv_sd, (struct sockaddr *) &cli, (int *) &cli_len);
			printf("New connection: socket fd: %d, ip: %s, port: %d\n", new_socket, inet_ntoa(cli.sin_addr), ntohs(cli.sin_port));

			for (int i = 0; i < MAXCLI; i++) {
				if (cli_sd[i] == 0) {
					cli_sd[i] = new_socket;
					client_num++;
					printf("The %d client socket is in cli_sd[%d]\n", client_num, i);
					break;
				}
			}
		}

		// check each cli_sd client present in read sockets
		for (int i = 0; i < MAXCLI; i++) {
			if (FD_ISSET(cli_sd[i], &readfds)) {
				n = recv(cli_sd[i], str, MAXRECV, 0);

				if (n == SOCKET_ERROR) {
					int error_code = WSAGetLastError();
					if (error_code == WSAECONNRESET) {
						// somebody disconnected, get his details and print
						printf("Host disconnected unexpectedly\n");

						closesocket(cli_sd[i]);
						cli_sd[i] = 0;
						client_num--;
					} else {
						printf("recv failed with error code: %d", error_code);
					}
				}

				if (n == 0) {
					// somebody disconnected, get his details and print
					printf("Host disconnected\n");

					closesocket(cli_sd[i]);
					cli_sd[i] = 0;
					client_num--;
				}

				if (n > 0) {
					printf("recv from cli[%d]: %s\n", i, str);
					ready_to_send[i] = 1;
				}

			}

			if (FD_ISSET(cli_sd[i], &writefds)) {
				send(cli_sd[i], str, int(strlen(str) + 1), 0);
				ready_to_send[i] = 0;
			}
		}
	}// while

	closesocket(serv_sd);

	WSACleanup();
	system("pause");

	return 0;
}