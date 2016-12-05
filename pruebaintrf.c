
#include "myintrf.h"
#include "world.h"


int main(){

	World *w = create_world("testintrfsp.txt", "testintrfob.txt");
	intrf *ic = create_intrf(20, 20, 10, 10);
	int *stats = getStats_player(getPlayer_world(w));
	char obj[4]; 
	int i = 0;
	int obj_row[4], obj_col[4];

	for( ; i < 4; i++){
		obj[i] = 'o';
		obj_col[i] = i+1;
		obj_row[i] = i+1;
	}

	setMenu_intrf(ic, "Hey", stats, 15, 9);
	setPlayData_intrf(ic, 'P', obj, 4, 1, 2, obj_col, obj_row);	
	setField_intrf(ic, 4, 4, getPict_Space(getByID_world(w,getWaI_player(getPlayer_world(w)))));
	addObjects_intrf(ic, obj_row, 4);
	removeObject(ic, 3, 3);
	drawField_intrf(ic, obj_row, 0);
	setStats_intrf(ic, stats);
	movePlayer_intrf(ic, EAST);

	fflush(stdout);
	while(1)
		;

	delete_world(w);
	delete_intrf(ic);

	return 1;

}