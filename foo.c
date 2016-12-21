


#include "world.h"
#include <curses.h>


int main() {
	int j = 0;
/* load the world */
	World *w = create_world("test1sp.txt","ficheroob.txt");

	while(j <= 2) {
		int err;
		int i = 0;
		char buf[100];
		int curr_id = getWaI_player(getPlayer_world(w));
		Space *curr_sp = getByID_world(w, curr_id);
		char *desc = desc_Space(curr_sp);
		int rows = pictRows_Space(curr_sp);
		char **pict = getPict_Space(curr_sp);
		j++;
		printf("\n%s\n", desc);
		for ( ; i<rows; i++) 
			printf("%s\n", pict[i]);

		/* Print current room */

		
		/*fgets(buf, 100, stdin);
		if (buf[0] == 'n')
			err = movePlayer_world(w, 0);
		else if (buf[0] == 's')
			err = movePlayer_world(w, 2);
		else if (buf[0] == 'e')
			err = movePlayer_world(w, 1);
		else if (buf[0] == 'w')
			err = movePlayer_world(w, 3);
		else {
			printf("wha?\n");
			err = 0;
		}*/

		if(getch()!= '\033') printf("nop");
		getch();
		i = getch();
		if(i == 65)
			err = movePlayer_world(w, 0);
		else if(i == 66)
			err = movePlayer_world(w, 2);
		else if(i == 67)
			err = movePlayer_world(w, 1);
		else if(i == 68)
			err = movePlayer_world(w, 3);
		else{
			printf("wha?\n");
			err = 0;
		}

		if (err) printf("Error: %d\n", err);

		else printf("Done!\n");
	}
	delete_world(w);

	return 0;

}

