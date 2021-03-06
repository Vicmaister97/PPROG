
#include "game.h"
#include "fight.h"
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

/*no dibuja nada, solo asigna datos de la interfaz*/
static void prepare_game(Game *gm){
	int i = 0, col, row, num_obj;
	/*enemy stuff*/
	int num_enemy;
	num_enemy = _get_num_enemies_space(getWaI_player(getPlayer_world(gm->w)),gm->w);
	int enemy_row[num_enemy];
	int enemy_col[num_enemy];
	char enemy[num_enemy];
	Player **enemies = getEnemiesSpace_world(gm->w,getWaI_player(getPlayer_world(gm->w)));

	for( ; i < num_enemy; i++){
	    enemy[i] = getSymbol_player(enemies[i]);
	    enemy_row[i] = getRow_player(enemies[i]);
	    enemy_col[i] = getCol_player(enemies[i]);
	}



	int obj_row[_get_num_objects_space(getWaI_player(getPlayer_world(gm->w)), gm->w)], obj_col[_get_num_objects_space(getWaI_player(getPlayer_world(gm->w)), gm->w)];
	char obj[_get_num_objects_space(getWaI_player(getPlayer_world(gm->w)), gm->w)];
	Object **obs = getObjectsSpace_world(gm->w,getWaI_player(getPlayer_world(gm->w)));

	if(!gm) return;

	col = getCol_player(getPlayer_world(gm->w));
	row = getRow_player(getPlayer_world(gm->w));
	num_obj = _get_num_objects_space(getWaI_player(getPlayer_world(gm->w)),gm->w);
	
	for( ; i < num_obj; i++){
	    obj[i] = getPicture_object(obs[i]);
	    obj_row[i] = getRow_object(obs[i]);
	    obj_col[i] = getCol_object(obs[i]);
	}
	
  	setPlayData_intrf(gm->ic, getSymbol_player(getPlayer_world(gm->w)), obj, _get_num_objects_space(getWaI_player(getPlayer_world(gm->w)), gm->w), row ,col , obj_col, obj_row/*enemy*/,enemy,num_enemy,enemy_col,enemy_row);
  	
  	row = pictRows_Space(getByID_world(gm->w,getWaI_player(getPlayer_world(gm->w))));
  	col = pictCols_Space(getByID_world(gm->w,getWaI_player(getPlayer_world(gm->w))));
  	setField_intrf(gm->ic, row, col, getPict_Space(getByID_world(gm->w, getWaI_player(getPlayer_world(gm->w)))));

  	free(obs);
}

/*dibuja la interfaz, objetos y demás*/
static void draw_game(Game *gm){

	if(!gm) return;

	setMenu_intrf(gm->ic, "Hey", getStats_player(getPlayer_world(gm->w)), 12, 2, getNameStats_player(getPlayer_world(gm->w)), getNumStats_player(getPlayer_world(gm->w)), getLimitStats_player(getPlayer_world(gm->w)));
	drawField_intrf(gm->ic, 1);
	addObjects_intrf(gm->ic);
	/*new stuff*/
	addEnemies_intrf(gm->ic);
	setStats_intrf(gm->ic, getStats_player(getPlayer_world(gm->w)));

	fflush(stdout);

}

int cmd1(void *dummy, char *obj, char **str, int n) {
	return printf("cmd1: %s\n", str[0]);
}


int cmd2(void *dummy, char *obj, char **str, int n) {
	Game *gm = (Game *) dummy;
	Player *p = create_player("enemy1.txt");
	join_fight(getPlayer_world(gm->w), p);
	return 1;
}

int use_object_game(Game *gm, Object *po){
    if(!gm || !po || !isInInventory(po)) return 0;
    modStats_player(getPlayer_world(gm->w), getProp_object(po));
    setStats_intrf(gm->ic, getStats_player(getPlayer_world(gm->w)));
    return 1; 
}


int cmd3(void *dummy, char *obj, char **str, int n) {
	Game *gm = (Game *) dummy;
	return use_object_game(gm, getObjectByName_wordl(gm->w, obj));
}


int cmd4(void *dummy, char *obj, char **str, int n) {
	Game *gm = (Game *) dummy;
	return drop_object(getByIdObject_world(gm->w, getId_object(getObjectByName_wordl(gm->w, obj))));
}


int err(void *dummy, char *obj, char **str, int n) {
	return printf("error: %s\n", str[0]);
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


Game *create_game(char *filesp, char *fileob, char *filepl, char *fileic, char *cmdnofile,char *fileEnemy){
	Game *gm;
	FILE *cmdfile;

	if(!filesp || !fileob || !fileic || !filepl)
		return NULL;

	_term_init();
	cmdfile = fopen(cmdnofile, "r");
	gm = (Game *) malloc(sizeof(Game));
	gm->w = create_world(filesp, fileob, filepl,fileEnemy);
	gm->ic = create_intrf(fileic);
	
	gm->cop = CoP_create(cmdfile);
	
	asociemos_cosas(gm->cop);
	prepare_game(gm);
	draw_game(gm);
	printf("\n\n\nHola 6\n");

	fclose(cmdfile);
	return gm;
}

static void write_object_missing_intrf(Game *gm, int ob_id, int flag){
	char buf[50];
	char *aux = NULL;
	aux = getName_object(getByIdObject_world(gm->w, ob_id));
	char *name = (char *) malloc(sizeof(char)*strlen(aux)+1);
	strcpy(name, aux);
	if(flag)
		sprintf(buf, "Locked! You need %s to unlock the space", name);
	else
		sprintf(buf, "Dark! You need %s to see smthing", name);
	extra_write_message_object_intrf(gm->ic, buf);
	free(name);
	return;
}

static void extra_write_message_found_object_intrf(Game *gm, Object *ob){
	char buf[50];
	char *aux = NULL;
	aux = getName_object(ob);
	char *name = (char *) malloc(sizeof(char)*strlen(aux)+1);
	strcpy(name, aux);
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
	if(isOnEnemy_intrf(gm->ic)){
		
	}
}

/*Para que el jugador entre por la puerta del otro espacio*/
static void doors_al(Game *gm, int aux){
	int new_row = getRow_player(getPlayer_world(gm->w));
	int new_col = getCol_player(getPlayer_world(gm->w));
	if(aux == NORTH || aux == SOUTH){
		if(aux == NORTH)
			new_row += -2 + pictRows_Space(getByID_world(gm->w, getWaI_player(getPlayer_world(gm->w))));
		else
			new_row -= -2 + pictRows_Space(getByID_world(gm->w, getWaI_player(getPlayer_world(gm->w))));
	}
	else if(aux == EAST || aux == WEST){
		if(aux == WEST)
			new_col += -2 + pictCols_Space(getByID_world(gm->w, getWaI_player(getPlayer_world(gm->w))));
		else
			new_col -= -2 + pictCols_Space(getByID_world(gm->w, getWaI_player(getPlayer_world(gm->w))));
	}
	modRow_player(getPlayer_world(gm->w), new_row);
	modCol_player(getPlayer_world(gm->w), new_col);
}

static void _read_smth(Game *gm, char c){
	char buf[50];
	int i = 0;
	char aux = c;
	prepare_to_write_cmd_intrf(gm->ic);
	while(aux != 10){
		if(aux == 127 && i > 0){
			i--;
			smth_useful(gm->ic, i+3);
		}
		else{
			buf[i] = aux;
			printf("%c", aux);
			i++;
		}
		aux = _read_key();
	}
	buf[i] = '\0';
	extra_write_message_object_intrf(gm->ic, buf);
	CoP_execute(gm->cop, buf, gm);
}


void play_game(Game *gm){
	int ret = 0, aux, sh;
	
	if(!gm) return;

	while(1){
		prepare_to_write_cmd_intrf(gm->ic);
		if(isOnDoor_intrf(gm->ic)){
			aux = - _read_key();
			if(aux == -126)
				return;
			if(aux >= 0){
				if(ret == aux){
					ret = movePlayer_world(gm->w, ret);
					if(ret < 0){
						write_object_missing_intrf(gm, -ret, 1);
						ret = aux;
					}
					else if(ret > 2){
						doors_al(gm, aux);
						write_object_missing_intrf(gm, ret/3, 0);
						dark_spaces_intrf(gm->ic);
						prepare_game(gm);
						draw_game(gm);
					}
					else{
						doors_al(gm, aux);
						prepare_game(gm);
						draw_game(gm);
					}
				}
				else if(aux != ret && (aux + ret)%2 == 0){
					ret = movePlayer_intrf(gm->ic, aux);
					if(ret >= 0)
						moving_moving(gm, ret);
				}	
			}
			else{
				clear_cmd_intrf(gm->ic);
				_read_smth(gm, -aux);		
			}
		}

		else{		
			sh = - _read_key();	
			if(sh == -43)
				display_inventory(gm->ic, getPicturesObjectsInventory_world(gm->w), getNamesObjectsInventory_world(gm->w), _get_num_objects_inventory(gm->w));
	
			if(sh == -126)
				return;													
			
			if(sh >= 0){
				ret = movePlayer_intrf(gm->ic, sh);
				moving_moving(gm, ret);
			}
			else{
				clear_cmd_intrf(gm->ic);
				_read_smth(gm, -sh);
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
