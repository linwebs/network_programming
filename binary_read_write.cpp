/*
 * NCYU 109 Network Programming
 * Exercise 6: binary write
 * Created by linwebs on 2021/5/3.
 */
#include <iostream>
#include <cstdio>

using namespace std;

#define MAXSIZE 30000

int main() {
	FILE *file_in;
	FILE *file_out;

	char buffer[MAXSIZE];

	int file_size = 0;

	// read file
	file_in = fopen("in.jpg", "rb");

	// write and overwrite the file
	file_out = fopen("out.jpg", "w+b");

	// loop get binary from file
	while (true) {
		// read file
		file_size = fread(buffer, 1, MAXSIZE, file_in);

		cout << "file size: " << file_size << endl;

		if (file_size <= 0) {
			break;
		}

		fwrite(buffer, 1, file_size, file_out);
	}

	// close file
	fclose(file_in);
	fclose(file_out);

	return 0;
}
