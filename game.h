
#ifndef GAME_H
#define GAME_H

#include "myintrf.h"
#include "world.h"
#include "cop.h"


typedef struct _Game Game;

Game *create_game(char *filesp, char *fileob, char *fileic, char *filepl, char *cmdfile);
void play_game(Game *gm);
void delete_game(Game *gm);


#endif