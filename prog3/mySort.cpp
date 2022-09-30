//Seoyoon Park
//CECS 325-01
//Prog 3 - Sorting Contest
//10/03/2022
//
//I certify that this program is my own original work. I did not copy any part of this program from
//any other source. I further certify that I typed each and every line of code in this program.

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

// quick sort using an array
void quick(int v[], int start, int end) {
	
	if (start >= end)
		return;

	int pivot = start;
	int left = start;
	int right = end + 1;

	do {
		do {
			left++;
		} while ((left <= end) && (v[pivot] > v[left]));
		do {
			right--;
		} while ((right >= start) && (v[pivot] < v[right]));
		if (left < right) {
			int temp = v[left];
			v[left] = v[right];
			v[right] = temp;
		}
	} while (left < right);

	int temp = v[right];
	v[right] = v[pivot];
	v[pivot] = temp;

	quick(v, start, right - 1);
	quick(v, right + 1, end);
	
	
}


int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		cout << "Please include input filename and output filename in param list.\n";
		cout << "Example:\n";
		cout << "     % mySort numbers.txt sortedQ.txt\n";
		exit(EXIT_SUCCESS);
	}

	const int MAX = 1000000;
	ofstream fout;
	ifstream fin;
	int n;

	int v[MAX];
	int count = 0;

	fin.open(argv[1]);
	
	while (fin >> n)
	{
		v[count++] = n;	// insert a number into the arary and increase the index
	}

	cout << "Starting Array quick sort with " << count << " items\n";
	quick(v, 0, count);	 // call the quickSort function
	

		fout.open(argv[2], ios::out | ios::trunc);
		for (int i = 0; i < count; i++) {
			fout << v[i] << endl;
		}
		

		fout.close();
	fin.close();
		return 0;
}
