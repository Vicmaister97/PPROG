
/*  
	Group: Obviously nut
		Alfonso Villar
		Arturo Turmo
		Blanca Martín
		Víctor Gracía
*/
		
#ifndef PLAYER_H
#define PLAYER_H

typedef struct _Player Player;

Player *create_player(char *name); /*Creates a Player and allocates memory for it*/
Status *destroy_player( Player* p); /*Frees the memory allocated for the Player p*/
char *getName_player(Player *p); /*Given a Player, returns its name*/
int *getStats_player(Player *p); /*Given a Player, returns its stats*/ 
int getWaI_player(Player *p); /*Given a Player, returns where it is*/
Status modName_player(Player *p, char *newName); /*Modificates the name of a given Player*/
Status modStats_player(Player *p, int *newStats); /*Modificates the stats of a given Player*/
Status modWaI_player(Player *p, int newWaI); /*Modificates where the Player is*/

#endif
