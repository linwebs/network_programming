/*
 * NCYU 109 Network Programming mid 1 client
 * Created by linwebs on 2021/4/19.
 */
#include <stdio.h>
#include <winsock.h>
#define MAXSIZE 1024
int main(){
	WSADATA wsadata;
	struct sockaddr_in serv;
	SOCKET sd;
	char str[MAXSIZE];
	char str1[] = "time";
	char str2[] = "ask://8.8.8.8";
	char str3[] = "http://163.28.10.81";
	char str4[] = "end";
	WSAStartup(0x101, (WSADATA*) &wsadata); //
	sd = socket(AF_INET, SOCK_STREAM, 0);
	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv.sin_port = htons(1234);

	connect(sd,(struct sockaddr*) &serv,sizeof(serv));

	send(sd,str1,strlen(str1)+1,0);
	recv(sd,str,MAXSIZE,0);
	printf("(1) time: %s",str);

	send(sd,str2,strlen(str2)+1,0);
	recv(sd,str,MAXSIZE,0);
	printf("(2) 8.8.8.8's domain name: %s\n",str);

	send(sd,str3,strlen(str3)+1,0);
	recv(sd,str,MAXSIZE,0);
	printf("(3) 163.28.10.81's webpage: \n %s \n",str);

	send(sd,str4,strlen(str4)+1,0);
	recv(sd,str,MAXSIZE,0);
	printf("(4) %s",str);
	closesocket(sd);
	WSACleanup();
}