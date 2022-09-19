//Seoyoon Park
//CECS 325-01
//Prog 1 - Solitaire Fibonacci
//09/19/2022
//
//I certify that this program is my own original work. I did not copy any part of this program from
//any other source. I further certify that I typed each and every line of code in this program.


#include <iostream>
using namespace std;
#include "Card.h"
#include "Deck.h"

enum MENU {
	menu_None,//0
	menu_NewDeck,//1
	menu_DisplayDeck,//2
	menu_ShuffleDeck,//3
	menu_PlaySolitaire,//4
	menu_Exit//5
};
int isFibo(int num) {
	int fibo[] = { 1,2,3,5,8,13,21,34,55,89,144,233,377 };
	for (int i = 0; i < 13; i++) {
		if (num == fibo[i]) {
			return 0;
			break;
		}
	}
	//else
	return num;
}
int main() {
	int cnt = 0;
	Deck d;
	

	cout << "Welcome to Fibonacci Solitaire!\n";
	while (1) {
		cout << "1) New Deck\n";
		cout << "2) Display Deck\n";
		cout << "3) Shuffle Deck\n";
		cout << "4) Play Solitaire\n";
		cout << "5) Exit\n";

		int imenu;
		cin >> imenu; //select menu
		if (imenu == menu_Exit)
			break;
		else if (imenu == menu_NewDeck) {
			cout << "New Deck\n\n";
			d.refreshDeck(); 
		}
		else if (imenu == menu_DisplayDeck) {
			cout << "Display Deck\n\n";
			d.display(); 
			cout << "\n";
		}
		else if (imenu == menu_ShuffleDeck) {
			cout << "Shuffle Deck\n\n";
			d.shuffle(); 
		}
		else if (imenu == menu_PlaySolitaire) {
			cout << "Playing Fibonacci Solitaire !!!\n\n";
			int sum = 0;
			int pile = 0;
			bool win = false;
			

			while (1) {
				if (d.isEmpty() != true) {
					Card c1 = d.deal();
					c1.display(); cout << ", ";
					sum += c1.getValue();
					if (isFibo(sum) == 0) {
						cout << "Fibo:" << sum << endl;
						sum = 0;
						pile++;
						if (d.isEmpty() == true) {
							win = true;
							cnt++;
							break;
						}
					}
				}
				else {
					cnt++;
					break;
				}
			}
			if (win == true) {
				cout << "\n" << "Winner in " << pile << " piles!\n\n";
				cout << "games played:" << cnt << "\n\n";
			}
			else if (win == false) {
				cout << "\n" << "Last hand value:" << sum << "\n";
				cout << "Loser in " << pile << " piles!\n\n";
			}
		}
		else
			cout << "You choose the wrong menu.\n\n";
	}

	return 0;
}