/**
 * @file card.h
 * @brief Definition of Card data type and related operations
 *
 * This module defines the fundamental Card data structure using enums for suit and rank,
 * and provides basic operations for card manipulation and comparison.
 *
 * @author 
 * @date 
 */
#ifndef CARD_H
#define CARD_H

/**
 * @enum Suit
 * @brief Represents the four suits of playing cards
 */
typedef enum {
    CLUBS,      /**< Clubs suit */
    SPADES,     /**< Spades suit */
    HEARTS,     /**< Hearts suit */
    DIAMONDS    /**< Diamonds suit */
} Suit;

/**
 * @enum Rank
 * @brief Represents the thirteen ranks of playing cards
 */
typedef enum {
    TWO,        /**< Rank Two */
    THREE,      /**< Rank Three */
    FOUR,       /**< Rank Four */
    FIVE,       /**< Rank Five */
    SIX,        /**< Rank Six */
    SEVEN,      /**< Rank Seven */
    EIGHT,      /**< Rank Eight */
    NINE,       /**< Rank Nine */
    TEN,        /**< Rank Ten */
    JACK,       /**< Rank Jack */
    QUEEN,      /**< Rank Queen */
    KING,       /**< Rank King */
    ACE         /**< Rank Ace */
} Rank;

/**
 * @struct Card
 * @brief Represents a single playing card with suit and rank
 */
typedef struct {
    Suit suit;  /**< The suit of the card (CLUBS, SPADES, HEARTS, DIAMONDS) */
    Rank rank;  /**< The rank of the card (TWO through ACE) */
} Card;

/**
 * @brief Creates and returns a Card structure
 *
 * @param suit The suit of the card to create
 * @param rank The rank of the card to create
 * @return Card The created card structure
 */
Card createCard(Suit suit, Rank rank);

/**
 * @brief Prints a card to console in readable format (e.g., "Spade-Five")
 *
 * @param card Pointer to the card to print
 *
 * @note Output should be in format "Suit-Rank" using the enum names
 * @example
 * Card c = {HEARTS, ACE};
 * printCard(&c); // Should print "Hearts-Ace"
 */
void printCard(const Card* card);

/**
 * @brief Compares two cards for sorting purposes
 *
 * Comparison order:
 * - First by suit: CLUBS < SPADES < HEARTS < DIAMONDS
 * - Then by rank: TWO < THREE < ... < ACE
 *
 * @param card1 Pointer to first card
 * @param card2 Pointer to second card
 * @return int Negative if card1 < card2, 0 if equal, positive if card1 > card2
 *
 * @note Used by sortDeck() function for card comparison
 */
int compareCards(const Card* card1, const Card* card2);

/**
 * @brief Checks if a player can play a card on the current top card
 *
 * According to game rules, a card can be played if it matches the top card
 * either in suit OR in rank.
 *
 * @param playerCard Pointer to the card the player wants to play
 * @param topCard Pointer to the current top card on the played deck
 * @return int 1 if the card can be played, 0 otherwise
 *
 * @example
 * // If topCard is Spade-Five, player can play:
 * // - Any Spade (Spade-Two, Spade-Ten, etc.) OR
 * // - Any Five (Heart-Five, Club-Five, etc.)
 */
int canPlayCard(const Card* playerCard, const Card* topCard);

#endif
