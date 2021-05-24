#include <cstdio>
#include <cstring>
#include <winsock.h>

#define MAXLINE 1024

int main() {

	SOCKET sd;
	struct sockaddr_in serv{};
	char str[1024] = "How are you?";
	WSADATA wsadata;

	WSAStartup(0x101, (LPWSADATA) &wsadata); // 呼叫 WSAStartup() 註冊 WinSock DLL 的使用

	sd = socket(AF_INET, SOCK_STREAM, 0); //開啟一個 TCP socket.

	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv.sin_port = htons(5678);

	connect(sd, (LPSOCKADDR) &serv, sizeof(serv)); // 連接至 echo server
	printf("Client has connected to Server.\n");

	while (true) {  //每隔10秒，週期送出
		Sleep(10000);
		send(sd, str, int(strlen(str) + 1), 0);
		printf("Send: %s (in 10 secs)\n", str);

		if (strcmp(str, "exit") == 0) {
			break;
		}
	}
	closesocket(sd); //關閉TCP socket
	WSACleanup();  // 結束 WinSock DLL 的使用
	return 0;
}