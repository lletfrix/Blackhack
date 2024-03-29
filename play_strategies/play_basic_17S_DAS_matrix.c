#include "../play_strategies.h"

char recommendation_17S_DAS(int player_hand, int crupier_hand, Hand* h) {
    int* handCards, row, column, number_row;
    /*
     * x is for hit, D is for double-down, S is for split, a is for early surrender,
     * - is for stand.
     *
     *   To access this matrix:
     *   number_strategy[PLAYER_CONVERT(player_hand)][CRUPIER_CONVERT(crupier_hand)]
     */

    char number_strategy[34][10] = {
    //    2    3    4    5    6    7    8    9    10   A
        {'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x'}, // 5 #0
        {'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x'}, // 6
        {'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x'}, // 7
        {'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x'}, // 8
        {'x', 'D', 'D', 'D', 'D', 'x', 'x', 'x', 'x', 'x'}, // 9
        {'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'x', 'x'}, // 10
        {'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'x', 'x'}, // 11
        {'x', 'x', '-', '-', '-', 'x', 'x', 'x', 'x', 'x'}, // 12
        {'-', '-', '-', '-', '-', 'x', 'x', 'x', 'x', 'x'}, // 13
        {'-', '-', '-', '-', '-', 'x', 'x', 'x', 'x', 'x'}, // 14
        {'-', '-', '-', '-', '-', 'x', 'x', 'x', 'x', 'x'}, // 15 #10
        {'-', '-', '-', '-', '-', 'x', 'x', 'x', 'x', 'x'}, // 16
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'}, // 17
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'}, // 18
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'}, // 19
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'}, // 20
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'}, // 21
        {'x', 'x', 'x', 'D', 'D', 'x', 'x', 'x', 'x', 'x'}, // A-2
        {'x', 'x', 'x', 'D', 'D', 'x', 'x', 'x', 'x', 'x'}, // A-3
        {'x', 'x', 'D', 'D', 'D', 'x', 'x', 'x', 'x', 'x'}, // A-4
        {'x', 'x', 'D', 'D', 'D', 'x', 'x', 'x', 'x', 'x'}, // A-5 #20
        {'x', 'D', 'D', 'D', 'D', 'x', 'x', 'x', 'x', 'x'}, // A-6
        {'-', 'd', 'd', 'd', 'd', '-', '-', 'x', 'x', 'x'}, // A-7
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'}, // A-8,9,T
        {'s', 's', 's', 's', 's', 's', 's', 's', 's', 'x'}, // A-A
        {'s', 's', 's', 's', 's', 's', 'x', 'x', 'x', 'x'}, // 2-2
        {'s', 's', 's', 's', 's', 's', 'x', 'x', 'x', 'x'}, // 3-3
        {'x', 'x', 'x', 's', 's', 'x', 'x', 'x', 'x', 'x'}, // 4-4
        {'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'x', 'x'}, // 5-5
        {'s', 's', 's', 's', 's', 's', 'x', 'x', 'x', 'x'}, // 6-6
        {'s', 's', 's', 's', 's', 's', 'x', 'x', 'x', 'x'}, // 7-7 #30
        {'s', 's', 's', 's', 's', 's', 's', 's', 'x', 'x'}, // 8-8
        {'s', 's', 's', 's', 's', '-', 's', 's', '-', '-'}, // 9-9
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'}, // T-T
    };

    int player_combination[10][10] = {
    //    2  3  4  5  6  7  8  9  T  A
        {25, 0, 1, 2, 3, 4, 5, 6, 7, 17}, // 2
        { 0,26, 2, 3, 4, 5, 6, 7, 8, 18}, // 3
        { 1, 2,27, 4, 5, 6, 7, 8, 9, 19}, // 4
        { 2, 3, 4,28, 6, 7, 8, 9,10, 20}, // 5
        { 3, 4, 5, 6,29, 8, 9,10,11, 21}, // 6
        { 4, 5, 6, 7, 8,30,10,11,12, 22}, // 7
        { 5, 6, 7, 8, 9,10,31,12,13, 23}, // 8
        { 6, 7, 8, 9,10,11,12,32,14, 23}, // 9
        { 7, 8, 9,10,11,12,13,14,33, 23}, // T
        {17,18,19,20,21,22,23,23,23, 24}, // A
    };

    if (player_hand > 21 || player_hand < 4|| hand_getNumCards(h) < 2) {
        fprintf(stderr, "strategy can't recommend anything for that value (%d)\n", player_hand);
        return 'E';
    }

    if (hand_getNumCards(h) == 2){
        handCards = hand_getCards(h);
        /*Optimize*/
        for (int i = 0; i < 10; i++) {
            if (handCards[i] != 0) {
                row = i-1;
                if (row == -1){
                    row = 9;
                }
                handCards[i]--;
                break;
            }
        }
        for (int i = 0; i < 10; i++) {
            if (handCards[i] != 0) {
                column = i-1;
                if (column == -1){
                    column = 9;
                }
                handCards[i]--;
                break;
            }
        }
        free (handCards);
        number_row = player_combination[row][column];
        return number_strategy[number_row][crupier_hand - 2];
    }

    return number_strategy[player_hand - 5][crupier_hand - 2];
}

Player *play_basic_17S_DAS_matrix(Player* p, Table* t){
    int *player_hand, *crupier_hand, player_value, active_hand=0, numHands=1, index=-1;
    char decision;
    Deck *d;
    Hand *current_hand;
    int no_split_matrix[18][10] = {
    //    2    3    4    5    6    7    8    9    10   A
        {'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x'}, // 4 #0
        {'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x'}, // 5 #1
        {'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x'}, // 6
        {'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x'}, // 7
        {'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x'}, // 8
        {'x', 'D', 'D', 'D', 'D', 'x', 'x', 'x', 'x', 'x'}, // 9
        {'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'x', 'x'}, // 10
        {'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'x', 'x'}, // 11
        {'x', 'x', '-', '-', '-', 'x', 'x', 'x', 'x', 'x'}, // 12
        {'-', '-', '-', '-', '-', 'x', 'x', 'x', 'x', 'x'}, // 13
        {'-', '-', '-', '-', '-', 'x', 'x', 'x', 'x', 'x'}, // 14
        {'-', '-', '-', '-', '-', 'x', 'x', 'x', 'x', 'x'}, // 15 #11
        {'-', '-', '-', '-', '-', 'x', 'x', 'x', 'x', 'x'}, // 16
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'}, // 17
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'}, // 18
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'}, // 19
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'}, // 20
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'}, // 21
    };

    if (!p || !t) {
        fprintf(stderr, "play_basic_17S_DAS_matrix: invalid parameters\n");
        return NULL;
    }

    d = table_getDeck(t);

    crupier_hand = hand_getValues(crupier_getHand(table_getCrupier(t)));
    if (!crupier_hand) {
        fprintf(stderr, "play_strategy: could not get crupier hand\n");
        return NULL;
    }

    while (active_hand < numHands) {
        player_hand = hand_getValues(player_getHand(p, active_hand));
        if (!player_hand) {
            fprintf(stderr, "play_strategy: handValues pointing NULL\n");
            return NULL;
        }

        // chose what value of the hand we'll use for this iteration of the strategy
        player_value = (player_hand[0] > 21 && player_hand[1] != -1) ? player_hand[1] : player_hand[0];

        // Blackjack! Pay immediately;
        if (player_value == 21 && hand_getNumCards(player_getHand(p, active_hand))==2){
            player_addCash(p, 2.5*hand_getCurrentBet(player_getHand(p, active_hand)));
            active_hand++;
            continue;
        }
        if (player_value > 21){
            /*printf("over 21.\n");*/
            active_hand++;
            continue;
        }

        decision = recommendation_17S_DAS(player_value, crupier_hand[0], player_getHand(p, active_hand));
        /*
        * Change decision depending on the situation. To be implemented.
        */
        /*If splitting is impossible go to the first table*/
        if(decision=='s' && numHands>=MAX_HANDS){
            decision = no_split_matrix[player_value-4][crupier_hand[0]-2];
        }
        /*If doubling is impossible, hit instead*/
        if(hand_getNumCards(player_getHand(p, active_hand))>2 && decision=='D'){
            decision='x';
        }
        if(hand_getNumCards(player_getHand(p, active_hand))>2 && decision=='d'){
            decision='-';
        }
        /*
        *
        */
        /*printf("%d vs %d: player choses to %c\n", player_value, crupier_hand[0], decision);*/
        switch(decision) {
            // hit, ask for another card
            case 'x':
                p = player_addCardToHand(p, active_hand, deck_draw(d));
                break;
            case 's':  //split
                /*printf("\e[0;31mSPLIT\e[0m\n");*/
                index = player_splitHand(p, active_hand);
                p = player_addCardToHand(p, active_hand, deck_draw(d));
                p = player_addCardToHand(p, index, deck_draw(d));
                int current_bet = hand_getCurrentBet(player_getHand(p, active_hand));
                p = player_removeCash(p, current_bet);
                hand_setCurrentBet(player_getHand(p, index), current_bet);
                numHands++;
                break;
            case 'D': // double
            case 'd':
                current_hand = player_getHand(p, active_hand);
                p = player_addCardToHand(p, active_hand, deck_draw(d));
                current_bet = hand_getCurrentBet(current_hand);
                p = player_removeCash(p, current_bet);
                current_bet*=2;
                hand_setCurrentBet(current_hand, current_bet);
                active_hand++;
                break;
            default: // stay
                active_hand++;
                break;
        }
    }

    return p;
}
