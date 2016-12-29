#include "player.h"
		

struct _Player{
	char* name;
	int wai; /*Where he is*/
	int *stats;  /* [0]: Strength; [1]: Endurance; [2]: HP; [3]: Speed; [4]: Agility;  [5]: Luck */
	int *limit_stats;
	char **name_stats;
	int num_stats;
	int col;
	int row;
	char show;
	char **abilities;
	int NumAbilities;
	int damage_ability[4];
};


/*Private function*/
int* setDefStats( Player *p ){
	int i = 0;
	if( p == NULL) 	
		return NULL;
	for( ; i < p->num_stats; i++)
		p->stats[i] = 50;
	return p->stats;
}


/*Public functions*/
Player* create_player(const char * file_player) { 
/*No muy claro qué necesito para crear un jugador*/
	int i = 0;
	char buf[100];
	Player* p = ( Player *) malloc( sizeof( Player ));
	if( !p ) return NULL;
	p->name = (char *)malloc(sizeof(char)*10);
	strcpy( p->name, "default" );
	if( !p->name ){
		free( p );
		return NULL;
	}

	FILE *f;
	f=fopen(file_player,"r");
	p->col=atoi(fgets(buf,100,f));
	p->row=atoi(fgets(buf,100,f));

	p->show=fgetc(f);
	p->wai = 1;

	p->num_stats = atoi(fgets(buf, 100, f));
	p->stats = (int *) malloc(sizeof(int)*p->num_stats);
	p->stats = setDefStats(p);
	p->name_stats = (char **) malloc(sizeof(char *)*p->num_stats);
	p->limit_stats = (int *) malloc(sizeof(int)*p->num_stats);
	for(i = 0; i < p->num_stats; i++){
		fgets(buf, 100, f);
		p->name_stats[i] = (char *) malloc(sizeof(char)*strlen(buf)+1);
		strcpy(p->name_stats[i], buf);
		p->limit_stats[i] = atoi(fgets(buf, 100, f));
	}


	/*nuevo para el fight*/
	/*para leer el fichero del player, en la linea siguiente a la fila(row) debe aparecer un numero que corrsponde al numero
	de abilidades, Maximo 4*/
	p->NumAbilities = atoi(fgets(buf,100,f));
	if(p->NumAbilities>4){
		printf("ERROR no puede haber tantas habilidades");
		return NULL;
	}
	/*en la siguiente linea va el nombre de la habilidad y en la de debajo el daño que provoca*/
	/*cuando se llame en la funcion getAbilityName_player(Player *p,int n) n es 1,2,3 y 4*/
	p->abilities=(char**)malloc(sizeof(char*)*p->NumAbilities);
	for(i = 0; i < p->NumAbilities; i++){
		fgets(buf,100,f);
		p->abilities[i]=(char*)malloc(sizeof(char)*strlen(buf)+1);
		strcpy(p->abilities[i], buf);

		p->damage_ability[i]=atoi(fgets(buf,100,f));
	}
	

	fclose(f);
	return p;
}	

void delete_player( Player* p){
	int i = 0;
	if( p->name ) free( p->name );
	if(p->stats) free(p->stats);	
	for( ; i < p->num_stats; i++)
		if(p->name_stats[i]) free(p->name_stats[i]);
	if(p->name_stats) free(p->name_stats);
	if(p->limit_stats) free(p->limit_stats);
	for(i = 0; i < p->NumAbilities; i++)
		if(p->abilities[i]) free(p->abilities[i]);
	free(p->abilities);
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

int *getLimitStats_player(Player *p){
	if(!p) return NULL;
	return p->limit_stats;
}

char **getNameStats_player(Player *p){
	if(!p) return NULL;
	return p->name_stats;
}

int getNumStats_player(Player *p){
	if(!p) return -1;
	return p->num_stats;
}

Status modName_player( Player* p, char* newName){
	if(!newName) return ERROR;
	strcpy( p->name, newName);
	if(!p->name) return ERROR;
	return OK;
}

Status modStats_player(Player *p, int *newStats){
	int i = 0;
	for( ; i < p->num_stats; i++)
			p->stats[i] += newStats[i];
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


/*funciones del fight*/
int getStrength_player(Player *p){
	if(!p)return ERROR;
	return p->stats[0];
}
int getEndurance_player(Player *p){
	if(!p)return ERROR;
	return p->stats[1];
}
int getHp_player(Player *p){
	if(!p)return ERROR;
	return p->stats[2];
}
int getSpeed_player(Player *p){
	if(!p)return ERROR;
	return p->stats[3];
}
int getAgility_player(Player *p){
	if(!p)return ERROR;
	return p->stats[4];
}
int getLuck_player(Player *p){
	if(!p)return ERROR;
	return p->stats[5];
}


Status changeStrength_player(Player*p,int strength){
	if(!p)return ERROR;
	p->stats[0]=p->stats[0]+strength;
	if(p->stats[0]<=0)p->stats[0]=1;
	return OK;
}

Status changeEndurance_player(Player*p,int endurance){
	if(!p)return ERROR;
	p->stats[1]=p->stats[1]+endurance;
	if(p->stats[1]<=0)p->stats[1]=1;
	return OK;
}

Status changeHp_player(Player*p,int hp){
	if(!p)return ERROR;
	p->stats[2]=p->stats[2]+hp;
	if(p->stats[2]<=0)p->stats[2]=1;
	return OK;
}

Status changeSpeed_player(Player*p,int speed){
	if(!p)return ERROR;
	p->stats[3]=p->stats[3]+speed;
	if(p->stats[3]<=0)p->stats[3]=1;
	return OK;
}

Status changeAgility_player(Player*p,int agility){
	if(!p)return ERROR;
	p->stats[4]=p->stats[4]+agility;
	if(p->stats[4]<=0)p->stats[4]=1;
	return OK;
}

Status changeLuck_player(Player*p,int luck){
	if(!p)return ERROR;
	p->stats[5]=p->stats[5]+luck;
	if(p->stats[5]<=0)p->stats[5]=1;
	return OK;
}





char * getAbilityName_player(Player *p,int n){
 if(!p) return NULL;
 return p->abilities[n-1];

}

int getDamageAbility_player(Player*p,int n){
	if(!p||n<0)return ERROR;
	return p->damage_ability[n-1];
}