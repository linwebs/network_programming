/*
 * NCYU 109 Network Programming
 * Week 14: multiple thread exchange data
 * Created by linwebs on 2021/5/24.
 */
#include <iostream>
#include <winsock.h>

using namespace std;

void *thread_add(void *thread_arg);

void *thread_sub(void *thread_arg);

/**
 * structure of arguments to pass to client thread
 */
struct thread_args {
	int a;
	int b;
	int c;
};

int main() {
	// thread_id from CreateThread()
	int thread_id_add;
	int thread_id_sub;

	// pointer to argument structure for thread
	thread_args *thread_arg;

	thread_arg = new thread_args;

	thread_arg->a = 5;
	thread_arg->b = 3;

	cout << "Hello World from main()." << endl;

	// thread_add
	if (CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE) thread_add, thread_arg, 0, (LPDWORD) &thread_id_add) ==
		nullptr) {
		cout << "CreateThread() failed" << endl;
	} else {
		cout << "Thread " << thread_id_add << " created." << endl;
	}
	Sleep(1);

	// thread_sub
	if (CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE) thread_sub, thread_arg, 0, (LPDWORD) &thread_id_sub) ==
		nullptr) {
		cout << "CreateThread() failed" << endl;
	} else {
		cout << "Thread " << thread_id_sub << " created." << endl;
	}
	Sleep(30);

	free(thread_arg); // deallocate memory for argument

	return 0;
}

/**
 * Main program of a thread_add
 * @param thread_arg
 * @return
 */
void *thread_add(void *thread_arg) {
	int i, j, k;

	i = ((struct thread_args *) thread_arg)->a;
	j = ((struct thread_args *) thread_arg)->b;

	k = i + j;
	((struct thread_args *) thread_arg)->c = k;

	// Sleep(30);

	cout << i << " + " << j << " = " << ((struct thread_args *) thread_arg)->c << endl;

	return nullptr;
}

/**
 * Main program of a thread_sub
 * @param thread_arg
 * @return
 */
void *thread_sub(void *thread_arg) {
	int i, j, k;

	i = ((struct thread_args *) thread_arg)->a;
	j = ((struct thread_args *) thread_arg)->b;

	k = i - j;
	((struct thread_args *) thread_arg)->c = k;

	cout << i << " - " << j << " = " << ((struct thread_args *) thread_arg)->c << endl;

	return nullptr;
}