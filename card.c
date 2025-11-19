/**
* @file card.c
* @brief Implementation of Card operations
*/

#include <stdio.h>
#include "card.h"

/* Lookup tables for printing */
static const char* suitNames[] = {
	"CLUBS",
	"SPADES",
	"HEARTS",
	"DIAMONDS"
};

static const char* rankNames[] = {
	"TWO",
	"THREE",
	"FOUR",
	"FIVE",
	"SIX",
	"SEVEN",
	"EIGHT",
	"NINE",
	"TEN",
	"JACK",
	"QUEEN",
	"KING",
	"ACE"
};

Card createCard(Suit suit, Rank rank) {
	Card c;
	c.suit = suit;
	c.rank = rank;
	return c;
}

void printCard(const Card* card) {
	if (card == NULL) {
		printf("NULL Card\n");
		return;
	}

	printf("%s-%s", suitNames[card->suit], rankNames[card->rank]);
}

int compareCards(const Card* card1, const Card* card2) {
	if (card1 == NULL || card2 == NULL)
		return 0;

	/* First compare suits */
	if (card1->suit != card2->suit)
		return card1->suit - card2->suit;

	/* Suits are the same, compare ranks */
	return card1->rank - card2->rank;
}

int canPlayCard(const Card* playerCard, const Card* topCard) {
	if (playerCard == NULL || topCard == NULL)
		return 0;

	/* Playable if suit OR rank matches */
	if (playerCard->suit == topCard->suit)
		return 1;

	return 0;
}
