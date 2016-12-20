#include "player.h"
		

struct _Player{
	char* name;
	int wai; /*Where he is*/
	int stats[6];  /*[0]: Strength; [1]: HP; [2]: Speed; [3]: Wisdom; [4]: Defense; [5]: Luck*/
	int col;
	int row;
	char show;
};


/*Private function*/
int* setDefStats( Player *p ){
	int i = 0;
	if( p == NULL) 	
		return NULL;
	for( ; i < 6; i++)
		p->stats[i] = 50;
	return p->stats;
}


/*Public functions*/
Player* create_player(const char * file_player) { 
/*No muy claro qué necesito para crear un jugador*/
	int i = 0;
	char buff[100];
	Player* p = ( Player *) malloc( sizeof( Player ));
	if( !p ) return NULL;
	p->name = (char *)malloc(sizeof(char)*10);
	strcpy( p->name, "default" );
	if( !p->name ){
		free( p );
		return NULL;
	}
	for( ; i < 6; i++ ){
		p->stats[i] = setDefStats(p)[i];
	}
	FILE *f;
	f=fopen(file_player,"r");
	p->col=atoi(fgets(buff,100,f));
	p->row=atoi(fgets(buff,100,f));

	p->show=fgetc(f);
	p->wai = 1;
	fclose(f);
	return p;
}	

void delete_player( Player* p){
	if( p->name ) free( p->name );
	if( p ) free( p );
}

char* getName_player( Player* p ){
	if( !p->name ) return NULL;
	return p->name;
}

int getWaI_player( Player* p ){
	if( !p ) return 0;
	return p->wai;
}

int* getStats_player( Player* p ){
	if(!p) return NULL;
	return p->stats;
}

Status modName_player( Player* p, char* newName){
	if(!newName) return ERROR;
	strcpy( p->name, newName);
	if(!p->name) return ERROR;
	return OK;
}

Status modStats_player(Player *p, int *newStats){
	int i = 0;
	for( ; i < 6; i++)
			p->stats[i] = newStats[i];
	return OK;
}	

Status modWaI_player(Player *p, int newWaI){
	if(!p) return ERROR;
	p->wai = newWaI;
	return OK;
}
int getRow_player(Player *p){
	if(!p) return -1;
	return p->row;
}
int getCol_player(Player *p){
	if(!p) return -1;
	return p->col;
}
Status modRow_player(Player *p,int row){
	if(!p)return ERROR;
	p->row=row;
	return OK;
}
Status modCol_player(Player *p,int col){
	if(!p)return ERROR;
	p->col=col;
	return OK;
}
char getSymbol_player(Player *p){
	if(!p)return ' ';
	return p->show;
}