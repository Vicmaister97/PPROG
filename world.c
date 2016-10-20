#include "world.h"


struct _World{
    Player* player;
    Map** map;
}
struct _Map{
    Space** space;
    int size;
}

World* create_world();
int delete_world();
int save_world();
int load_world();
int edit_world();
int world_create_player();
int world_change_player();
int world_delete_player();
int world_create_map();
int world_change_map();
int world_delete_map();
Map** create_map(int size){
    if (size<=0) return NULL;
    Map** map= (Map**) malloc (size*sizeof(space*));
    map->size=size;
    if (map==NULL) return NULL;
    return map;
}
int change_map(World* world, Map* map){
    if(world==NULL || map==NULL) return -1;
    world->map=map_copy (map);
    if (world->map==NULL) return -1;
    return 1;
}
int change_map_space();
int delete_map();
