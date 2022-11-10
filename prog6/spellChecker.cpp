//Seoyoon Park
//CECS 325-01
//Prog 6 - Spell Checker
//11/09/2022
//
//I certify that this program is my own original work. I did not copy any part of this program from
//any other source. I further certify that I typed each and every line of code in this program.

#include <iostream>
#include <regex>
#include <fstream>
#include <string>
#include <map>
#include <vector>
using namespace std;

int main(int argc, char *argv[]) {
	string word;
	map<string, int> d; //dictionary
	map<string, int> book;

	ifstream fin;
	fin.open(argv[1]); //open dictionary.txt
	while (fin >> word) {
		//d.push_back(word);
		d.insert({ word,0 });
	}
	fin.close();

	regex reg("^[a-z]+\'*[a-z]+");  // this will match any word with 0 or more apostophes
	regex quotes("\"");
	regex punc("[!?]");
	regex marks("[.,;:()]");
	smatch match;

	fin.open(argv[2]); //open words.txt
	while (fin >> word)
	{
		int n = 1;
		word = regex_replace(word, quotes, "");
		word = regex_replace(word, punc, "");
		word = regex_replace(word, marks, "");
		if (regex_search(word, match, reg)) {
			for (int i = 0; i < word.length(); i++) {
				word[i] = tolower(word[i]); // change string to lower case
			}

			auto it = book.find(word);
			if (it != book.end()) {
				book[word] += 1;
			}
			else {
				book.insert({ word,n });
			}
		}
	}

	int cnt = 0;
	for (map<string, int>::iterator it = book.begin(); it != book.end(); it++) {
		auto iter = d.find(it->first);
		if (iter != d.end()) { //if find
			book[it->first] = 0;
		}
		else {
			cnt++;
		}
	}

	cout << "Misspelled words: " << "(" << cnt << ")" << "\n";
	while (!book.empty()) {
		if (book.begin()->second != 0) {
			cout << book.begin()->first << " - " << book.begin()->second << "\n";
		}
		book.erase(book.begin());
	}
	fin.close();
	return 0;
}