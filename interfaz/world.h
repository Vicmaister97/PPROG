

#ifndef WORLD_H
#define WORLD_H
    
#include <stdio.h>
#include <stdlib.h>
#include "space.h"
#include "player.h"
#include "types.h"
#include "object.h"

typedef struct _World World;

World *create_world(const char *filesp, const char *fileob,const char* );
void delete_world(World *w);
Player *getPlayer_world(World *w);
Space *getByID_world(World *w, int id);
int movePlayer_world(World *w, int dir);
Object **getObjectsSpace_world(World *w, int sp_id);
int _get_num_objects_space(int sp_id, World *w);

#endif


