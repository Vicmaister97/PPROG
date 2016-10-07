
#ifndef PLAYER_H
#define PLAYER_H

typedef struct _Player Player;

Player *create_player(char *name);
Status *destroy_player( Player* p);
char *getName_player(Player *p);
int *getStats_player(Player *p);
int getWaI_player(Player *p);
Status *modName_player(Player *p, char *newName);
Status *modStats_player(Player *p, int *newStats);
Status modWaI_player(Player *p, int newWaI); 

#endif
