/*
 * NCYU 109 Network Programming HW1
 * Created by Linwebs on 2021/3/8.
 *
 * Test Input:
 * 140.130.41.11 140.130.41.13
 *
 * Test Output:
 * 140.130.41.11's host name: mxdns.ncyu.edu.tw
 * 140.130.41.12's host name: 041012.cc.ncyu.edu.tw
 * 140.130.41.13's host name: 041013.cc.ncyu.edu.tw
 */

#include <iostream>
#include <string>
#include <winsock.h>

using namespace std;

void output_all_host_name(int start, int stop, string pre);

void output_host_name(string ip_addr);

int get_ip_pre_local(char *ip);

string get_ip_pre(char *ip);

int get_class_d(char *ip);

int main() {
	string ip_pre;
	char ip_start_c[16], ip_stop_c[16];
	int ip_start_num, ip_stop_num;
	cin >> ip_start_c >> ip_stop_c;

	// 取得起始IP位址的Class D
	ip_start_num = get_class_d(ip_start_c);

	// 取得結束IP位址的Class D
	ip_stop_num = get_class_d(ip_stop_c);

	// 取得IP位址Class D前面的部分
	ip_pre = get_ip_pre(ip_start_c);

	// 輸出所有查詢結果
	output_all_host_name(ip_start_num, ip_stop_num, ip_pre);
	return 0;
}

/*
 * 輸出所有查詢結果
 * int start	=> 起始IP位址的Class D
 * int stop		=> 起始IP位址的Class D
 * string pre	=> IP位址Class D前面的部分
 */
void output_all_host_name(int start, int stop, string pre) {
	string ip_addr;
	for (int i = start; i <= stop; i++) {
		ip_addr = pre + to_string(i);
		output_host_name(ip_addr);
	}
}

/*
 * 輸出單一查詢結果
 * string ip_addr	=> 要查詢的IP位址
 */
void output_host_name(string ip_addr) {
	WSADATA wsadata;
	int n_result = WSAStartup(0x101, (LPWSADATA) &wsadata);
	struct in_addr sAddr;

	LPHOSTENT hp;

	if (n_result != 0) {
		// 初始化失敗: 輸出錯誤代碼
		cout << "WSA Initialization failed: " << n_result;
		WSACleanup();
		return;
	}

	// 帶入IP位址 (char array 型態)
	sAddr.s_addr = inet_addr(ip_addr.c_str());

	// 由IP位址取得hostname
	hp = gethostbyaddr((LPSTR) &sAddr, sizeof(sAddr), AF_INET);

	if (hp == NULL) {
		// 未取得到結果
		switch (WSAGetLastError()) {
			case 11004:
				cout << "WSA Error: Valid name, no data record of requested type." << endl;
				break;
			default:
				cout << "WSA Error: " << WSAGetLastError() << endl;
				break;
		}
	} else {
		cout << ip_addr << "'s host name: " << hp->h_name << endl;
	}
}

/*
 * 取得IP位址Class D的起始位置
 * char *ip	=> IP位址
 */
int get_ip_pre_local(char *ip) {
	int i = 0, count_dot = 0;
	while (true) {
		if (ip[i] == '.') {
			count_dot++;
			if (count_dot == 3) {
				return i;
			}
		}
		i++;
	}
}

/*
 * 取得IP位址Class D前的部分
 * char *ip	=> IP位址
 */
string get_ip_pre(char *ip) {
	string ip_str = "";
	for (int i = 0; i <= get_ip_pre_local(ip); i++) {
		ip_str += ip[i];
	}
	return ip_str;
}

/*
 * 取得IP位址Class D的部分
 * char *ip	=> IP位址
 */
int get_class_d(char *ip) {
	bool do_loop = true;
	int i = 0, count_dot = 0, num = 0;
	while (do_loop) {
		if (ip[i] == '.') {
			count_dot++;
			if (count_dot == 3) {
				while (true) {
					i++;
					if (ip[i] != '\0') {
						num = num * 10 + (ip[i] - 48);
					} else {
						do_loop = false;
						break;
					}
				}
			}
		}
		i++;
	}
	return num;
}