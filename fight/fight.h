/*
Fights are going to be done by rounds, where the faster fighter starts.
There'll be some facts that will make the fight get easier or harder for the fighters.
Also the fighters'll have 4 habilities to make the diference in the fight.
and they'll be SPEED HP DMG EVASION 
*/
#ifndef FIGTH_H
#define FIGTH_H

/*#include "world.h"	
#include "objects.h"
#include "space.h"*/

#include <time.h>
#include "player.h"

typedef struct _Fight Fight;


<<<<<<< HEAD
Status join_fight(Player* player, Player* foe);
Player* resolve(Player* p1,Player* p2, int hab,Fight *fight);
=======
Fight* join_fight(Player* player, Player* foe);
>>>>>>> d3764174fef00c78486f1b4a2f99ee1483ae6f7f
void waitFor (unsigned int secs);
int aleat_num(int inf, int sup);
int getRound_fight (Fight *fight);
int RunAway(Fight *fight);
Bool isFinished_fight(Fight *fight);
Status nextRound_fight(Fight *fight);
Player *getPlayer_fight(Fight *fight);
Player *getFoe_fight(Fight *fight);
void finish_fight(Fight *fight);




#endif
