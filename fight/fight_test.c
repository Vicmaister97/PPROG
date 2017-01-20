#include "fight.h"

int main (){
 printf("hey");	
 Player *p,*foe,*aux;
 
 p=create_player("testintrf_player.txt");
 foe=create_player("enemy1.txt");
 if(!p)printf("Error en la creacion del player\n");
 if(!foe)printf("Error en la creacion del enemigo\n");
 join_fight(p,foe);

 return 0;
}
