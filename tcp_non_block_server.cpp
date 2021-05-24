#include <cstdio>
#include <cstring>
#include <winsock.h>

#define MAXLINE 1024    /* 字串緩衝區長度 */

int main() {
	SOCKET serv_sd, cli_sd;        /* socket 描述子 */
	int cli_len, n;
	char str[MAXLINE];
	bool exit = false;

	struct sockaddr_in serv, cli{};
	WSADATA wsadata;

	WSAStartup(0x101, &wsadata); //呼叫 WSAStartup() 註冊 WinSock DLL 的使用

	serv_sd = socket(AF_INET, SOCK_STREAM, 0);// 開啟 TCP socket

	//指定 socket 的 IP 位址和 port number
	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = 0;
	serv.sin_port = htons(5678);    // 指定 IPPORT_ECHO 為 echo port

	bind(serv_sd, (LPSOCKADDR) &serv, sizeof(serv));

	listen(serv_sd, 5); //呼叫 listen() 使 socket 進入「監聽」狀態

	cli_len = sizeof(cli);

	while (true) {
		printf("server: waiting for client\n");

		cli_sd = accept(serv_sd, (LPSOCKADDR) &cli, &cli_len);

		//enable non-blocking mode when iMode=1
		u_long iMode = 1;
		ioctlsocket(cli_sd, FIONBIO, &iMode);

		if (iMode == 0)
			printf("This is blocking mode.\n");
		else
			printf("This is non-blocking mode.\n");

		while (true) {
			printf("recv() checks.\n");
			n = recv(cli_sd, str, MAXLINE, 0);
			str[n] = '\0';

			if (n > 0)
				printf("Recv: %s\n", str);        // 顯示從 client 傳來的字串

			if (strcmp(str, "exit") == 0) {
				exit = true;
				printf("exit");
				break;
			}

			Sleep(1000);

			int nError = WSAGetLastError();
			if (nError != WSAEWOULDBLOCK && nError != 0) {
				printf("Disconnected! error code:%d\n", nError);
				closesocket(cli_sd);
				break;
			}
		}

		if (exit) {
			break;
		}
	}

	//結束 WinSock DLL 的使用
	closesocket(serv_sd);
	closesocket(cli_sd);
	WSACleanup();
}