#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
#include "Deck.h"

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