/**
 * @file deck_operations.h
 * @brief Dynamic CardDeck abstract data type and operationsAlgorithms for deck manipulation (shuffling and sorting)
 * 
 * This module provides algorithms for shuffling and sorting decks of cards.
 *
 * @author
 * @date
 */

 // uses: All functions from  deck.h
 // - compareCards() из card.h (for sorting)

#ifndef DECK_OPERATIONS_H
#define DECK_OPERATIONS_H

#include "deck.h"  // Requires CardDeck type from deck_core.h

 /**
  * @brief Shuffles a deck using the algorithm specified in the assignment
  *
  * Algorithm from assignment:
  * 1. Create a second empty deck
  * 2. While original deck has cards:
  *    a. Generate random number r between 1 and current deck size
  *    b. Remove the r-th card from original deck (0-indexed: position r-1)
  *    c. Add this card to the beginning of the second deck
  * 3. Replace original deck with the shuffled second deck
  *
  * @param deck Pointer to the deck to shuffle
  *
  * @note Uses rand() function for random number generation
  * @note Remember to call srand(time(NULL)) once in main() before using this
  */
void shuffleDeck(CardDeck* deck);

/**
 * @brief Sorts a deck of cards using Insertion Sort algorithm
 *
 * Sorting order as defined in compareCards():
 * - First by suit: CLUBS < SPADES < HEARTS < DIAMONDS
 * - Then by rank: TWO < THREE < ... < ACE
 *
 * @param deck Pointer to the deck to sort
 *
 * @note Uses Insertion Sort
 * @note Algorithm complexity: O(n²) but efficient for small decks  
 * @note Sort is stable (preserves order of equal cards)
 */
void sortDeck(CardDeck* deck);

#endif // DECK_OPERATIONS_H