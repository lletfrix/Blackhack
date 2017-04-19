/* main.c*/
#include "player.h"
#include "crupier.h"
#include "hand.h"
#include "deck.h"

// load strategies
#include "bet_strategies.h"
#include "play_strategies.h"

#define NUMPLAYERS 4

int main(int argc, char** argv) {
    int numPartidas;
    if (argc < 2){
    fprintf(stderr, "Playing a hundred games as default.\n");
    numPartidas=100;    
    }
    else numPartidas=atoi(argv[1]);
    Table *table = table_ini();
    if(!table)
    {
        fprintf(stderr, "main: error: failed to initialize table\n");
        return 1;
    }

    // initialize players
    //
    // set the first player to use a random strategy
    table = table_addPlayer(table, player_ini(boring_bet, play_random));

    for (int i = 1; i < NUMPLAYERS; i++) {
        // pasar funciones vacías para que de momento compile
        Player *p = player_ini(boring_bet, play_like_crupier);
        if (!p) {
            fprintf(stderr, "main: player_ini: error allocating memory for player %d\n", i);
            table_destroy(table);
            return 2;
        }

        table = table_addPlayer(table, p);
    }

    // initialize crupier
    Crupier *crupier = crupier_ini();
    if (!crupier) {
        fprintf(stderr, "main: crupier_ini: error allocating memory for crupier\n");
        table_destroy(table);
        return 3;
    }
    table = table_setCrupier(table, crupier);

    // initialize deck
    Deck *deck = deck_ini();
    if (!deck) {
        fprintf(stderr, "main: deck_ini: error allocating memory of deck\n");
        table_destroy(table);
        return 4;
    }
    table = table_setDeck(table, deck);

    // play a hundred times
    for (int k = 0; k < numPartidas; k++) {

        /* apostar*/
        table = table_makeBets(table);

        /* repartir primera carta */
        table = table_dealCard(table);

        /* repartir 1 carta al crupier */
        table = table_dealCardToCrupier(table);

        /*repartir segunda carta*/
        table = table_dealCard(table);

        /* juegan los jugadores */
        table = table_makePlays(table);

        /*juega el crupier*/ // TODO: should we only touch the crupier thorugh table?
        crupier = crupier_play(crupier, deck);

        table = table_distributeEarnings(table);

        table = table_restartTable(table);
    }

table_printPlayersPercentages(stdout, table);

table_printPlayersMoney(stdout, table);

return EXIT_SUCCESS;
}
