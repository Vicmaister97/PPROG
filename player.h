
/*  
	Group: Obviously nut
		Alfonso Villar
		Arturo Turmo
		Blanca Martín
		Víctor Gracía
*/
		
#ifndef PLAYERPRUEBA_H
#define PLAYERPRUEBA_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "types.h"

typedef struct _Player Player;

/*

struct _Player{
	char* name;
	int wai; Where he is
	int stats[5];  [0]: Strength; [1]: HP; [2]: Speed; [3]: Wisdom; [4]: Defense
};
*/

Player *create_player(); /*Creates a Player and allocates memory for it*/
void delete_player( Player* p); /*Frees the memory allocated for the Player p*/
char *getName_player(Player *p); /*Given a Player, returns its name*/
int *getStats_player(Player *p); /*Given a Player, returns its stats*/ 
int getWaI_player(Player *p); /*Given a Player, returns where it is*/
Status modName_player(Player *p, char *newName); /*Modifies the name of a given Player*/
Status modStats_player(Player *p, int *newStats); /*Modifies the stats of a given Player*/
Status modWaI_player(Player *p, int newWaI); /*Modifies where the Player is*/

#endif
