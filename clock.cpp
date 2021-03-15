/*
 * Created by linwebs on 2021/3/14.
 */
#include <iostream>
#include <ctime>

using namespace std;

int main() {
	int start = clock();
	int stop = clock();

	cout << "start time: " << start << endl;
	cout << "stop  time: " << stop << endl;
	cout << "total time: " << stop - start << endl;
	return 0;
}