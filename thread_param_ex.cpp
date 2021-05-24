/*
 * NCYU 109 Network Programming
 * Week 14: create thread pass parameter exercise from 1 to 10
 * Created by linwebs on 2021/5/24.
 */
#include <iostream>
#include <winsock.h>

using namespace std;

void *thread_main(void *thread_arg);

/**
 * structure of arguments to pass to client thread
 */
struct thread_args {
	int c;
};

int main() {
	int thread_id;              // thread_id from CreateThread()
	thread_args *thread_arg;    // pointer to argument structure for thread

	thread_arg = new thread_args;

	for (int i = 1; i <= 10; i++) {

		thread_arg->c = i;

		//cout << "Hello World from main() pass: " << thread_arg->c << "." << endl;

		if (CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE) thread_main, thread_arg, 0, (LPDWORD) &thread_id) ==
			nullptr) {
			cout << "CreateThread() failed" << endl;
		} else {
			//cout << "Thread " << thread_id << " created." << endl;
		}
		Sleep(100);
	}

	free(thread_arg); // deallocate memory for argument

	return 0;
}

/**
 * Main program of a thread
 * @param thread_arg
 * @return
 */
void *thread_main(void *thread_arg) {
	int arg;

	arg = ((struct thread_args *) thread_arg)->c;

	cout << "Hello World from Thread with arg: " << arg << "." << endl;

	return nullptr;
}