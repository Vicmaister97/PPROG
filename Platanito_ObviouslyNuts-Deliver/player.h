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
int getRow_player(Player *p);
int getCol_player(Player *p);
char getSymbol_player(Player *p);
Status modRow_player(Player *p, int row);
Status modCol_player(Player *p, int col);
int *getLimitStats_player(Player *p);
char **getNameStats_player(Player *p);
int getNumStats_player(Player *p);

/*functions for fight*/
int getStrength_player(Player *p);
int getEndurance_player(Player *p);
int getHp_player(Player *p);
int getSpeed_player(Player *p);
int getAgility_player(Player *p);
int getLuck_player(Player *p);

int getPlatanito_player(Player *p);
Status changePlatanito_player(Player*p);

Status changeStrength_player(Player*p,int strength);
Status changeEndurance_player(Player*p,int endurance);
Status changeHp_player(Player*p,int hp);
Status changeSpeed_player(Player*p,int speed);
Status changeAgility_player(Player*p,int agility);
Status changeLuck_player(Player*p,int luck);

char * getAbilityName_player(Player *p,int n);

int *getAbilities_player(Player *p,int n);

Status add_player_stats(Player* p,int n);
Status less_player_stats(Player* p,int n);
Player *copy_player(Player*p1);
Player* create_enemy(FILE *f);
int getId_player(Player *p);

int getNum_player(Player *p);
Status changeNum_player(Player *p);
Status changeStats_player(Player *p,int num);
Status switchHP_player(Player *p,int new);
#endif
