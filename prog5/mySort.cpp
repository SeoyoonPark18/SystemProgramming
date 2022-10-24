//Seoyoon Park
//CECS 325-01
//Prog 5 - Sorting Contest using Threads (threading with thread)
//10/24/2022
//
//I certify that this program is my own original work. I did not copy any part of this program from
//any other source. I further certify that I typed each and every line of code in this program.

#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <iostream>
#include <unistd.h>
#include <fstream>
using namespace std;

const int MAX = 1000000;
int v[MAX];
int m[MAX];

// quick sort using an array
void quick(int start, int end) {
	if (start >= end)
		return;
	int pivot = start;
	int i = pivot + 1;
	int j = end;
	int temp;

	while (i <= j) {
		while (i <= end && v[i] <= v[pivot])
			i++;
		while (j > start && v[j] >= v[pivot])
			j--;
		if (i > j) {
			temp = v[j];
			v[j] = v[pivot];
			v[pivot] = temp;
		}
		else {
			temp = v[i];
			v[i] = v[j];
			v[j] = temp;
		}
	}
	quick(start, j - 1);
	quick(j + 1, end);
}

// Create a structure to pass parameters
struct num {
	//int *arr;
	int left;
	int right;
};

void sort_numbers(num arg) {
	//num arg = arr;
	quick(arg.left, arg.right);
	//return NULL;
}

// Merge two sections in a array in sorted order to another array
void merge_numbers(int a, int b, int cnt) {
	int i = 0;
	int j = 0;
	int k = a;

	while (i < cnt && j < cnt) {
		if (v[a] <= v[b]) {
			m[k] = v[a];
			k++; a++; i++;
		}
		else {
			m[k] = v[b];
			k++; b++; j++;
		}
	}
	if (i >= cnt) {
		while (j < cnt) {
			m[k] = v[b];
			k++; b++; j++;
		}
	}
	else {
		while (i < cnt) {
			m[k] = v[a];
			k++; a++; i++;
		}
	}
}



int main(int argc, char* argv[]) {
	if (argc < 3)
	{
		cout << "Please include input filename and output filename in param list.\n";
		exit(EXIT_SUCCESS);
	}
	cout << "\n" << "Sorting array using threads";

	ofstream fout;
	ifstream fin;
	int n;
	int count = 0;
	fin.open(argv[1]); //open numbers.txt
	while (fin >> n) {
		v[count++] = n;
	}

	num argList[8]; // array of arguments to pass to each thread
	for (int i = 0; i < 8; i++) {
		//argList[i].arr = v;
		argList[i].left = i * 125000;
		argList[i].right = (i + 1) * 125000 - 1;
	}


	thread thread0(sort_numbers, argList[0]);
	thread thread1(sort_numbers, argList[1]);
	thread thread2(sort_numbers, argList[2]);
	thread thread3(sort_numbers, argList[3]);
	thread thread4(sort_numbers, argList[4]);
	thread thread5(sort_numbers, argList[5]);
	thread thread6(sort_numbers, argList[6]);
	thread thread7(sort_numbers, argList[7]);


	thread0.join();
	thread1.join();
	thread2.join();
	thread3.join();
	thread4.join();
	thread5.join();
	thread6.join();
	thread7.join();


	//merge
	merge_numbers(argList[0].left, argList[1].left, MAX / 8);
	merge_numbers(argList[2].left, argList[3].left, MAX / 8);
	merge_numbers(argList[4].left, argList[5].left, MAX / 8);
	merge_numbers(argList[6].left, argList[7].left, MAX / 8);
	for (int i = 0; i < MAX; i++) {
		v[i] = m[i];
	}
	merge_numbers(argList[0].left, argList[2].left, MAX / 4);
	merge_numbers(argList[4].left, argList[6].left, MAX / 4);
	for (int i = 0; i < MAX; i++) {
		v[i] = m[i];
	}
	merge_numbers(argList[0].left, argList[4].left, MAX / 2);


	fout.open(argv[2], ios::out | ios::trunc);
	for (int i = 0; i < MAX; i++) {
		fout << m[i] << "\n";
	}
	fout.close();

	fin.close();
	return 0;
}