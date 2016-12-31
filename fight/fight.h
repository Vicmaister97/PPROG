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


Fight* join_fight(Player* player, Player* foe);
Player* resolve(Player* p1,Player* p2, int hab,Fight *fight);
void waitFor (unsigned int secs);
int aleat_num(int inf, int sup);












#endif
