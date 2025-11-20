/**
 * @file deck.h
 * @brief Dynamic CardDeck abstract data type and operations
 *
 * This module defines an abstract data type for a dynamic deck of cards
 * that can grow/shrink as needed. Implementation details are hidden.
 *
 * @author warda 
 * @date 20th November 2025 
 */

 // uses: Card type, printCard()

#ifndef DECK_CORE_H
#define DECK_CORE_H

#include "card.h"  // Requires Card type from card.h

 /**
  * @struct CardDeck
  * @brief Opaque type for dynamic collection of cards
  *
  * The actual implementation is hidden - users can only interact
  * with CardDeck through the provided interface functions.
  */
typedef struct CardDeck CardDeck;

/**
 * @brief Creates a new empty deck
 *
 * @return CardDeck* Pointer to newly created deck, NULL on failure
 *
 * @note Uses dynamic memory allocation
 * @note Must be destroyed with destroyDeck()
 */
CardDeck* createDeck(void);

/**
 * @brief Destroys a deck and frees all memory
 *
 * @param deck Pointer to the deck to destroy
 *
 * @warning After calling this, the deck pointer becomes invalid
 */
void destroyDeck(CardDeck* deck);

/**
 * @brief Adds a card to the top of the deck
 *
 * @param deck Pointer to the deck to modify
 * @param card The card to add to the top
 *
 * @note Handles internal memory reallocation if needed
 */
void addCardToTop(CardDeck* deck, Card card);

/**
 * @brief Removes and returns the card from the top of the deck
 *
 * @param deck Pointer to the deck to modify
 * @return Card The card that was removed from the top
 *
 * @warning Do not call on an empty deck
 */
Card removeCardFromTop(CardDeck* deck);

/**
 * @brief Gets a pointer to the card at a specific index
 *
 * @param deck Pointer to the deck to access
 * @param index The index of the card to retrieve (0 = bottom, size-1 = top)
 * @return Card* Pointer to the card, NULL if index invalid
 *
 * @note This does NOT remove the card, just provides access
 * @warning The returned pointer becomes invalid if deck is modified
 */
Card* getCardAtIndex(const CardDeck* deck, int index);

/**
 * @brief Removes and returns a card from a specific position
 *
 * @param deck Pointer to the deck to modify
 * @param index The index of the card to remove
 * @return Card The card that was removed
 *
 * @warning Do not call with invalid index
 */
Card removeCardAtIndex(CardDeck* deck, int index);

/**
 * @brief Returns the current number of cards in the deck
 *
 * @param deck Pointer to the deck to check
 * @return int Number of cards in the deck
 */
int getDeckSize(const CardDeck* deck);

/**
 * @brief Prints all cards in the deck to console
 *
 * @param deck Pointer to the deck to print
 *
 * @note Prints cards in order from bottom to top
 * @note Uses printCard() function for each card
 */
void printDeck(const CardDeck* deck);

/**
 * @brief Moves card from one deck to another
 *
 * @param fromDeck Pointer to source deck
 * @param toDeck Pointer to destination deck
 * @param index Index of card to move in source deck
 */
void moveCardBetweenDecks(CardDeck* fromDeck, CardDeck* toDeck, int index);

#endif // DECK_H
