/*  
	Group: Obviously nut
		Alfonso Villar
		Arturo Turmo
		Blanca Martín
		Víctor Gracía
*/

#include "world.h"

struct _World{
    /*char *name;*/
    Player* player;
    Space **spaces;
    int n_spaces;
    Object **objects;
    int n_objects;
};


World *create_world(const char *filesp, const char *fileob){
    char buf[100];
    int i = 0, j = 0;
    World *w= (World *) malloc(sizeof(World));
    FILE *pfs = fopen(filesp, "r");
    FILE *pfo = fopen(fileob, "r");
    w->n_spaces = atoi(fgets(buf, 100, pfs));
    w->spaces = (Space **)malloc(sizeof(Space *)*w->n_spaces);
    for( ; i < w->n_spaces; i++){
        w->spaces[i] = create_Space(pfs);
        /*if(!w->spaces[i]){
        	for( ; i >= 0; i--)
        		delete_space( w->spaces[i] );
            free(w->spaces);
        	free( w );
            fclose(pfs);
            fclose(pfo);
        	return NULL;
        }*/
    }
    w->player = create_player(); 
    /*if(!w->player){
    	for( ; i >= 0; i--)
    		delete_space( w->spaces[i] );
        free(w->spaces);
    	free(w);
        fclose(pfs);
        fclose(pfo);
    	return NULL;
    }*/
    w->objects = (Object **)malloc(sizeof(Object *)*w->n_objects);
    for( ; j < w->n_objects; i++){
        w->objects[i] = create_object(pfo);
    }
    return w;

}

void delete_world(World *w){
    int i=0;
	if(!w) return;
	for( ; i < w->n_spaces; i++)
		delete_space(w->spaces[i]);
    free(w->spaces);
	delete_player(w->player);
	free(w);
}

Player *getPlayer_world(World *w){
	if(!w) return NULL;
	return w->player;
}

Space *getByID_world(World *w, int id) {
    int i=0;
    Space **s = w->spaces;
    for ( ; i < w->n_spaces; i++)
        if (getID(s[i])==id) 
            return s[i];
    return NULL; 
}

/*	
	Function that moves the player from one space to another.
	INPUT:
	- World *w : a world, not NULL
	- int dir : the direction, being 1 = NORTH, 2 = EAST, 3 = SOUTH, 4 = WEST
	OUTPUT:
	- 1 : the current space is NULL
	- 0 : the player has been moved succesfully
	- 2 : the room is locked
	- 3 : some error related to the modification of the player wai (player == NULL)
*/
int movePlayer_world(World *w, int dir) {
    int curr_id = getWaI_player(w->player);
    Space *curr_sp = getByID_world(w, curr_id);
    int new_id = getNeigh_space(curr_sp, dir); /*Dudas sobre la implementación de la función*/
    if (!curr_sp) return 1;
    if(isLocked(curr_sp,dir)==TRUE) return 2;
    if(modWaI_player(w->player,new_id)==ERROR) return 3;
    return 0;

}

Object *getByIdObject_world(World *w, int id){
    
}

Object **getObjectsSpace_world(World *w, int sp_id){
    if(!w || sp_id < 0) return NULL;

}


