
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

struct termios initial;

/*
  Initializes the terminal in such a way that we can read the input
  without echo on the screen
*/
void _term_init() {
	struct termios new;	          /*a termios structure contains a set of attributes about 
					  how the terminal scans and outputs data*/
		
	tcgetattr(fileno(stdin), &initial);    /*first we get the current settings of out 
						 terminal (fileno returns the file descriptor 
						 of stdin) and save them in initial. We'd better 
						 restore them later on*/
	new = initial;	                      /*then we copy them into another one, as we aren't going 
						to change ALL the values. We'll keep the rest the same */
	new.c_lflag &= ~ICANON;	              /*here we are setting up new. This line tells to stop the 
						canonical mode (which means waiting for the user to press 
						enter before sending)*/
	new.c_lflag &= ~ECHO;                 /*by deactivating echo, we tell the terminal NOT TO 
						show the characters the user is pressing*/
	new.c_cc[VMIN] = 1;                  /*this states the minimum number of characters we have 
					       to receive before sending is 1 (it means we won't wait 
					       for the user to press 2,3... letters)*/
	new.c_cc[VTIME] = 0;	              /*I really have no clue what this does, it must be somewhere in the book tho*/
	new.c_lflag &= ~ISIG;                 /*here we discard signals: the program won't end even if we 
						press Ctrl+C or we tell it to finish*/

	tcsetattr(fileno(stdin), TCSANOW, &new);  /*now we SET the attributes stored in new to the 
						    terminal. TCSANOW tells the program not to wait 
						    before making this change*/
}

/*
  Reads a key from the keyboard. If the key is a "regular" key it
  returns its ascii code; if it is an arrow key, it returns one of the
  four interface directions with the "minus" sign
*/
int _read_key() {
  char choice;
  choice = fgetc(stdin);


  if (choice == 27 && fgetc(stdin) == '[') { /* The key is an arrow key */
    choice = fgetc(stdin);

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
	CoP *cop;
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

void cmd1(void *dummy, char *obj, char **str, int n) {
	world *q = (world *) dummy;
	printf("cmd1: %s\n", str[0]);
}


void cmd2(void *dummy, char *obj, char **str, int n) {
	printf("cmd2: %s\n", str[0]);
}


void cmd3(void *dummy, char *obj, char **str, int n) {
	printf("cmd3: %s\n", str[0]);
}


void cmd4(void *dummy, char *obj, char **str, int n) {
	drop_object(getByIdObject_world((World *)dummy), n);
}


void err(void *dummy, char *obj, char **str, int n) {
	printf("error: %s\n", str[0]);
}

static void asociemos_cosas(CoP *cop){
	if (CoP_assoc(cop, "cmd1_internal", cmd1) == -1)
		return;
	if (CoP_assoc(cop, "cmd2_internal", cmd2) == -1)
		return;
	if (CoP_assoc(cop, "cmd3_internal", cmd3) == -1)
		return;
	if (CoP_assoc(cop, "cmd4_internal", cmd4) == -1)
		return;
	if (CoP_assoc(cop, "error_internal", err) == -1)
		return;
}


Game *create_game(char *filesp, char *fileob, char *filepl, char *fileic, char *cmdnofile){
	Game *gm;
	FILE *cmdfile;

	if(!filesp || !fileob || !fileic || !filepl)
		return NULL;

	_term_init();
	cmdfile = fopen(cmdnofile, "r");
	gm = (Game *) malloc(sizeof(Game));
	gm->w = create_world(filesp, fileob, filepl);
	gm->ic = create_intrf(fileic);
	gm->cop = CoP_create(cmdfile);

	asociemos_cosas(gm->cop);

	prepare_game(gm);
	draw_game(gm);

	fclose(cmdfile);
	return gm;
}

static void write_object_missing_intrf(Game *gm, int ob_id){
	char buf[50];
	char *aux = NULL;
	aux = getName_object(getByIdObject_world(gm->w, -ob_id));
	char *name = (char *) malloc(sizeof(char)*strlen(aux)+1);
	int fin = strlen(aux);
	strcpy(name, aux);
	name[fin-1] = ' ';
	sprintf(buf, "Locked! You need %sto unlock the space", name);
	extra_write_message_object_intrf(gm->ic, buf);
	free(name);
	return;
}

static void extra_write_message_found_object_intrf(Game *gm, Object *ob){
	char buf[50];
	char *aux = NULL;
	aux = getName_object(ob);
	char *name = (char *) malloc(sizeof(char)*strlen(aux)+1);
	int fin = strlen(aux);
	strcpy(name, aux);
	name[fin-1] = ' ';
	sprintf(buf, "You have found %s!", name);
	extra_write_message_object_intrf(gm->ic, buf);
	free(name);
	return;	
}

static void moving_moving(Game *gm, int ret){
	int new;
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
		extra_write_message_found_object_intrf(gm, getObjectByCoordinates_world(gm->w, getRow_player(getPlayer_world(gm->w)), getCol_player(getPlayer_world(gm->w)), getWaI_player(getPlayer_world(gm->w))));
		pick_object(getObjectByCoordinates_world(gm->w, getRow_player(getPlayer_world(gm->w)), getCol_player(getPlayer_world(gm->w)), getWaI_player(getPlayer_world(gm->w))));
	}
}

static void _read_smth(Game *gm){
	char buf[50];
	fgets(buf, 50, stdin);
	/*extra_write_message_object_intrf(gm->ic, buf);*/
	CoP_execute(c, buf, (void *) gm->w);
}


void play_game(Game *gm){
	int ret = 0, aux;
	
	if(!gm) return;

	while(1){
		prepare_to_write_cmd_intrf(gm->ic);
		/*sprintf(buf, "%d %d ", getRow_player(getPlayer_world(gm->w)), getCol_player(getPlayer_world(gm->w)));
		extra_write_message_object_intrf(gm->ic, buf);*/
		if(isOnDoor_intrf(gm->ic)){
			aux = - _read_key();
			if(aux >= 0){		
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
					/*printf("%d", ret);*/
					if(ret >= 0)
						moving_moving(gm, ret);
				}	
			}
			else{
				prepare_to_write_cmd_intrf(gm->ic);
				_read_smth(gm);		
			}
		}

		else{																
			ret = movePlayer_intrf(gm->ic, - _read_key());
			/*printf("%d", ret);*/
			if(ret >= 0)
				moving_moving(gm, ret);
			else{
				prepare_to_write_cmd_intrf(gm->ic);
				_read_smth(gm);
			}
		}
		prepare_to_write_cmd_intrf(gm->ic);
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
