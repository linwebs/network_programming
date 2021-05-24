#include <cstdio>
#include <winsock.h>

int main() {
	SOCKET sd, clnt_sd1, clnt_sd2;
	WSADATA wsadata;
	struct sockaddr_in serv{}, clnt1{}, clnt2{};
	int i, n;
	char str[100];

	WSAStartup(0x101, &wsadata);
	sd = socket(AF_INET, SOCK_STREAM, 0);
	serv.sin_family = AF_INET;
	serv.sin_port = htons(1234);
	serv.sin_addr.s_addr = inet_addr("127.0.0.1");

	bind(sd, (struct sockaddr *) &serv, sizeof(serv));

	listen(sd, 5);

	int clnt_len1 = sizeof(clnt1);
	int clnt_len2 = sizeof(clnt2);

	printf("Server waits.\n");

	clnt_sd1 = accept(sd, (struct sockaddr *) &clnt1, &clnt_len1);
	printf("One client connects.\n");

	clnt_sd2 = accept(sd, (struct sockaddr *) &clnt2, &clnt_len2);
	printf("Two clients connect.\n");

	//enable non-blocking mode when iMode=1
	u_long iMode = 1;
	ioctlsocket(clnt_sd1, FIONBIO, &iMode);
	ioctlsocket(clnt_sd2, FIONBIO, &iMode);

	while (true) {
		n = recv(clnt_sd1, str, 100, 0);

		if (n > 0) {
			str[n] = '\0';
			printf("(1): %s\n", str);
			send(clnt_sd2, str, strlen(str) + 1, 0);
		}

		if (strcmp(str, "exit") == 0) {
			break;
		}

		n = recv(clnt_sd2, str, 100, 0);

		if (n > 0) {
			str[n] = '\0';
			printf("(2): %s\n", str);
			send(clnt_sd1, str, strlen(str) + 1, 0);
		}

		if (strcmp(str, "exit") == 0) {
			break;
		}

		Sleep(100);
	}

	closesocket(sd);
	closesocket(clnt_sd1);
	closesocket(clnt_sd2);
	WSACleanup();
}