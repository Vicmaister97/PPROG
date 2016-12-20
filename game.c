
#include "game.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define NORTH    0
#define SOUTH    2
#define EAST     1
#define WEST     3
#define HERE     4


#include <unistd.h>
#include <termios.h>

char getch() {
        char buf = 0;
        struct termios old = {0};
        if (tcgetattr(0, &old) < 0)
                perror("tcsetattr()");
        old.c_lflag &= ~ICANON;
        old.c_lflag &= ~ECHO;
        old.c_cc[VMIN] = 1;
        old.c_cc[VTIME] = 0;
        if (tcsetattr(0, TCSANOW, &old) < 0)
                perror("tcsetattr ICANON");
        if (read(0, &buf, 1) < 0)
                perror ("read()");
        old.c_lflag |= ICANON;
        old.c_lflag |= ECHO;
        if (tcsetattr(0, TCSADRAIN, &old) < 0)
                perror ("tcsetattr ~ICANON");
        return (buf);
}

/*
  Reads a key from the keyboard. If the key is a "regular" key it
  returns its ascii code; if it is an arrow key, it returns one of the
  four interface directions with the "minus" sign
*/
int _read_key() {
  char choice;
  choice = getch();


  if (choice == 27 && getch() == '[') { /* The key is an arrow key */
    choice = getch();

    switch(choice) {
    case('A'):
      return -NORTH;
    case('B'):
      return -SOUTH;
    case('C'):
      return -EAST;
    case('D'):
      return -WEST;
    default:
      return -HERE;
    }
  }
  else
    return choice;
}



struct _Game{
	intrf *ic;
	World *w;
};


static void prepare_game(Game *gm){
	int i = 0, col, row, num_obj;
	int obj_row[_get_num_objects_space(getWaI_player(getPlayer_world(gm->w)), gm->w)], obj_col[_get_num_objects_space(getWaI_player(getPlayer_world(gm->w)), gm->w)];
	char obj[_get_num_objects_space(getWaI_player(getPlayer_world(gm->w)), gm->w)];

	if(!gm) return;

	col = getCol_player(getPlayer_world(gm->w));
	row = getRow_player(getPlayer_world(gm->w));
	num_obj = _get_num_objects_space(getWaI_player(getPlayer_world(gm->w)),gm->w);
	
	for( ; i < num_obj; i++){
	    obj[i] = getPicture_object(getObjectsSpace_world(gm->w,getWaI_player(getPlayer_world(gm->w)))[i]);
	    obj_row[i] = getRow_object(getObjectsSpace_world(gm->w, getWaI_player(getPlayer_world(gm->w)))[i]);
	    obj_col[i] = getCol_object(getObjectsSpace_world(gm->w, getWaI_player(getPlayer_world(gm->w)))[i]);
	}
	
  	setPlayData_intrf(gm->ic, getSymbol_player(getPlayer_world(gm->w)), obj, _get_num_objects_space(getWaI_player(getPlayer_world(gm->w)), gm->w), row ,col , obj_col, obj_row);
  	
  	row = pictRows_Space(getByID_world(gm->w,getWaI_player(getPlayer_world(gm->w))));
  	col = pictCols_Space(getByID_world(gm->w,getWaI_player(getPlayer_world(gm->w))));
  	setField_intrf(gm->ic, row, col, getPict_Space(getByID_world(gm->w, getWaI_player(getPlayer_world(gm->w)))));

}

static void draw_game(Game *gm){

	if(!gm) return;

	setMenu_intrf(gm->ic, "Hey", getStats_player(getPlayer_world(gm->w)), 10, 2);
	drawField_intrf(gm->ic, 0);
	addObjects_intrf(gm->ic);
	setStats_intrf(gm->ic, getStats_player(getPlayer_world(gm->w)));

	fprintf(stdout, "%c[%d;%dH", 27, getRow_player(getPlayer_world(gm->w))+2, getCol_player(getPlayer_world(gm->w))+3);
	fflush(stdout);

}


Game *create_game(char *filesp, char *fileob, char *filepl, char *fileic){
	Game *gm;

	if(!filesp || !fileob || !fileic || !filepl)
		return NULL;

	gm = (Game *) malloc(sizeof(Game));
	gm->w = create_world(filesp, fileob, filepl);
	gm->ic = create_intrf(fileic);

	prepare_game(gm);
	draw_game(gm);

	return gm;
}

static void write_object_missing_intrf(Game *gm, int ob_id){
	char buf[50];
	sprintf(buf, "Locked! You need %d to unlock the space", -ob_id);
	extra_write_message_object_intrf(gm->ic, buf);
	return;
}


void play_game(Game *gm){
	int ret = 0, new, aux;

	if(!gm) return;

	while(1){
		if(isOnDoor_intrf(gm->ic)){
			aux = - _read_key();			
			if(ret == aux){
				ret = movePlayer_world(gm->w, ret);
				if(ret < 0){
					write_object_missing_intrf(gm, ret);
					ret = aux;
				}
				else{
					modRow_player(getPlayer_world(gm->w), 6);
					modCol_player(getPlayer_world(gm->w), 6);
					prepare_game(gm);
					draw_game(gm);
				}
			}
			else if(aux != ret && (aux + ret)%2 == 0){
				ret = movePlayer_intrf(gm->ic, aux);
				if(ret == NORTH || ret == SOUTH){
					new = getRow_player(getPlayer_world(gm->w));
					if(ret == NORTH)
						new --;
					else
						new ++;
					modRow_player(getPlayer_world(gm->w),new);
				}
				else if(ret == EAST || ret == WEST){
					new = getCol_player(getPlayer_world(gm->w));
					if(ret == EAST)
						new ++;
					else
						new --;
					modCol_player(getPlayer_world(gm->w), new);
				}
				else ;

				if(isOnObject_intrf(gm->ic)){
					removeObject(gm->ic, getRow_player(getPlayer_world(gm->w)), getCol_player(getPlayer_world(gm->w)));		
					pick_object(getObjectByCoordinates_world(gm->w, getRow_player(getPlayer_world(gm->w)), getCol_player(getPlayer_world(gm->w)), getWaI_player(getPlayer_world(gm->w))));	
				}
			}			
		}

		else{	
			ret = movePlayer_intrf(gm->ic, - _read_key());
			if(ret >= 0){
				if(ret == NORTH || ret == SOUTH){
					new = getRow_player(getPlayer_world(gm->w));
					if(ret == NORTH)
						new --;
					else
						new ++;
					modRow_player(getPlayer_world(gm->w),new);
				}
				else if(ret == EAST || ret == WEST){
					new = getCol_player(getPlayer_world(gm->w));
					if(ret == EAST)
						new ++;
					else
						new --;
					modCol_player(getPlayer_world(gm->w), new);
				}
				else ;

				if(isOnObject_intrf(gm->ic)){
					removeObject(gm->ic, getRow_player(getPlayer_world(gm->w)), getCol_player(getPlayer_world(gm->w)));		
					pick_object(getObjectByCoordinates_world(gm->w, getRow_player(getPlayer_world(gm->w)), getCol_player(getPlayer_world(gm->w)), getWaI_player(getPlayer_world(gm->w))));
				}

			}
		}
	}	
}

void delete_game(Game *gm){
	if(gm->w)
		delete_world(gm->w);
	if(gm->ic)
		delete_intrf(gm->ic);
	if(gm)
		free(gm);
}
