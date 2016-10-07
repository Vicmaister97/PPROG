#include "player.h"

struct _Player{
	char *name;
	int wai; /*Where he is*/
	int stats[5];  /*[0]: Strength; [1]: HP; [2]: Speed; [3]: Wisdom; [4]: Defense*/
};

/*Función privada*/
int *setDefStats( Player *p ){
	for (int i=0; i < 5; i++)
		p->stats[i]=50;
	return p->stats;
}

/*Funciones públicas*/
Player* create_player( char* name ) {
	Player* p = NULL;
	p = ( Player *) malloc( sizeof( Player ));
	strcpy( p->name, name );
	p->stats = setDefStats( p );
	p->wai = 0;
	return p;
}	

char* getName_player( Player* p ){
	return p->name;
}

int getWaI_player( Player* p ){
	return p->wai;
}

int* getStats_player( Player* p ){
	return p->stats;
}

Status modName_player( Player* p, char* newName){
	strcpy( p->name, newName);
	return OK;
}

Status destroy_player( Player* p)
	


