// simple TCP chat client(2)
// v2: two client chat through server

#include <cstdio>
#include <winsock.h>

int main() {
	SOCKET sd;
	WSADATA wsadata;
	struct sockaddr_in serv{};
	int i, n;
	char str[100] = "I love NP!";

	WSAStartup(0x101, &wsadata);
	sd = socket(AF_INET, SOCK_STREAM, 0);

	serv.sin_family = AF_INET;
	serv.sin_port = htons(1234);
	serv.sin_addr.s_addr = inet_addr("127.0.0.1");

	connect(sd, (struct sockaddr *) &serv, sizeof(serv));
	printf("Connect to server.\n");

	while (true) {
		memset(str, 0, 100);
		recv(sd, str, 100, 0);
		printf("[Client 1]:%s\n", str);
		printf("[Client 2]:");
		gets(str);
		send(sd, str, strlen(str) + 1, 0);

		if (strcmp(str, "exit") == 0) {
			break;
		}
	}

	closesocket(sd);
	WSACleanup();
}