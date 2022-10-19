//Seoyoon Park
//CECS 325-01
//Prog 4 - Sorting Contest using Threads
//10/19/2022
//
//I certify that this program is my own original work. I did not copy any part of this program from
//any other source. I further certify that I typed each and every line of code in this program.

#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char * argv[]) {

	ifstream fin;
	fin.open(argv[1]);

	const int MAX = 1000000;
	int arr[MAX];
	int n;
	int count = 0;
	while (fin >> n)
	{
		arr[count++] = n;
	}
	cout << "\n";
	for (int i = 1; i < MAX; i++) {
		if (arr[i] < arr[i - 1]) {
			cout << "Error. Array is not sorted.\n";
			break;
		}
	}
	cout << "Total " <<count <<" numbers in the array.\n" <<"Array is in sorted order.\n";

	return 0;
}