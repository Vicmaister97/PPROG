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
	- negative number : the id of the needed object
	- 2 : some error related to the modification of the player wai (player == NULL)
*/
int movePlayer_world(World *w, int dir) {
    int ret = 0;
    int curr_id = getWaI_player(w->player);
    Space *curr_sp = getByID_world(w, curr_id);
    int new_id = getNeigh_Space(curr_sp, dir);/*Dudas sobre la implementación de la función*/
    if(!getByID_world(w,new_id)) return curr_id;
    if (!curr_sp) return 1;
    if(isLocked_Space(curr_sp,dir)==TRUE){
        ret = getUnlock_Space(curr_sp, dir);
        if(!isInInventory(getByIdObject_world(w, ret)))
            return -ret;
    }
    if(isDark_Space(curr_sp, dir) == TRUE){
        ret = getUnlock_Space(curr_sp, dir);
        modWaI_player(w->player,new_id);
        if(!isInInventory(getByIdObject_world(w, ret)))
            return ret*3;
    }
    if(modWaI_player(w->player,new_id)==ERROR) return 2;
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
    for( ; i < w->n_objects; i++){
        if(getId_object(obs[i]) == id){
            return obs[i];
        }
    }
    return NULL;
}


Object *getObjectByCoordinates_world(World *w, int row, int col, int sp_id){
    Object **objs = getObjectsSpace_world(w, sp_id);
    Object *ret = NULL;
    int i = 0;
    for( ; i < _get_num_objects_space(sp_id, w); i++)
        if(getRow_object(objs[i]) == row && getCol_object(objs[i]) == col)
            ret = objs[i];
        
    free(objs);
    if(ret) return ret;
    return NULL;
}

int _get_num_objects_inventory(World *w){
    int i = 0, ret = 0;
    for( ; i < w->n_objects; i++){
        if(isInInventory(w->objects[i]))
            ret++;
    }
    return ret;
}

Object **getObjectsInventory_world(World *w){
    Object **obs = (Object **) malloc(sizeof(Object *)*_get_num_objects_inventory(w));
    int i = 0, j = 0;
    if(!w){
        free(obs);
        return NULL;
    }
    for( ; i < _get_num_objects_inventory(w); i++)
        if(isInInventory(w->objects[i])){
            obs[j] = w->objects[i];
            j++;
        }
    return obs;
}

char **getNamesObjectsInventory_world(World *w){
    Object **obs = getObjectsInventory_world(w);
    char **ret = (char **) malloc(sizeof(char *)*_get_num_objects_inventory(w));
    int i = 0;
    for( ; i < _get_num_objects_inventory(w); i++){
        ret[i] = (char *) malloc(sizeof(char)*strlen(getName_object(obs[i]))+1);
        strcpy(ret[i], getName_object(obs[i]));
    }
    free(obs);
    return ret;
}

char *getPicturesObjectsInventory_world(World *w){
    Object **obs = getObjectsInventory_world(w);
    char *pict = (char *) malloc(sizeof(char) * _get_num_objects_inventory(w));
    int i = 0;
    for( ; i < _get_num_objects_inventory(w); i++)
        pict[i] = getPicture_object(obs[i]);
    free(obs);
    return pict;
}

Object *getObjectByName_wordl(World *w, char *name){
    int i = 0;
    if(!w || !name)
        return NULL;
    for( ; i < w->n_objects; i++)
        if(!strcmp(getName_object(w->objects[i]), name))
            return w->objects[i];
    return NULL;
}

Space *getSpaceByName_world(World *w, char *name){
    int i = 0;
    if(!w || !name)
        return NULL;
    for( ; i < w->n_spaces; i++)
        if(!strcmp(name_Space(w->spaces[i]), name))
            return w->spaces[i];
    return NULL;
}


