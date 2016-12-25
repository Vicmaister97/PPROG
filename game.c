
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

/*no dibuja nada, solo asigna datos de la interfaz*/
static void prepare_game(Game *gm){
	int i = 0, col, row, num_obj;
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
	
  	setPlayData_intrf(gm->ic, getSymbol_player(getPlayer_world(gm->w)), obj, _get_num_objects_space(getWaI_player(getPlayer_world(gm->w)), gm->w), row ,col , obj_col, obj_row);
  	
  	row = pictRows_Space(getByID_world(gm->w,getWaI_player(getPlayer_world(gm->w))));
  	col = pictCols_Space(getByID_world(gm->w,getWaI_player(getPlayer_world(gm->w))));
  	setField_intrf(gm->ic, row, col, getPict_Space(getByID_world(gm->w, getWaI_player(getPlayer_world(gm->w)))));

  	free(obs);
}

/*dibuja la interfaz, objetos y demás*/
static void draw_game(Game *gm){

	if(!gm) return;

	setMenu_intrf(gm->ic, "Hey", getStats_player(getPlayer_world(gm->w)), 12, 2, getNameStats_player(getPlayer_world(gm->w)), getNumStats_player(getPlayer_world(gm->w)), getLimitStats_player(getPlayer_world(gm->w)));
	drawField_intrf(gm->ic, 0);
	addObjects_intrf(gm->ic);
	setStats_intrf(gm->ic, getStats_player(getPlayer_world(gm->w)));

	fprintf(stdout, "%c[%d;%dH", 27, getRow_player(getPlayer_world(gm->w))+2, getCol_player(getPlayer_world(gm->w))+3);
	fflush(stdout);

}

/*void fgetId_object(void *dummy, char *obj, char **str, int n) {
	int num = getId_object ()
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
	if (CoP_assoc(cop, "prueba_internal", fgetId_object) == -1)
		return;
	if (CoP_assoc(cop, "cmd2_internal", cmd2) == -1)
		return;
	if (CoP_assoc(cop, "cmd3_internal", cmd3) == -1)
		return;
	if (CoP_assoc(cop, "cmd4_internal", cmd4) == -1)
		return;
	if (CoP_assoc(cop, "error_internal", err) == -1)
		return;
} */


Game *create_game(char *filesp, char *fileob, char *filepl, char *fileic, char *cmdnofile){
	Game *gm;
	FILE *cmdfile;

	if(!filesp || !fileob || !fileic || !filepl)
		return NULL;

	_term_init();
	cmdfile = fopen("cmdfile.txt", "r");
	gm = (Game *) malloc(sizeof(Game));
	gm->w = create_world(filesp, fileob, filepl);
	gm->ic = create_intrf(fileic);
	gm->cop = CoP_create(cmdfile);

	/*asociemos_cosas(gm->cop);*/

	prepare_game(gm);
	draw_game(gm);

	fclose(cmdfile);
	return gm;
}

/*cuando tratas de entrar en un espacio bloqueado y necesitas
un objeto que no tienes, te imprime el mensaje de error
con el nombre del objeto*/
static void write_object_missing_intrf(Game *gm, int ob_id, int flag){
	char buf[50];
	char *aux = NULL;
	aux = getName_object(getByIdObject_world(gm->w, ob_id));
	char *name = (char *) malloc(sizeof(char)*strlen(aux)+1);
	int fin = strlen(aux);
	strcpy(name, aux);
	name[fin-1] = '\0';
	if(flag)
		sprintf(buf, "Locked! You need %s to unlock the space", name);
	else
		sprintf(buf, "Dark! You need %s to see smthing", name);
	extra_write_message_object_intrf(gm->ic, buf);
	free(name);
	return;
}

/*cuando encuentras un objeto te imprime un mensaje y su nombre*/
static void extra_write_message_found_object_intrf(Game *gm, Object *ob){
	char buf[50];
	char *aux = NULL;
	aux = getName_object(ob);
	char *name = (char *) malloc(sizeof(char)*strlen(aux)+1);
	int fin = strlen(aux);
	strcpy(name, aux);
	name[fin-1] = '\0';
	sprintf(buf, "You have found %s!", name);
	extra_write_message_object_intrf(gm->ic, buf);
	free(name);
	return;	
}


/*esto es lo que realmente hace que el jugador se mueva.
tomamos la fila o columna del payer y la aumentamos o disminuimos
dependiendo de la direccion pasada "ret" y modificamos la struct.
despues miramos si está encima de un objeto, y entonces
llamamos a esas tres preciosas funciones que lo borran de la interfaz
y mueven ahí al jugador, escriben el mensaje de que has encontrado
un objeto, y cambian su struct para marcar que está en inventario*/
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

/*esta se supone que debería de leer algo, que lo hace, y utilizar el cop*/
static void _read_smth(Game *gm, char c){
	char buf[50];
	int i = 0;
	char aux = c;
	prepare_to_write_cmd_intrf(gm->ic);
	while(aux != 10){
		buf[i] = aux;
		printf("%c", aux);
		aux = _read_key();
		i++;
	}
	buf[i] = '\0';
	extra_write_message_object_intrf(gm->ic, buf);
	/*CoP_execute(c, buf, (void *) gm->w);*/
}

/*este es el bucle turbio en proceso de formarse, el juego en sí*/
/*ahora mismo pulsndo supr sales del bucle eterno, de ahí lo de aux == -126*/
void play_game(Game *gm){
	int ret = 0, aux, sh;
	/*char buf[50];*/
	
	if(!gm) return;

	while(1){
		/*simplemente sitúa el puntero de escritura abajo*/
		prepare_to_write_cmd_intrf(gm->ic);
		/*si el jugador está en una puerta (un hueco en el marco del espacio)..*/
		if(isOnDoor_intrf(gm->ic)){
			aux = - _read_key();
			if(aux == -126)
				return;
			/*como he cambiado el signo las flechas son números positivos ahora*/
			if(aux >= 0){
				/*si te mueves en la misma dirección que has hecho antes (como que vas
				más allá de la puerta), intenta moverlo de espacio, y si ret es un 
				número negativo, quiere decir que te falta un objeto (con id -ret (brillante esto)).
				si ret es positivo (estoy sudando de cde) te modifica la fila y columna
				del player a 6,6 (porque me apetece) y vuelve a cargar la interfaz con el nuevo espacio*/		
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
						extra_write_message_object_intrf(gm->ic, desc_Space(getByID_world(gm->w, getWaI_player(getPlayer_world(gm->w)))));
					}
					else{
						doors_al(gm, aux);
						prepare_game(gm);
						draw_game(gm);
						extra_write_message_object_intrf(gm->ic, desc_Space(getByID_world(gm->w, getWaI_player(getPlayer_world(gm->w)))));
					}
				}
				/*si en una puerta en el norte no pulsas la tecla de arriba sino 
				la del sur esto te permite salir del hueco ese.
				no sé por qué, pero esto se necesita*/
				/*darse cuenta de que NORTH = 0 y SOUTH = 2 (0+2=2..2%2=0) y 
				EAST = 1 y WEST = 3 ... ya se intuye*/
				else if(aux != ret && (aux + ret)%2 == 0){
					ret = movePlayer_intrf(gm->ic, aux);
					if(ret >= 0)
						moving_moving(gm, ret);
				}	
			}
			/*si la tecla pulsada no es una flecha se lee lo que se
			escribe y se debería llamar al cop en la función _read_smth*/
			else{
				/*prepare_to_write_cmd_intrf(gm->ic);*/
				clear_cmd_intrf(gm->ic);
				_read_smth(gm, -aux);		
			}
		}

		/*más de lo mismo pero cuando no estás en una puerta
		(mucho menos turbio)*/
		else{		
			sh = - _read_key();	
			if(sh == -43)
				display_inventory(gm->ic, getPicturesObjectsInventory_world(gm->w), getNamesObjectsInventory_world(gm->w), _get_num_objects_inventory(gm->w));
			/*sprintf(buf, "%d", sh);
			extra_write_message_object_intrf(gm->ic, buf);*/
			if(sh == -126)
				return;													
			
			/*printf("%d", ret);*/
			if(sh >= 0){
				ret = movePlayer_intrf(gm->ic, sh);
				moving_moving(gm, ret);
			}
			else{
				/*prepare_to_write_cmd_intrf(gm->ic);*/
				clear_cmd_intrf(gm->ic);
				_read_smth(gm, -sh);
			}
		}
		/*prepare_to_write_cmd_intrf(gm->ic);*/
	}	
}

void delete_game(Game *gm){
	if(gm->w)
		delete_world(gm->w);
	if(gm->ic)
		delete_intrf(gm->ic);
	/*if(gm->cop)
	CoP_delete(gm->cop);
	*/
	if(gm)
		free(gm);
}
