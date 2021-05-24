// simple TCP chat client(1)
// v2: two client chat through server

#include <cstdio>
#include <ctime>
#include <winsock.h>

int main() {
	SOCKET sd;
	WSADATA wsadata;
	struct sockaddr_in serv{};
	int i, n;
	char str[100] = "I love NP!";
	char str_name[100];
	clock_t t1, t2;
	int time_interval;

	WSAStartup(0x101, &wsadata);
	sd = socket(AF_INET, SOCK_STREAM, 0);

	serv.sin_family = AF_INET;
	serv.sin_port = htons(1234);
	serv.sin_addr.s_addr = inet_addr("127.0.0.1");

	connect(sd, (struct sockaddr *) &serv, sizeof(serv));
	printf("Connect to server.\n");

	//enable non-blocking mode when iMode=1
	u_long iMode = 1;
	ioctlsocket(sd, FIONBIO, &iMode);

	printf("Client name:");
	gets(str_name);

	printf("Time Interval(sec):");

	scanf("%d", &time_interval);
	Sleep(5000);

	t2 = 0;
	long time;

	while (true) {
		t1 = clock();
		time = (t1 - t2) / CLOCKS_PER_SEC;

		if (time > time_interval) {
			strcpy(str, str_name);
			printf("[Client]: %s\n", str);
			send(sd, str, strlen(str) + 1, 0);

			t2 = clock();

		}

		memset(str, 0, 100);
		n = recv(sd, str, 100, 0);

		if (n > 0) {
			str[n] = '\0';
			printf("[Other]:%s\n", str);
		}

		if (strcmp(str, "exit") == 0) {
			break;
		}

		Sleep(100);
	}

	closesocket(sd);
	WSACleanup();
}