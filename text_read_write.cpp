/*
 * NCYU 109 Network Programming
 * Exercise 5: text read write
 * Created by linwebs on 2021/5/3.
 */
#include <iostream>
#include <cstdio>

using namespace std;

#define MAXSIZE 1024

int main() {
	FILE *file_in;
	FILE *file_out;

	char str[MAXSIZE];

	// read file
	file_in = fopen("in.txt", "rt");

	// write and overwrite the file
	file_out = fopen("out.txt", "w+t");

	// loop get string from file
	while (fgets(str, 10, file_in) != nullptr) {
		fputs(str, file_out);
	}

	// close file
	fclose(file_in);
	fclose(file_out);

	return 0;
}
