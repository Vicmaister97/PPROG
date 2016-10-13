/*  
	Group: Obviously nut
		Alfonso Villar
		Arturo Turmo
		Blanca Martín
		Víctor Gracía
*/


#include "player.h"
		

struct _Player{
	char* name;
	int wai; /*Where he is*/
	int stats[5];  /*[0]: Strength; [1]: HP; [2]: Speed; [3]: Wisdom; [4]: Defense*/
};


/*Private function*/
int* setDefStats( Player *p ){
	int i = 0;
	if( p == NULL) 	
		return NULL;
	for ( ; i < 5; i++)
		p->stats[i] = 50;
	return p->stats;
}


/*Public functions*/
Player* create_player( char* name ) {
	Player* p = NULL;
	p = ( Player *) malloc( sizeof( Player ));
	strcpy( p->name, name );
	p->stats = setDefStats( p );
	p->wai = 0;
	return p;
}	


Status destroy_player( Player* p){
	free( p->name );
	free( p );
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

Status modStats_player(Player *p, int *newStats){
	int i = 0;
	for( ; i < 5; i++)
			p->stats[i] = newStats[i];
	return OK;
}	

Status modWaI_player(Player *p, int newWaI){
	p->wai = newWaI;
	return OK;
}


