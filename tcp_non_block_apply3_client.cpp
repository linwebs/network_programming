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
		n = recv(sd, str, 100, 0);

		if (n == 0) {
			break;
		}

		printf("Recv: %s\n", str);
	}

	closesocket(sd);
	WSACleanup();
}