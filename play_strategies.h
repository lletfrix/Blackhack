#include "player.h"
#include "table.h"
#include "probability.h"

/**
 * Esta estrategia no hace nada.
 */
Player *play_do_nothing(Player *, Table *);

Player *play_like_crupier(Player *, Table *);

Player *play_random(Player *, Table *);

Player *play_standard_wo_sd(Player*, Table*);

Player *play_basic(Player*, Table*);

Player *play_basic_17S_DAS(Player*, Table*);

Player *play_basic_17S_DAS_matrix(Player *, Table *);

Player *play_manual(Player*, Table*);

char recommendation_17S_DAS(int player_hand, int crupier_hand, Hand*);
