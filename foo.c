

#include <stdio.h>




main() {

/* load the world */
	world *w;

	while(1) {

		int curr = p_whereAmI(w_getPlayer(w));
		space *cs = w_getById(w, curr);
		char *c = s_short_desc(cs);
		printf("%s\n", c);
		int r = s_pictRows(cs);

		char **pict = s_getPict(cs);
		for (int i=0; i<r; i++) 
			printf("%s\n", pict[i]);

		/* Print current room */

		char buf[100];
		fgets(buf, 100, stdin);
		if buf[0] == 'n' {
			int err = w_movePlayer(w, NORTH)
		}
		else if buf[0] == 's' {
			int err = w_movePlayer(w, SOUTH)
		}
		else if buf[0] == 'e' {
			int err = w_movePlayer(w, EAST)
		}
		else if buf[0] == 'w' {
			int err = w_movePlayer(w, WEST)
		}
		else  {
			printf("wha?\n");
			err = 0;
		}
		if (err) {
			printf("Error: %d\n", err);
		} else {
			printf("Done!\n");
		}
	}
	

}



space *_get_by_id(world, *w, int id) {
    space **s = w->map->space;
    for (int i=0; i<w->map->size; i++)
        if (s_getId(s[i])==id) 
            return s[i];
    return NULL; 
}


int w_movePlayer(wodld *w, int dir) {

    int sid = p_whereAmI(w->player);
    space *here = _get_by_id(w, id);
    int newsp = s_get_neigh(here, dir);
    if (!newsp) {
        return 1;
    }
    /* check for locked door */
    p_goto(w->player, newsp);
    return 0;

}