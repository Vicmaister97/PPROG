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
    People **people;
    int n_people;
    
    /*new stuff*/
    Player **enemies;
    int n_enemies;
};

/*fight stuff*/
int _get_num_enemies_space(int sp_id, World *w){
    int i = 0, cont = 0;
    if(sp_id < 0) return 0;
    for( ; i < w->n_enemies; i++)
        if(getWaI_player(w->enemies[i]) == sp_id)
            cont ++;
    return cont;
}

Player **getEnemiesSpace_world(World *w, int sp_id){
    int i = 0, j = 0;
    Player **e = (Player **)malloc(sizeof(Player *)*_get_num_enemies_space(sp_id,w));
    if(!w || sp_id <= 0){
        free(e);
        
        return NULL;
    }
    for( ; i < _get_num_enemies_space(sp_id,w); i++){
        if(getWaI_player(w->enemies[i]) == sp_id){
            e[j] = w->enemies[i];
            j++;
        }
    }
    return e;
}

Player * getEnemy_world(World *w,Player *p,int col,int row){
    int i=0,id;
    id=getWaI_player(p);
    Player**aux;
    aux=getEnemiesSpace_world(w,id);
    for(i=0;i<_get_num_enemies_space(id,w);i++){
        if(getCol_player(aux[i])==col){
            if(getRow_player(aux[i])==row)return aux[i];
        }
    }
    return NULL;
}





World *create_world(const char *filesp, const char *fileob,const char *fileplayer,const char *fileEnemy){
    char buf[100];
    int i = 0, j = 0;
    World *w= (World *) malloc(sizeof(World));
    FILE *pfs = fopen(filesp, "r");
    FILE *pfo = fopen(fileob, "r");
    w->n_spaces = atoi(fgets(buf, 100, pfs));
    w->spaces = (Space **)malloc(sizeof(Space *)*w->n_spaces);
    for( i=0; i < w->n_spaces; i++){
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
    

    /*this is new*/
    FILE *pfe=fopen(fileEnemy,"r");
    if(pfe==NULL)printf("\nERRRORRR\n");
    
    w->n_enemies=atoi(fgets(buf, 100, pfe));
    w->enemies = (Player **)malloc(sizeof(Player *)*w->n_enemies);
    for (i=0;i<w->n_enemies;i++){
            w->enemies[i] = create_enemy(pfe); 
    }
    /*fclose(pfe);*/

    
    
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
  
    w->n_people = atoi(fgets(buf, 100, pfo));
    /*a=atoi(fgets(buf, 100, pfo));*/
    
    w->objects = (Object **)malloc(sizeof(Object *)*w->n_objects);
   
    for( j=0; j < w->n_objects; j++){        
        w->objects[j] = create_object(pfo);
    }
    fgets(buf,100,pfo);
    w->people = (People **)malloc(sizeof(People*)*w->n_people);
    
    for (j = 0; j < w->n_people; j++){
        w->people[j] = create_people(pfo);
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
    for( i = 0; i < w->n_people; i++){
        delete_people(w->people[i]);
    }
    free(w->objects);
    free(w->people);
    for(i = 0; i < w->n_enemies; i++)
        delete_player(w->enemies[i]);
    free(w->enemies);
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
    /*if(isDark_Space(curr_sp, dir) == TRUE){
        ret = getUnlock_Space(curr_sp, dir);
        modWaI_player(w->player,new_id);
        if(!isInInventory(getByIdObject_world(w, ret)))
            return ret*3;
    }*/
    if(modWaI_player(w->player,new_id)==ERROR) return 2;
    return 0;

}


int _get_num_objects_space(int sp_id, World *w){
    int i = 0, cont = 0;
    if(sp_id < 0) return 0;
    for( ; i < w->n_objects; i++){
        if(getLocation_object(w->objects[i]) == sp_id && isInInventory(w->objects[i]) == FALSE)
            cont ++;
    }
    return cont;
}

int _get_num_people_space(int sp_id, World *w){
    int i = 0, cont = 0;
    if(sp_id < 0) return 0;
    for( ; i < w->n_people; i++){
        if(getLocation_people(w->people[i]) == sp_id)
            cont ++;
    }
    return cont;
}

Object **getObjectsSpace_world(World *w, int sp_id){ /*CUIDADO PORQUE HAY QUE LIBERAR MEMORIA DESPUES DE LLAMAR A ESTA FUNCION*/
    int i = 0, j = 0;
    Object **obs = (Object **)malloc(sizeof(Object *)*_get_num_objects_space(sp_id,w));
    if(!w || sp_id <= 0){
        free(obs);
        return NULL;
    }
    for( ; i < w->n_objects; i++){
        if(getLocation_object(w->objects[i]) == sp_id && isInInventory(w->objects[i]) == FALSE){
            obs[j] = w->objects[i];
            j++;
        }
    }
    return obs;
}

People **getPeopleSpace_world(World *w, int sp_id){ /*CUIDADO PORQUE HAY QUE LIBERAR LA MEMORIA FUERA AL LLAMAR A ESTA FUNCION*/
    int i = 0, j = 0;
    People **peo = (People **)malloc(sizeof(People *)*_get_num_people_space(sp_id,w));
    if(!w || sp_id <= 0){
        free(peo);
        return NULL;
    }
    for( ; i < w->n_people; i++){
        if(getLocation_people(w->people[i]) == sp_id){
            peo[j] = w->people[i];
            j++;
        }
    }
    return peo;
}

Object *getByIdObject_world(World *w, int id){ /*Lo mismo del CUIDADO, en todas las de + adelante igual, hay que tener cuidado con esa memoria*/
    int i = 0;
    for( ; i < w->n_objects; i++){
        if(getId_object(w->objects[i]) == id){
            return w->objects[i];
        }
    }
    return NULL;
}

People *getByIdPeople_world(World *w, int id){
    int i = 0;
    for( ; i < w->n_objects; i++){
        if(getId_people(w->people[i]) == id){
            return w->people[i];
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

People *getPeopleByCoordinates_world(World *w, int row, int col, int sp_id){
    People **objs = getPeopleSpace_world(w, sp_id);
    People *ret = NULL;
    int i = 0;
    for( ; i < _get_num_people_space(sp_id, w); i++)
        if(getRow_people(objs[i]) == row && getCol_People(objs[i]) == col)
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
    for( ; i < w->n_objects; i++)
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
    if(!obs){
        free(ret);
        return NULL;
    }
    for( ; i < _get_num_objects_inventory(w); i++){
        if(obs[i]){
            ret[i] = (char *) malloc(sizeof(char)*strlen(getName_object(obs[i]))+1);
            strcpy(ret[i], getName_object(obs[i]));
        }
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



