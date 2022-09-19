#ifndef CARD_H
#define CARD_H

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
#endif