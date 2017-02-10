#include "player.h"
		

struct _Player{
	char* name;
	int wai; 
	int *stats;  /* [0]: Strength; [1]: Endurance; [2]: HP; [3]: Speed; [4]: Agility;  [5]: Luck */
	int *limit_stats;
	char **name_stats;
	int num_stats;
	int col;
	int row;
	char show; 
	char **abilities; 
	int NumAbilities; 
	int id;
	int num;

	int strength_ability[4];
	int endurance_ability[4];
	int hp_ability[4];
	int speed_ability[4];
	int agility_ability[4];
	int luck_ability[4];
	int platanito_cheat;
	
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
	int i = 0;
	char buf[100];
	Player* p = ( Player *) malloc( sizeof( Player ));
	if( !p ) return NULL;
	

	FILE *f;
	f=fopen(file_player,"r");
	p->col=atoi(fgets(buf,100,f));
	p->row=atoi(fgets(buf,100,f));
	p->id=0;
	p->show=fgetc(f);
	p->wai = 66;
	p->num=0;

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
		p->stats[i]=atoi(fgets(buf, 100, f));
	}


	p->NumAbilities = atoi(fgets(buf,100,f));
	if(p->NumAbilities>4){
		printf("ERROR no puede haber tantas habilidades");
		return NULL;
	}
	
	p->abilities=(char**)malloc(sizeof(char*)*4);

	for(i=0;i<4;i++){
		p->abilities[i]=(char*)malloc(sizeof(char)*20);
		strcpy (p->abilities[i], "vacio");


		p->strength_ability[i]=0;
		p->endurance_ability[i]=0;
		p->hp_ability[i]=0;
		p->speed_ability[i]=0;
		p->agility_ability[i]=0;
		p->luck_ability[i]=0;
	}




	for(i = 0; i < p->NumAbilities; i++){
		fgets(buf,100,f);
		free(p->abilities[i]);
		p->abilities[i]=(char*)malloc(sizeof(char)*strlen(buf)+1);
		strcpy(p->abilities[i], buf);
		p->abilities[i][strlen(buf)-1] = '\0';

		p->strength_ability[i]=atoi(fgets(buf,100,f));
		p->endurance_ability[i]=atoi(fgets(buf,100,f));
		p->hp_ability[i]=atoi(fgets(buf,100,f));
		p->speed_ability[i]=atoi(fgets(buf,100,f));
		p->agility_ability[i]=atoi(fgets(buf,100,f));
		p->luck_ability[i]=atoi(fgets(buf,100,f));
	}
	fgets(buf,100,f);
	p->name = (char *) malloc(sizeof(char)*strlen(buf)+1);
	strcpy(p->name,buf);
	p->name[strlen(buf)-1] = '\0';
	p->platanito_cheat = 0;
	

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
int getPlatanito_player(Player *p){
	if(!p)return ERROR;
	return p->platanito_cheat;
}


Status changeStrength_player(Player*p,int strength){
	if(!p)return ERROR;
	p->stats[0]=p->stats[0]+strength;
	if(p->stats[0]<=0)p->stats[0]=1;
	if(p->stats[0]>p->limit_stats[0])p->stats[0]=p->limit_stats[0];
	return OK;
}

Status changeEndurance_player(Player*p,int endurance){
	if(!p)return ERROR;
	p->stats[1]=p->stats[1]+endurance;
	if(p->stats[1]<=0)p->stats[1]=1;
	if(p->stats[1]>p->limit_stats[1])p->stats[1]=p->limit_stats[1];
	return OK;
}

Status changeHp_player(Player*p,int hp){
	if(!p)return ERROR;
	p->stats[2]=p->stats[2]+hp;
	if(p->stats[2]<=0)p->stats[2]=0;
	if(p->stats[2]>p->limit_stats[2])p->stats[2]=p->limit_stats[2];
	return OK;
}

Status changeSpeed_player(Player*p,int speed){
	if(!p)return ERROR;
	p->stats[3]=p->stats[3]+speed;
	if(p->stats[3]<=0)p->stats[3]=1;
	if(p->stats[3]>p->limit_stats[3])p->stats[3]=p->limit_stats[3];
	return OK;
}

Status changeAgility_player(Player*p,int agility){
	if(!p)return ERROR;
	p->stats[4]=p->stats[4]+agility;
	if(p->stats[4]<=0)p->stats[4]=1;
	if(p->stats[4]>p->limit_stats[4])p->stats[4]=p->limit_stats[4];
	return OK;
}

Status changeLuck_player(Player*p,int luck){
	if(!p)return ERROR;
	p->stats[5]=p->stats[5]+luck;
	if(p->stats[5]<=0)p->stats[5]=1;
	if(p->stats[5]>p->limit_stats[5])p->stats[5]=p->limit_stats[5];
	return OK;
}

Status changePlatanito_player(Player*p){
	if(!p)return ERROR;
	p->platanito_cheat = 1;
	return OK;
}





char * getAbilityName_player(Player *p,int n){
 if(!p) return NULL;
 return p->abilities[n];

}
int *getAbilities_player(Player *p,int n){
	int *aux;
	if(!p||n<0)return NULL;
	aux=(int*)malloc(sizeof(int)*6);
	

	aux[0]=p->strength_ability[n];
	aux[1]=p->endurance_ability[n];
	aux[2]=p->hp_ability[n];
	aux[3]=p->speed_ability[n];
	aux[4]=p->agility_ability[n];
	aux[5]=p->luck_ability[n];
	return aux;
	
}


Status add_player_stats(Player* p,int n){
    if(!p||n>4||n<0)return ERROR;
    int *buff;
    buff=(int*)malloc(sizeof(int)*6);
    buff=getAbilities_player(p,n-1);
    changeStrength_player(p, buff[0]);
    changeEndurance_player(p, buff[1]);
    changeHp_player(p, buff[2]);
    changeSpeed_player(p, buff[3]);
    changeAgility_player(p, buff[4]);
    changeLuck_player(p, buff[5]);
    free(buff);
    return OK;
}

Status less_player_stats(Player* p,int n){
	if(!p||n>4||n<0)return ERROR;
    int *buff;
    buff=(int*)malloc(sizeof(int)*6);
    buff=getAbilities_player(p,n-1);
    changeStrength_player(p, -buff[0]);
    changeEndurance_player(p, -buff[1]);
    changeSpeed_player(p, -buff[3]);
    changeAgility_player(p, -buff[4]);
    changeLuck_player(p, -buff[5]); 
    free(buff);
    return OK;
}









Player *copy_player(Player*p1){
	if(!p1)return NULL;
	int i = 0;
	Player* p = ( Player *) malloc( sizeof( Player ));
	if( !p ) return NULL;
	p->name = (char *)malloc(sizeof(char)*10);
	strcpy( p->name, p1->name );
	if( !p->name ){
		free( p );
		return NULL;
	}
	

	
	p->col=p1->col;
	p->row=p1->row;

	p->show=p1->show;
	p->wai = p1->wai;

	p->num_stats = p1->num_stats;
	p->stats = (int *) malloc(sizeof(int)*p1->num_stats);
	p->stats = setDefStats(p);
	p->name_stats = (char **) malloc(sizeof(char *)*p->num_stats);
	p->limit_stats = (int *) malloc(sizeof(int)*p->num_stats);
	for(i = 0; i < p->num_stats; i++){
		p->name_stats[i] = (char *) malloc(sizeof(char)*strlen(p1->name_stats[i])+1);
		strcpy(p->name_stats[i], p1->name_stats[i]);
		p->limit_stats[i] = p1->limit_stats[i];
	}

	p->NumAbilities = p1->NumAbilities;
	if(p->NumAbilities>4){
		printf("ERROR no puede haber tantas habilidades");
		return NULL;
	}
	
	p->abilities=(char**)malloc(sizeof(char*)*4);

	for(i=0;i<4;i++){
	p->abilities[i]=(char*)malloc(sizeof(char)*strlen(p1->abilities[i]+1));
	strcpy (p->abilities[i], p1->abilities[i]);


	p->strength_ability[i]=p1->strength_ability[i];
	p->endurance_ability[i]=p1->endurance_ability[i];
	p->hp_ability[i]=p1->hp_ability[i];
	p->speed_ability[i]=p1->speed_ability[i];
	p->agility_ability[i]=p1->agility_ability[i];
	p->luck_ability[i]=p1->luck_ability[i];
	}
	strcpy(p->name,p1->name);
	p->platanito_cheat = p1->platanito_cheat;
	return p;
	
}


Player* create_enemy(FILE * f) { 
	int i = 0;
	char buf[100];
	Player* p = ( Player *) malloc( sizeof( Player ));
	if( !p ) return NULL;
	
	

	
	p->col=atoi(fgets(buf,100,f));
	p->row=atoi(fgets(buf,100,f));
	p->wai = atoi(fgets(buf,100,f));
	p->id = atoi(fgets(buf,100,f));
	p->show=fgetc(f);
	p->num=0;

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
		p->stats[i]=atoi(fgets(buf, 100, f));
	}

	p->NumAbilities = atoi(fgets(buf,100,f));
	if(p->NumAbilities>4){
		printf("ERROR no puede haber tantas habilidades");
		return NULL;
	}

	p->abilities=(char**)malloc(sizeof(char*)*4);

	for(i=0;i<4;i++){
	p->abilities[i]=(char*)malloc(sizeof(char)*20);
	strcpy (p->abilities[i], "vacio");


	p->strength_ability[i]=0;
	p->endurance_ability[i]=0;
	p->hp_ability[i]=0;
	p->speed_ability[i]=0;
	p->agility_ability[i]=0;
	p->luck_ability[i]=0;
	}




	for(i = 0; i < p->NumAbilities; i++){
		fgets(buf,100,f);
		free(p->abilities[i]);
		p->abilities[i]=(char*)malloc(sizeof(char)*strlen(buf)+1);
		strcpy(p->abilities[i], buf);

		p->strength_ability[i]=atoi(fgets(buf,100,f));
		p->endurance_ability[i]=atoi(fgets(buf,100,f));
		p->hp_ability[i]=atoi(fgets(buf,100,f));
		p->speed_ability[i]=atoi(fgets(buf,100,f));
		p->agility_ability[i]=atoi(fgets(buf,100,f));
		p->luck_ability[i]=atoi(fgets(buf,100,f));
	}
	fgets(buf,100,f);
	p->name = (char *)malloc(sizeof(char)*strlen(buf)+1);
	strcpy(p->name,buf);
	p->name[strlen(buf)-1] = '\0';
	p->platanito_cheat = 0;
	

	return p;
}	

int getNum_player(Player *p){
	if(!p)return ERROR;
	return p->num;
}
Status changeNum_player(Player *p){
	if(!p)return ERROR;
	p->num++;
	return OK;
}
Status changeStats_player(Player *p,int num){
	if(!p||num<0)return ERROR;
	changeHp_player(p,num);
        changeStrength_player(p,num);
        changeEndurance_player(p,num);
        changeAgility_player(p,num);
        changeSpeed_player(p,num);
        changeLuck_player(p,num);
        return OK;
}
Status switchHP_player(Player *p,int new){
	if(!p||new<0)return ERROR;
	p->stats[2]=new;
	if(p->stats[2]>p->limit_stats[2])p->stats[2]=p->limit_stats[2];
	return OK;
}
