/*
 * NCYU 109 Network Programming
 * Week 14: create thread
 * Created by linwebs on 2021/5/24.
 */
#include <iostream>
#include <winsock.h>

using namespace std;

void *thread_main();

int main() {
	int thread_id;    // thread_id from CreateThread()

	cout << "Hello World from main()." << endl;

	if (CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE) thread_main, nullptr, 0, (LPDWORD) &thread_id) == nullptr) {
		cout << "CreateThread() failed." << endl;
	} else {
		cout << "Thread " << thread_id << " created." << endl;
	}
	Sleep(1000);

	return 0;
}

/**
 * Main program of a thread
 * @return null
 */
void *thread_main() {
	cout << "Hello World from Thread!" << endl;
	return nullptr;
}