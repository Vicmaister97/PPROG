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


World *create_world(const char *filesp, const char *fileob,const char *fileplayer){
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
        		delete_Space( w->spaces[i] );
            free(w->spaces);
        	free( w );
            fclose(pfs);
            fclose(pfo);
        	return NULL;
        }*/
    }
    w->player = create_player(fileplayer); 
    /*if(!w->player){
    	for( ; i >= 0; i--)
    		delete_Space( w->spaces[i] );
        free(w->spaces);
    	free(w);
        fclose(pfs);
        fclose(pfo);
    	return NULL;
    }*/
    w->n_objects = atoi(fgets(buf, 100, pfo));
    w->objects = (Object **)malloc(sizeof(Object *)*w->n_objects);
    for( ; j < w->n_objects; j++){
        w->objects[j] = create_object(pfo);
    }
    return w;

}

void delete_world(World *w){
    int i=0;
	if(!w) return;
	for( ; i < w->n_spaces; i++)
		delete_Space(w->spaces[i]);
    free(w->spaces);
    for( i = 0; i < w->n_objects; i++){
        delete_object(w->objects[i]);
    }
    free(w->objects);
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
        if (getID_Space(s[i]) == id) 
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
    int new_id = getNeigh_Space(curr_sp, dir); /*Dudas sobre la implementación de la función*/
    if(!getByID_world(w,new_id)) return curr_id;
    if (!curr_sp) return 1;
    if(isLocked_Space(curr_sp,dir)==TRUE) return 2;
    if(modWaI_player(w->player,new_id)==ERROR) return 3;
    return 0;

}


int _get_num_objects_space(int sp_id, World *w){
    int i = 0, cont = 0;
    if(sp_id < 0) return 0;
    for( ; i < w->n_objects; i++)
        if(getLocation_object(w->objects[i]) == sp_id)
            cont ++;
    return cont;
}

Object **getObjectsSpace_world(World *w, int sp_id){
    int i = 0, j = 0;
    Object **obs = (Object **)malloc(sizeof(Object *)*_get_num_objects_space(sp_id,w));
    if(!w || sp_id <= 0){
        free(obs);
        return NULL;
    }
    for( ; i < w->n_objects; i++){
        if(getLocation_object(w->objects[i]) == sp_id){
            obs[j] = w->objects[i];
            j++;
        }
    }
    return obs;
}

Object *getByIdObject_world(World *w, int id){
    int i = 0;
    Object **obs = w->objects;
    if(!w || id < 0) return NULL;
    for( ; i < w->n_objects; i++){
        if(getId_object(obs[i]) == id)
            return obs[i];
    }
    return NULL;
}





