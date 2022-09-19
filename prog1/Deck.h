#ifndef DECK_H
#define DECK_H
#include "Card.h"
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
#endif