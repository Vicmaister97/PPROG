 

#include "myintrf.h"
#include "world.h"
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


int main(){

	World *w = create_world("testintrfsp.txt", "testintrfob.txt","testintrf_player.txt");
	intrf *ic = create_intrf("testintrf_dim.txt");
	int *stats = getStats_player(getPlayer_world(w));

	char obj[_get_num_objects_space(getWaI_player(getPlayer_world(w)), w)]; 
	int i = 0;
	int obj_row[_get_num_objects_space(getWaI_player(getPlayer_world(w)), w)], obj_col[_get_num_objects_space(getWaI_player(getPlayer_world(w)), w)];
	int aux[_get_num_objects_space(getWaI_player(getPlayer_world(w)), w)];
	char str[10];
	strcpy(str, "Hey");

	for(; i < _get_num_objects_space(getWaI_player(getPlayer_world(w)),w); i++)
		aux[i] = i;
	
	for(i = 0; i < _get_num_objects_space(getWaI_player(getPlayer_world(w)),w); i++){
    obj[i] = getPicture_object(getObjectsSpace_world(w,getWaI_player(getPlayer_world(w)))[i]);
    obj_row[i] = getRow_object(getObjectsSpace_world(w, getWaI_player(getPlayer_world(w)))[i]);
    obj_col[i] = getCol_object(getObjectsSpace_world(w, getWaI_player(getPlayer_world(w)))[i]);
  }

	setPlayData_intrf(ic, getSymbol_player(getPlayer_world(w)), obj, _get_num_objects_space(getWaI_player(getPlayer_world(w)), w), getRow_player(getPlayer_world(w)) , getCol_player(getPlayer_world(w)), obj_col, obj_row);
	setField_intrf(ic, pictRows_Space(getByID_world(w,getWaI_player(getPlayer_world(w)))),pictCols_Space(getByID_world(w,getWaI_player(getPlayer_world(w)))) , getPict_Space(getByID_world(w,getWaI_player(getPlayer_world(w)))));

  setMenu_intrf(ic, str, stats, 10, 2);
	
	drawField_intrf(ic, 0);
	addObjects_intrf(ic);	
	
	setStats_intrf(ic, stats);	
	
	fprintf(stdout, "%c[%d;%dH", 27, getRow_player(getPlayer_world(w))+2, getCol_player(getPlayer_world(w))+3);
	fflush(stdout);
	while(1){
		movePlayer_intrf(ic, - _read_key());

    if(isOnDoor_intrf(ic)){
      movePlayer_world(w, - _read_key());
      char obja[_get_num_objects_space(getWaI_player(getPlayer_world(w)), w)]; 
      int obj_rowa[_get_num_objects_space(getWaI_player(getPlayer_world(w)), w)], obj_cola[_get_num_objects_space(getWaI_player(getPlayer_world(w)), w)];
      int auxa[_get_num_objects_space(getWaI_player(getPlayer_world(w)), w)];

      for(i = 0; i < _get_num_objects_space(getWaI_player(getPlayer_world(w)),w); i++)
        auxa[i] = i;
      
      for(i = 0; i < _get_num_objects_space(getWaI_player(getPlayer_world(w)),w); i++){
        obja[i] = getPicture_object(getObjectsSpace_world(w,getWaI_player(getPlayer_world(w)))[i]);
        obj_rowa[i] = getRow_object(getObjectsSpace_world(w, getWaI_player(getPlayer_world(w)))[i]);
        obj_cola[i] = getCol_object(getObjectsSpace_world(w, getWaI_player(getPlayer_world(w)))[i]);
      }

      setPlayData_intrf(ic, getSymbol_player(getPlayer_world(w)), obja, _get_num_objects_space(getWaI_player(getPlayer_world(w)), w), getRow_player(getPlayer_world(w)) , getCol_player(getPlayer_world(w)), obj_cola, obj_rowa);
      setField_intrf(ic, pictRows_Space(getByID_world(w,getWaI_player(getPlayer_world(w)))),pictCols_Space(getByID_world(w,getWaI_player(getPlayer_world(w)))) , getPict_Space(getByID_world(w,getWaI_player(getPlayer_world(w)))));
      
      drawField_intrf(ic, 0);
      addObjects_intrf(ic);    
      
      fprintf(stdout, "%c[%d;%dH", 27, getRow_player(getPlayer_world(w))+2, getCol_player(getPlayer_world(w))+3);
      fflush(stdout);
      }
  }

	delete_world(w);
	delete_intrf(ic);

	return 1;

}

