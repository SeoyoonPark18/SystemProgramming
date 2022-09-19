//Seoyoon Park
//CECS 325-01
//Prog 2 - Fibonacci Solitaire (single file)
//09/19/2022
//
//I certify that this program is my own original work. I did not copy any part of this program from
//any other source. I further certify that I typed each and every line of code in this program.


#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class Card {
private:
	char rank;
	char suit;
public:
	Card();
	Card(char r, char s);
	void setCard(char r, char s);
	int getValue();
	void display();
};
Card::Card() {}
Card::Card(char r, char s) {
	rank = r;
	suit = s;
}
void Card::setCard(char r, char s) {
	rank = r;
	suit = s;
}
int Card::getValue() {
	int value = 0;
	if (rank == 'A') value = 1;
	else if (rank == '2') value = 2;
	else if (rank == '3') value = 3;
	else if (rank == '4') value = 4;
	else if (rank == '5') value = 5;
	else if (rank == '6') value = 6;
	else if (rank == '7') value = 7;
	else if (rank == '8') value = 8;
	else if (rank == '9') value = 9;
	else if (rank == 't') value = 10;
	else if (rank == 'J') value = 10;
	else if (rank == 'Q') value = 10;
	else if (rank == 'K') value = 10;

	return value;
}
void Card::display() {
	if (rank == 't') //if rank is 10
		cout << "10" << suit;
	else
		cout << rank << suit;

}

class Deck {
private:
	Card store[52];
	int used[52];
public:
	Deck();
	void refreshDeck();
	Card deal();
	void shuffle();
	bool isEmpty();
	void display();
};
Deck::Deck() { //creates a deck of 52 cards	
	char ranks[13] = { 'A', '2', '3', '4', '5', '6', '7', '8', '9', 't', 'J', 'Q', 'K' };
	char suits[4] = { 'S', 'H', 'D', 'C' };
	int num = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 13; j++) {
			store[num] = Card(ranks[j], suits[i]);
			used[num] = 0;
			num++;
		}
	}
}
void Deck::refreshDeck() { //reset the deck	
	char ranks[13] = { 'A', '2', '3', '4', '5', '6', '7', '8', '9', 't', 'J', 'Q', 'K' };
	char suits[4] = { 'S', 'H', 'D', 'C' };
	int num = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 13; j++) {
			Card c;
			c.setCard(ranks[j], suits[i]);
			store[num] = c;
			used[num] = 0;
			num++;
		}
	}
}
Card Deck::deal() {
	for (int i = 51; i >= 0; i--) {
		if (used[i] != -1) { //-1 means the card is used
			used[i] = -1;
			return store[i];
			break;
		}
	}
}
void Deck::shuffle() {
	srand(time(NULL));
	for (int i = 0; i < 52; i++) {
		int a = i + (rand() % (52 - i));
		swap(store[i], store[a]);
	}
}
bool Deck::isEmpty() {
	for (int i = 51; i >= 0; i--) {
		if (used[i] != -1) { //-1 means the card is used
			return false; //deck is not empty
			break;
		}
		else if (used[0] == -1) {
			return true; //deck is now empty
			break;
		}
	}
}
void Deck::display() { //display deck in 13 columns and 4 rows
	int num = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 13; j++) {
			store[num].display();
			cout << " ";
			num++;
		}
		cout << "\n";
	}
}

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