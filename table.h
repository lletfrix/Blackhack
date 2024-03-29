#ifndef TABLE_H
#define TABLE_H

typedef struct _Table Table;

#include "deck.h"
#include "crupier.h"
#include "player.h"
#include "hand.h"


/*
 * Returns a new table.
 */
Table *table_ini();

/*
 * Frees a table and all children attributes (Deck, Players, Crupier and their Hands).
 */
void table_destroy(Table *);

/*
 * Stores a pointer to the specified player in table.
 */
Table *table_addPlayer(Table *, Player *);

/*
 * Returns a pointer to the deck of the game. Modifications to the deck will affect the rest of the deck.
 */
Deck *table_getDeck(const Table *);

/*
 * Sets the deck of the table to the specified Deck.
 */
Table *table_setDeck(Table *, Deck *);

/*
 * Returns a pointer to the crupier. Modifications to the crupier will affect the rest of the game.
 */
Crupier *table_getCrupier(const Table *);

/*
 * Sets the crupier of the game to the specified one.
 */
Table *table_setCrupier(Table *, Crupier *);

/*
 * Returns an array of pointers to Players. Modifications to players will affect the rest of the game.
 */
Player **table_getPlayers(const Table *);

/*
 * Returns the number of players on the table.
 */
int table_getNPlayers(const Table *);

/*
 * Returns the ith player on the table. Modifications to that player will affect the rest of the game.
 */
Player *table_getPlayer(const Table *, int player_index);

/*
 * Calls on each player to bet.
 */
Table *table_makeBets(Table *);

/*
 * Calls on each player to play.
 */
Table *table_makePlays(Table *);

/*
 * Deals a card to each player.
 */
Table *table_dealCard(Table *);

/*
 * Deals a card to the crupier.
 */
Table *table_dealCardToCrupier(Table *);

/*
 * Calculates outcomes for each player and distributes earnings.
 */
Table *table_distributeEarnings(Table *);

/*
 * Restart all the hands from crupier and players
 */

Table *table_restartTable(Table *);

/* Print players money */
int table_printPlayersMoney(FILE *pf, Table* t);

/* Print all players percentages */
int table_printPlayersPercentages(FILE *, Table *);

/* Print all players Maximum Streaks*/
int table_printPlayersStreakData (FILE *, Table*);

/*Print all players last game*/
int table_printLastGame(FILE*, Table*, int);

/* Print player cash separated by semi-colon */
int table_printCash(FILE *, Table *);

#endif
