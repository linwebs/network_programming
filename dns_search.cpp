#include <iostream>
#include <string>
#include <winsock.h>

#define USING_CIN true
using namespace std;

int main(int argc, char *argv[]) {
	WSADATA wsadata;
	int n_result = WSAStartup(0x101, (LPWSADATA) &wsadata);
	struct in_addr sAddr;
	LPHOSTENT hp;
	char ip_addr[16];
	if (n_result != 0) {
		cout << "WSA Initialization failed: " << n_result;
		WSACleanup;
		return 0;
	}

	if (USING_CIN) {
		// using cin
		cout << "Input an IP address: ";
		cin >> ip_addr;
	} else {
		// using argv
		if (argc > 1) {
			strcpy(ip_addr, argv[1]);
		} else {
			strcpy(ip_addr, "140.130.41.11");
		}
	}

	sAddr.s_addr = inet_addr(ip_addr);

	try {
		hp = gethostbyaddr((LPSTR) &sAddr, sizeof(sAddr), AF_INET);
	} catch (exception &e) {
		cout << e.what() << endl;
	}

	if (hp == NULL) {
		cout << "WSA Error: " << WSAGetLastError() << endl;
	} else {
		cout << ip_addr << "'s domain name: " << hp->h_name << endl;
		if (hp->h_aliases[0] != nullptr) {
			for(int i=0; hp->h_aliases[i]; i++) {
				cout << "nickname: " << hp->h_aliases[i] << endl;
			}
		} else {
			cout << "nickname: (NULL)" << endl;
		}
		cout << "ip addr: " << inet_ntoa(*(LPIN_ADDR) (hp->h_addr));
	}
	return 0;
}
