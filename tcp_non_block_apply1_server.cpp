#include <cstdio>
#include <ctime>
#include <winsock.h>

int main() {
	SOCKET sd, clnt_sd;
	WSADATA wsadata;
	struct sockaddr_in serv{}, clnt{};
	int i, n;
	char str[100];
	clock_t t1, t2;
	bool exit = false;
	int status = 0;


	WSAStartup(0x101, &wsadata);
	sd = socket(AF_INET, SOCK_STREAM, 0);
	serv.sin_family = AF_INET;
	serv.sin_port = htons(1234);
	serv.sin_addr.s_addr = inet_addr("127.0.0.1");

	status = bind(sd, (struct sockaddr *) &serv, sizeof(serv));
	printf("bind status: %d\n", status);

	status = listen(sd, 5);
	printf("listen status: %d\n", status);

	int clnt_len = sizeof(clnt);
	printf("Server waits.\n");

	//while (true) {

		clnt_sd = accept(sd, (struct sockaddr *) &clnt, &clnt_len);
		printf("Client is connected.\n");

		//enable non-blocking mode when iMode=1
		u_long iMode = 1;
		ioctlsocket(clnt_sd, FIONBIO, &iMode);

		t2 = 0;
		long time;

		while (true) {
			n = recv(clnt_sd, str, 100, 0);

			if (n > 0) {
				str[n] = '\0';
				printf("(client): %s\n", str);
			}

			t1 = clock();

			time = (t1 - t2) / CLOCKS_PER_SEC;

			//printf("time: %ld\n", time);

			if (time > 5) {
				strcpy(str, "I know.");
				printf("(server): %s\n", str);
				send(clnt_sd, str, strlen(str) + 1, 0);
				t2 = clock();
				Sleep(800);
			}

			if (strcmp(str, "exit") == 0) {
				exit = true;
				break;
			}
		}

		/*if (exit) {
			break;
		}
	}*/

	closesocket(sd);
	closesocket(clnt_sd);
	WSACleanup();
}