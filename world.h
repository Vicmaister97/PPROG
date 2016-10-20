//I have "int" to cast al functions, but this is just temporal, when ill made
//them in the .c ill change the cast if necesary

#ifndef WORLD_H
#define WORLD_H
	
#include <stdio.h>
#include "objects.h"
#include "space.h"
#include "player.h"

typedef struct _World World;
typedef struct _Map Map;
/*
struct _World{
    Player* player;
    Map** map;
}
struct _Map{
    Space** space;
    int size;
}
*/


int create_world(); // It makes a new world
int delete_world(); // It deletes a world
int save_world(); // It saves a world
int load_world(); // It loads a world
int edit_world(); // It edits a world
int world_create_player(); // It creates a new player in a world 
int world_change_player(); // It changes de player of a world
int world_delete_player(); // It deletes the player of a world
int world_create_map(); // It creates a map in a world
int world_change_map(); // It changes the map of the world
int world_delete_map(); // It deletes the map of the world
int create_map(); //It creates a new map
int change_map(); //It changes a map
int change_map_space(); // It changes a space of the map
int delete_map(); // It deletes a map
#endif


