#include <stdlib.h>
#include "assert.h"
#include "fight_a.h"


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

Fight* join_fight(Player* player, Player* foe){/*mirar a ver si hay que implementar funcion copy en player.c*/
    if (player==NULL ||foe==NULL) return NULL;
    Fight* fight=(Fight*) malloc (sizeof(fight));
    if(fight==NULL) return NULL;
    fight->player=player;/*aqui no deberia llamar a create_player,para no tener problemas en cambio de datos ya que has igualado 
    directamente punteros*/
    fight->preplayer=player;
    fight->foe=foe;
    fight->prefoe=foe;
    fight->round=1;
    fight->finish=0;
    int whatoption=0;
    goto Combat;

}
    
    
Combat:
    while (fight->finish==0){
        printf("\nRound %d ", fight->round);
        fight->round++;
        waitFor(1);
        printf("\e[2J\e[H");/*clear screen*/
        printf("\n¡FIGHT!");
        waitFor(1);
        printf("\e[2J\e[H");/*clear screen*/
        
        goto FightMenu;
    }
    
/*mirar a ver donde sale esto. en que parte de la interfaz*/
    /*debemos usar el cop*/
FightMenu:
        printf ("\nWhat are you going to do?\n");
        printf ("1. Fight\n");
        printf ("2. Inventory\n");
        printf ("3. Run away\n");
        scanf ("\n%d", &whatoption);
        switch ( whatoption ) {
         case '1':
            goto Fight;
            break;
         case '2':
            goto Inventory;
            break;
         case '3':
            goto RunAway;
            break;
         default:
            printf("%s, did you smoke too many joints?. Please choose a real option\n", getName_player(fight->player));
            goto FightMenu;
        }
        
RunAway:
    if (getSpeed_player(fight->player)>= getSpeed_player(fight->foe))
        changeHp_player(fight->preplayer,getHp_player(fight->player));
        printf ("\nYou do Santa Claus");
        return fight->preplayer;
    else {
        printf ("You are a fat bitch, better go gym next time");
        goto FightMenu;

Fight:
    waitFor(2);
    printf("\e[2J\e[H");/*clear screen*/
    printf ("\nChoose one of your four habilities.\n");
    printf ("1. %s\n", getAbilityName_player(fight->player, 0));
    printf ("2. %s\n", getAbilityName_player(fight->player, 1));
    printf ("3. %s\n", getAbilityName_player(fight->player, 2));
    printf ("4. %s\n", getAbilityName_player(fight->player, 3));
    scanf ("\n%d", &whatoption);
    if (whatoption<5 && whatoption>0) goto Resolution;
    else {
        printf("Did you smoke too many joints?. Please choose a real option\n");
        goto Fight;
        }

Resolution:
    /*[0]: Strength, [1]: Endurance, [2]: HP, [3]: Speed, [4]: Agility, [5]: Luck*/
    if(getSpeed_player(fight->player)>=getSpeed_player(fight->foe)){
        foe=resolve(fight->player, fight->foe, whatoption);
        player=resolve(fight->foe, fight->player, aleat_num(1,4));}
    else{
        player=resolve(fight->foe, fight->player, aleat_num(1,4));
        foe=resolve(fight->player, fight->foe, whatoption);}

    goto Combat;
/*p1 attacks and p2 defends*/    

/*hasta aqui estan player_fight las funciones para stats y mierdas*/



    


Player* resolve(Player* p1,Player* p2, int hab){ 
    int ad;
    int fail;
    double critic;
    int dmg;
    int rand;
    /*no entiendo esta funcion*/
    /*add_player_stats(p1 ,getAbilityName_player(p1, hab));/*CUIDADO QUE NO DE MENOS DE 0!*/

    ad=getStrength_player(p1)*getStrength_player(p1)/getEndurance_player(p2);
    rand=aleat_num(0,(getAgility_player(p1)+getAgility_player(p2)));
    if(rand<=(getAgility_player(p2)/2)) fail=0;
    else fail=1;
    rand=aleat_num(0,(getLuck_player(p1)+getLuck_player(p2)));
    if(rand<=(getLuck_player(p2)/3)) critic=0.5;
    else if (rand>=(2/3*getLuck_player(p1)+getLuck_player(p2))) critic=2;
    else critic=1;
    dmg=(int) ad*fail*critic;
    changeHp_player(p2,-dmg);
    /*no entiendo esta funcion*/
    /*less_player_stats(p1 ,getAbilityName_player(p1, hab));/*CUIDADO QUE NO DE MENOS DE 0! a arreglar*/
    if (getHp_player(p2)<=0) goto finish;
    return p1;
}

Finish:
if (getHp_player(fight->player)<=0){
    printf ("\nYou failed in your adventure, better luck next time");
    waitFor(10);
    return NULL;
}
printf ("\nWell done, you did it!")
return fFight->player;


Inventory:
    
    