/**
 * @file deck_operations.c
 * @brief 
 *
 * Implements functions declared in deck_operations.h to be used when shuffling and sorting decks.
 *
 * Uses the CardDeck functions createDeck, addCardToTop, removeCardFromTop, etc. from deck.h.
 * 
 * @author Gearóid Corrigan
 * @date 22/11/2025
 */

#include <stdlib.h>
#include <time.h>
#include "deck.h"


 /**
  * @brief Shuffles deck CardDeck using Fisher-Yates algorithm
  *
  * Generates a complete deck of 52 playing cards with all combinations
  * of suits (CLUBS, HEARTS, SPADES, DIAMONDS) and ranks (TWO through ACE).
  * Cards are added to the deck in suit-major, rank-minor order.
  *
  * @param deck Pointer to CardDeck structure to shuffle
  * @return void
  *
  * @note If deck is NULL or if the deck has 1 or less cards, function returns immediately without action
  */

void shuffleDeck(CardDeck* deck) 		// FISHER-YATES SHUFFLE ALGORITHM
{
	if (deck == NULL || deck->size <= 1)	// IN CASE OD EMPTY DECK OR SINGLE CARD
		return;
	CardDeck* shuffledDeck = createDeck();		// CREATE NEW EMPTY DECK
	if (shuffledDeck == NULL) {		// CHECK ALLOCATION
		fprintf(stderr, "Error: Failed to create shuffled deck.\n");	// ALLOCATION FAILED
		return;
	}
	while (deck->size > 0) {
		int r = rand() % deck->size;	// RANDOM INDEX BETWEEN 0 AND size-1
		Card c = removeCardAtIndex(deck, r-1);	// REMOVE CARD AT INDEX r
		addCardToTop(shuffledDeck, c);		// ADD CARD TO TOP OF SHUFFLED DECK
	}
	// TRANSFER SHUFFLED CARDS BACK TO ORIGINAL DECK
	while (shuffledDeck->size > 0) {
		Card c = removeCardFromTop(shuffledDeck);	// REMOVE TOP CARD FROM SHUFFLED DECK
		addCardToTop(deck, c);		// ADD CARD TO TOP OF ORIGINAL DECK
	}
	destroyDeck(shuffledDeck);	// FREE SHUFFLED DECK MEMORY
}


/**
 * @brief sorts deck CardDeck using Insertion Sort algorithm
 *
 * @param deck Pointer to CardDeck structure to sort
 * @return void
 *
 * @note If deck is NULL or if the deck has 1 or less cards, function returns immediately without action
 */
void sortDeck(CardDeck* deck) 		// INSERTION SORT ALGORITHM
{
	if (deck == NULL || deck->size <= 1)	// IN CASE OF EMPTY DECK OR SINGLE CARD
		return;
	for (int i = 1; i < deck->size; ++i) {	// ITERATE THROUGH DECK
		Card sorting = deck->cards[i];	// CURRENT CARD TO INSERT "SORTING"
		int j = i - 1;	// INDEX OF PREVIOUS CARD
		while (j >= 0 && compareCards(&deck->cards[j], &sorting) > 0) {		// COMPARE CARDS
			deck->cards[j + 1] = deck->cards[j];	// SHIFT CARD RIGHT
			j--;	// MOVE TO PREVIOUS CARD 
		}
		deck->cards[j + 1] = sorting;	// INSERT KEY CARD AT CORRECT POSITION
	}
}
