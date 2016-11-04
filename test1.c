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
		char move[10];
		int err;

		int curr_id = getWaI_player(getPlayer_world(w));
		Space *curr_sp = getByID_world(w, curr_id);
		char *desc_sp = desc_space(curr_sp);
		Object **obs = getObjectsSpace_world(w, curr_id);
		int rows = pictRows_space(curr_sp);
		char **pict = getPict_space(curr_sp);
		int num_obj = _get_num_objects_space(curr_id,w);
		printf("\n%s\n",desc_sp);
		for ( ; i<rows; i++) 
			printf("%s\n", pict[i]);
		i = 0;
		
		while(i < num_obj){
			
			char *desc_ob = getDesc_object(obs[i]);
			printf("\n%s\n",desc_ob);
			
			location = getLocation_object(obs[i]);
			printf("\nNot in inventory: %d", location);

			pick_object(obs[i]);
			location = getLocation_object(obs[i]);
			printf("\nIn inventory: %d", location);

			drop_object(obs[i]);
			location = getLocation_object(obs[i]);
			printf("\nDropped: %d\n", location);

			i++;

		}

		fgets(move, 10, stdin);
		if(move[0] == 'n')
			err = movePlayer_world(w,0);
		else if (move[0] == 's')
			err = movePlayer_world(w, 2);
		else if (move[0] == 'e')
			err = movePlayer_world(w, 1);
		else if (move[0] == 'w')
			err = movePlayer_world(w, 3);
		else{
			printf("wha?\n");
			err = 0;
		}
		if(err) printf("Error: %d\n", err);
		else printf("Done!\n");

		j++;
		free(obs);

	}


	delete_world(w);
	return 0;

}