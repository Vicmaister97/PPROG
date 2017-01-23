#include "assert.h"
#include "fight.h"


struct _Fight{
    Player* player;
    Player* foe;
    Player* preplayer;
    Player* prefoe; 
    int round;
    int finish;

} ;

void waitFor (unsigned int secs) {
    unsigned int retTime = time(0) + secs;   // Get finishing time.
    while (time(0) < retTime);               // Loop until it arrives.
}
int aleat_num(int inf, int sup)
{
	assert(inf <= sup);
	return inf + rand() % (sup - inf + 1);
}


Fight *join_fight(Player* player, Player* foe){/*mirar a ver si hay que implementar funcion copy en player.c*/
    if (player==NULL ||foe==NULL) return ERROR;
    Fight* fight=(Fight*) malloc (sizeof(Fight));
    if(fight==NULL) return ERROR;
    fight->player=player;/*aqui no deberia llamar a create_player,para no tener problemas en cambio de datos ya que has igualado 
    directamente punteros*/
    fight->preplayer=player;
    fight->foe=foe;
    fight->prefoe=foe;
    fight->round=0;
    fight->finish=0;


    
    return fight;
}

int getRound_fight(Fight *fight){
    if(!fight) return -1;
    return fight->round;
}

Status nextRound_fight(Fight *fight){
    if(!fight) return ERROR;
    fight->round++;
    return OK;
}

Bool isFinished_fight(Fight *fight){
    if(!fight || !fight->finish) return TRUE;
    return FALSE;
}

void finish_fight(Fight *fight){
    fight->finish = 1;
}

Player *getFoe_fight(Fight *fight){
    if(!fight) return NULL;
    return fight->foe;
}

Player *getPlayer_fight(Fight *fight){
    if(!fight) return NULL;
    return fight->player;
}


int RunAway(Fight *fight){
    if (getSpeed_player(fight->player)>= getSpeed_player(fight->foe)){

        switchHP_player(fight->preplayer,getHp_player(fight->player));
        return 0;
    }
    else 
        return 1;
 
}
