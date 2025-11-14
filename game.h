/**
 * @file deck_operations.h
 * @brief Game initialization and setup functions
 *
 * This module provides algorithms for shuffling and sorting decks of cards.
 *
 * @author
 * @date
 */

 // uses: shuffleDeck()
 // - createFullDeck()
 // - All functions from deck.h
 // - compareCards() from card.h

#ifndef GAME_H
#define GAME_H

#include "deck_operations.h"  // Requires shuffleDeck from deck_operations.h

 /**
  * @brief Creates a complete deck of 52 standard cards
  *
  * Creates one of each card combination:
  * - All four suits (CLUBS, SPADES, HEARTS, DIAMONDS)
  * - All thirteen ranks (TWO through ACE)
  *
  * @param fullDeck Pointer to the deck to fill with 52 cards
  *
  * @note Deck should be created in sorted order (by suit, then by rank)
  * @note Uses createCard() for each card and addCardToTop() to build the deck
  */
void createFullDeck(CardDeck* fullDeck);

/**
 * @brief Creates and shuffles a deck containing multiple packs of cards
 *
 * @param hiddenDeck Pointer to the deck to initialize (will be overwritten)
 * @param numPacks Number of complete 52-card packs to include
 *
 * @note Creates numPacks complete decks, combines them, then shuffles
 * @note Uses createFullDeck() and shuffleDeck() functions
 * @example If numPacks=2, creates 104 cards total
 */
void createShuffledMultiDeck(CardDeck* hiddenDeck, int numPacks);

/**
 * @brief Deals 8 cards to each player from the hidden deck
 *
 * Dealing order:
 * - First card to player1, second to player2, third to player1, etc.
 * - Continue until each player has 8 cards total
 *
 * @param hiddenDeck Pointer to the deck to deal from (will be modified)
 * @param player1 Pointer to first player's hand deck
 * @param player2 Pointer to second player's hand deck
 *
 * @note Uses removeCardFromTop() from hiddenDeck and addCardToTop() to player hands
 * @note Assumes hiddenDeck has at least 16 cards
 */
void dealCards(CardDeck* hiddenDeck, CardDeck* player1, CardDeck* player2);

/**
 * @brief Finds first playable card in player's hand
 *
 * @param player Pointer to player's hand deck
 * @param topCard Pointer to current top card on played deck
 * @return int Index of playable card, or -1 if no card can be played
 *
 * @note Uses canPlayCard() for each card in hand
 * @note Returns first matching card according to game rules
 */
int findPlayableCard(const CardDeck* player, const Card* topCard);

/**
 * @brief Checks if game is over (any player has empty hand)
 *
 * @param player1 Pointer to first player's hand
 * @param player2 Pointer to second player's hand
 * @return int 1 if game over, 0 otherwise
 */
int isGameOver(const CardDeck* player1, const CardDeck* player2);

/**
 * @brief Transfers played cards to hidden deck when hidden deck is empty
 *
 * Transfers all cards from played deck to hidden deck except the last card,
 * which remains in played deck as the new top card.
 *
 * @param playedDeck Pointer to the played deck (will be reduced to one card)
 * @param hiddenDeck Pointer to the hidden deck (will receive all but last played card)
 *
 * @note Used when hidden deck becomes empty during game
 * @note After transfer, hidden deck is shuffled
 */
void transferPlayedToHidden(CardDeck* playedDeck, CardDeck* hiddenDeck);

#endif // GAME_H