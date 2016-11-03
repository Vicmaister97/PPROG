#include "world.h"
#include "player.h"
#include "object.h"
#include "types.h"

int main(){

	
	int j = 0;
	World *w = create_world("test1sp.txt", "test1ob.txt");
		


	while(j <= 3){

		int i = 0;
		int location = 0;
		char move;

		int curr_id = getWaI_player(getPlayer_world(w));
		Space *curr_sp = getByID_world(w, curr_id);
		char *desc_sp = desc(curr_sp);
		Object **obs = getObjectsSpace_world(w, curr_id);
		int rows = pictRows_space(curr_sp);
		char **pict = getPict_space(curr_sp);
		printf("%s\n",desc_sp);
		for ( ; i<rows; i++) 
			printf("%s\n", pict[i]);

		
		while(obs[i]){
			
			char *desc_ob = getDesc_object(obs[i]);
			printf("%s\n",desc_ob);
			
			location = getLocation_object(obs[i]);
			printf("Not in inventory: %d", location);

			pick_object(obs[i]);
			location = getLocation_object(obs[i]);
			printf("In inventory: %d", location);

			drop_object(obs[i]);
			location = getLocation_object(obs[i]);
			printf("Dropped: %d", location);

			i++;

		}

		fgetc(move, 1, stdin);
		if(move == 'n')
			movePlayer_world(w,0);
		else if (buf[0] == 's')
			movePlayer_world(w, 2);
		else if (buf[0] == 'e')
			movePlayer_world(w, 1);
		else if (buf[0] == 'w')
			movePlayer_world(w, 3);
		else printf("wha?\n");

		j++;

	}

	delete_world(w);

}