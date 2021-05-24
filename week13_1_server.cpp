#include<cstdio>
#include<winsock.h>

#define MAXRECV 1024

int main() {
	WSADATA wsadata;
	SOCKET serv_sd, cli_sd;
	struct sockaddr_in serv{}, cli{};

	int max_clients = 30, activity, cli_len, i, n;
	fd_set readfds;  //set of socket descriptors
	char str[MAXRECV];

	WSAStartup(0x101, &wsadata); //呼叫 WSAStartup() 註冊 WinSock DLL 的使用

	serv_sd = socket(AF_INET, SOCK_STREAM, 0);// 開啟 TCP socket

	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = INADDR_ANY;
	serv.sin_port = htons(5678);

	bind(serv_sd, (LPSOCKADDR) &serv, sizeof(serv));

	listen(serv_sd, 3);

	cli_len = sizeof(cli);
	printf("TCP Server waits for client\n");

	cli_sd = accept(serv_sd, (LPSOCKADDR) &cli, &cli_len);
	printf("Client is connected: socket fd is %d , ip is : %s , port : %d \n", cli_sd, inet_ntoa(cli.sin_addr), ntohs(cli.sin_port));

	while (true) {
		printf("[1]clear the socket fd set. \n");
		FD_ZERO(&readfds);

		printf("[2]add client socket to fd set \n");
		FD_SET(cli_sd, &readfds);

		//wait for an activity on any of the sockets, timeout is NULL , so wait indefinitely
		printf("[3]call select() and waiting \n");

		activity = select(0, &readfds, NULL, NULL, NULL);

		printf("[4]wake up from select():%d\n", activity);

		if (activity == SOCKET_ERROR) {
			printf("select call failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}

		//if client 1 presend in read sockets
		if (FD_ISSET(cli_sd, &readfds)) {
			n = recv(cli_sd, str, MAXRECV, 0);
			printf("recv from client: %s \n", str);
			if (n <= 0) {
				printf("connection closed.\n");
				break;
			}
		}
	}// while

	closesocket(serv_sd);
	closesocket(cli_sd);

	WSACleanup();
	system("pause");

	return 0;
}