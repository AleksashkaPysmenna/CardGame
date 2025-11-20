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
typedef struct CardDeck;
    Card* cards;
    int size;     
    int capacity;  
};
/**
 * @brief Creates a new empty deck
 *
 * @return CardDeck* Pointer to newly created deck, NULL on failure
 *
 * @note Uses dynamic memory allocation
 * @note Must be destroyed with destroyDeck()
 */
CardDeck* createDeck(void);
void createDeck(Card* deck) {
    char* ranks[NUM_RANKS] = {
        "Ace", "2", "3", "4", "5", "6", "7",
        "8", "9", "10", "Jack", "Queen", "King"
    };
    char* suits[NUM_SUITS] = {
        "Hearts", "Diamonds", "Clubs", "Spades"
    };

/**
 * @brief Destroys a deck and frees all memory
 *
 * @param deck Pointer to the deck to destroy
 *
 * @warning After calling this, the deck pointer becomes invalid
 */
void destroyDeck(CardDeck* deck);
{
    if (deck == NULL)
        return;

    /* Free the dynamic card array first */
    free(deck->cards);

    /* Now free the deck structure itself */
    free(deck);
}
/**
 * @brief Adds a card to the top of the deck
 *
 * @param deck Pointer to the deck to modify
 * @param card The card to add to the top
 *
 * @note Handles internal memory reallocation if needed
 */
void addCardToTop(CardDeck* deck, Card card);
{
    if (deck == NULL)
        return;

    /* If array is full, grow it */
    if (deck->size == deck->capacity) {

        /* Increase capacity (double, or start at 4) */
        int newCapacity = (deck->capacity == 0) ? 4 : deck->capacity * 2;

        Card* newArray = realloc(deck->cards, newCapacity * sizeof(Card));
        if (newArray == NULL) {
            /* Allocation failure — keep deck unchanged */
            fprintf(stderr, "Error: Failed to expand card deck memory.\n");
            return;
        }

        deck->cards = newArray;
        deck->capacity = newCapacity;
    }

    /* Add the card at position size (top of deck) */
    deck->cards[deck->size] = card;
    deck->size++;
}

};
/**
 * @brief Removes and returns the card from the top of the deck
 *
 * @param deck Pointer to the deck to modify
 * @return Card The card that was removed from the top
 *
 * @warning Do not call on an empty deck
 */
Card removeCardFromTop(CardDeck* deck);
{
    /* Do NOT call on empty deck: caller's responsibility */
    if (deck == NULL || deck->size == 0) {
        fprintf(stderr, "Error: removeCardFromTop() called on empty or NULL deck.\n");
        Card empty = { CLUB, TWO }; /* Safe fallback, should not be used */
        return empty;
    }

    /* Top card is at index size - 1 */
    Card removed = deck->cards[deck->size - 1];

    deck->size--;   /* Reduce deck size */

    return removed; /* Return the card */
}

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
{
    if (deck == NULL)
        return NULL;

    /* Check index range: 0 = bottom, size-1 = top */
    if (index < 0 || index >= deck->size)
        return NULL;

    /* Return pointer to card inside the internal array */
    return &deck->cards[index];
}
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
{
    /* Defensive check — although header warns user */
    if (deck == NULL || deck->size == 0 || index < 0 || index >= deck->size) {
        fprintf(stderr, "Error: removeCardAtIndex() called with invalid index.\n");
        Card empty = { CLUB, TWO }; /* harmless fallback */
        return empty;
    }

    /* Store the card to return */
    Card removed = deck->cards[index];

    /* Shift remaining cards left to fill the gap */
    for (int i = index; i < deck->size - 1; i++) {
        deck->cards[i] = deck->cards[i + 1];
    }

    /* One fewer card now */
    deck->size--;

    return removed;
}
/**
 * @brief Returns the current number of cards in the deck
 *
 * @param deck Pointer to the deck to check
 * @return int Number of cards in the deck
 */
int getDeckSize(const CardDeck* deck);
{
    if (deck == NULL)
        return 0;

    return deck->size;
}
/**
 * @brief Prints all cards in the deck to console
 *
 * @param deck Pointer to the deck to print
 *
 * @note Prints cards in order from bottom to top
 * @note Uses printCard() function for each card
 */
void printDeck(const CardDeck* deck);
{
    if (deck == NULL) {
        printf("(null deck)\n");
        return;
    }

    if (deck->size == 0) {
        printf("[empty deck]\n");
        return;
    }

    /* Print cards bottom → top */
    for (int i = 0; i < deck->size; i++) {
        printCard(deck->cards[i]);
        printf(" ");
    }

    printf("\n");
}

/**
 * @brief Moves card from one deck to another
 *
 * @param fromDeck Pointer to source deck
 * @param toDeck Pointer to destination deck
 * @param index Index of card to move in source deck
 */
void moveCardBetweenDecks(CardDeck* fromDeck, CardDeck* toDeck, int index);
{
    if (fromDeck == NULL || toDeck == NULL) {
        fprintf(stderr, "Error: moveCardBetweenDecks() called with NULL deck.\n");
        return;
    }

    if (index < 0 || index >= fromDeck->size) {
        fprintf(stderr, "Error: moveCardBetweenDecks() invalid index.\n");
        return;
    }

    /* Remove the card from the source deck */
    Card cardToMove = removeCardAtIndex(fromDeck, index);

    /* Add the card to the top of the destination deck */
    addCardToTop(toDeck, cardToMove);
}
#endif // DECK_H
