#include <iostream>
#include <stdio.h>
#include <winsock.h>
using namespace std;

int main(void){

char domain[]="";
//initial WSAStartup
WSADATA 		wsadata;

int nResult=WSAStartup(0x101,(LPWSADATA) &wsadata); // �I�s WSAStartup() ���U WinSock DLL ���ϥ�
if(nResult!=0)
{
	printf("WSA Initialization failed: %d\n",nResult);
	WSACleanup();
	return 0;
}


//gethostbyaddr()
printf("What is 104.94.49.230's domain name?\n");
LPHOSTENT hp;

struct in_addr sAddr;
sAddr.s_addr=inet_addr("140.130.1.23");

hp=gethostbyaddr((LPSTR) &sAddr, sizeof(sAddr),AF_INET);

if(hp==NULL)
    //printf("get hp error, code:%d\n",WSAGetLastError());
    cout << "get hp error, code:" << WSAGetLastError() << endl;
else{
    printf("host name:%s\n",hp->h_name);
    printf("host nickname:%s\n",hp->h_aliases[0]);
    printf("host IP:%s\n\n",inet_ntoa(*(LPIN_ADDR)(hp->h_addr)));
}

}
