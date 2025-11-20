/**
 * @file game.c
 * @brief Implementation of game initialization and runtime helpers
 *
 * Implements functions declared in game.h for creating full decks,
 * creating shuffled multi-pack hidden decks, dealing cards, finding
 * playable cards, checking for game end, and transferring played
 * cards back to the hidden deck when it becomes empty.
 *
 * Uses the CardDeck API (addCardToTop, removeCardFromTop,
 * getCardAtIndex, removeCardAtIndex, getDeckSize, etc.) and the
 * shuffleDeck() function from deck_operations.h.
 *
 * @author Adam McCarthy
 * @date 20/11/2025
 */

#include <stdlib.h>
#include "game.h"

/**
 * @brief Creates a standard 52-card deck in order
 * 
 * Generates a complete deck of 52 playing cards with all combinations
 * of suits (CLUBS, HEARTS, SPADES, DIAMONDS) and ranks (TWO through ACE).
 * Cards are added to the deck in suit-major, rank-minor order.
 * 
 * @param fullDeck Pointer to CardDeck structure to populate with cards
 * @return void
 * 
 * @note If fullDeck is NULL, function returns immediately without action
 * @warning Deck must be initialized before calling this function
 */
void createFullDeck(CardDeck* fullDeck) {
    // Check for null pointer
    if (fullDeck == NULL) return;

    /* Iterate through all suits from CLUBS to DIAMONDS */
    for (int s = CLUBS; s <= DIAMONDS; ++s) {
        /* Iterate through all ranks from TWO to ACE */
        for (int r = TWO; r <= ACE; ++r) {
            // Create card and add to top of deck
            Card c = createCard((Suit)s, (Rank)r);
            addCardToTop(fullDeck, c);
        }
    }
}

/**
 * @brief Creates a shuffled deck composed of multiple standard decks
 * 
 * Clears any existing cards from the hidden deck, then adds the specified
 * number of full 52-card decks. The combined deck is then shuffled
 * using Fisher-Yates algorithm or equivalent.
 * 
 * @param hiddenDeck Pointer to CardDeck structure to populate with shuffled cards
 * @param numPacks Number of standard 52-card decks to combine and shuffle
 * @return void
 * 
 * @note If hiddenDeck is NULL or numPacks <= 0, function returns immediately
 * @see shuffleDeck()
 */
void createShuffledMultiDeck(CardDeck* hiddenDeck, int numPacks) {
    // Validate input parameters
    if (hiddenDeck == NULL || numPacks <= 0) return;

    /* Clear any existing cards from the deck */
    while (getDeckSize(hiddenDeck) > 0) {
        (void) removeCardFromTop(hiddenDeck);
    }

    /* Add multiple full decks to create a larger combined deck */
    for (int i = 0; i < numPacks; ++i) {
        createFullDeck(hiddenDeck);
    }

    /* Shuffle the combined multi-deck using Fisher-Yates algorithm */
    shuffleDeck(hiddenDeck);
}

/**
 * @brief Deals cards from hidden deck to both players
 * 
 * Distributes 8 cards to each player alternately from the hidden deck.
 * If the hidden deck becomes empty during dealing, the function stops
 * dealing additional cards.
 * 
 * @param hiddenDeck Pointer to the deck containing cards to be dealt
 * @param player1 Pointer to first player's hand deck
 * @param player2 Pointer to second player's hand deck
 * @return void
 * 
 * @note All deck pointers must be valid and initialized
 * @warning Function will stop dealing if hidden deck becomes empty mid-deal
 */
void dealCards(CardDeck* hiddenDeck, CardDeck* player1, CardDeck* player2) {
    // Validate all input parameters
    if (hiddenDeck == NULL || player1 == NULL || player2 == NULL) return;

    /* Deal 8 cards to each player alternately */
    for (int i = 0; i < 8; ++i) {
        // Check if hidden deck has cards before dealing to player 1
        if (getDeckSize(hiddenDeck) == 0) return;
        Card c1 = removeCardFromTop(hiddenDeck);
        addCardToTop(player1, c1);

        // Check if hidden deck has cards before dealing to player 2
        if (getDeckSize(hiddenDeck) == 0) return;
        Card c2 = removeCardFromTop(hiddenDeck);
        addCardToTop(player2, c2);
    }
}

/**
 * @brief Finds the first playable card in a player's hand
 * 
 * Searches through the player's hand from top to bottom (index 0 to size-1)
 * to find the first card that can be played on the current top card.
 * 
 * @param player Pointer to the player's hand deck to search
 * @param topCard Pointer to the current top card on the play pile
 * @return Index of the first playable card, or -1 if no playable card found
 * 
 * @note Returns the first playable card found (lowest index)
 * @see canPlayCard()
 */
int findPlayableCard(const CardDeck* player, const Card* topCard) {
    // Validate input parameters
    if (player == NULL || topCard == NULL) return -1;

    int size = getDeckSize(player);

    /* Iterate through all cards in player's hand */
    for (int i = 0; i < size; ++i) {
        Card* c = getCardAtIndex(player, i);
        // Check if card exists and can be played on top card
        if (c != NULL && canPlayCard(c, topCard)) {
            return i;  // Return index of first playable card
        }
    }
    return -1;  // No playable card found
}

/**
 * @brief Checks if the game has ended
 * 
 * Determines if the game should end by checking if either player
 * has no cards left in their hand.
 * 
 * @param player1 Pointer to first player's hand deck
 * @param player2 Pointer to second player's hand deck
 * @return 1 if game is over (either player has empty hand), 0 otherwise
 * 
 * @note Returns 1 (game over) if either player pointer is NULL
 * @note Game ends when any player runs out of cards
 */
int isGameOver(const CardDeck* player1, const CardDeck* player2) {
    // Check for null pointers or empty hands
    if (player1 == NULL || player2 == NULL) return 1;
    if (getDeckSize(player1) == 0 || getDeckSize(player2) == 0) return 1;
    return 0;  // Game continues
}

/**
 * @brief Transfers played cards (except last) to hidden deck and shuffles
 * 
 * Moves all but the most recently played card from the played deck
 * to the hidden deck, then shuffles the hidden deck. This is typically
 * called when the hidden deck becomes empty during gameplay.
 * 
 * @param playedDeck Pointer to the deck containing played cards
 * @param hiddenDeck Pointer to the hidden deck to receive transferred cards
 * @return void
 * 
 * @note The most recent card (top of played deck) remains in played deck
 * @note If played deck has 0 or 1 cards, no transfer occurs
 * @see shuffleDeck()
 */
void transferPlayedToHidden(CardDeck* playedDeck, CardDeck* hiddenDeck) {
    // Validate input parameters
    if (playedDeck == NULL || hiddenDeck == NULL) return;

    int size = getDeckSize(playedDeck);

    /* If played deck has 0 or 1 cards, nothing to transfer */
    if (size <= 1) return;

    /* Move all but last card from played deck to hidden deck */
    while (getDeckSize(playedDeck) > 1) {
        // Remove from bottom of played deck (index 0) and add to top of hidden deck
        Card c = removeCardAtIndex(playedDeck, 0);
        addCardToTop(hiddenDeck, c);
    }

    /* Shuffle the newly populated hidden deck */
    shuffleDeck(hiddenDeck);
}

