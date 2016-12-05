 

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

	World *w = create_world("testintrfsp.txt", "testintrfob.txt");
	intrf *ic = create_intrf(40, 80, 19, 7);
	int *stats = getStats_player(getPlayer_world(w));

	char obj[2]; 
	int i = 0;
	int obj_row[2], obj_col[2];
	int aux[2];
	char str[10];
	strcpy(str, "Hey");

	for(; i < 2; i++)
		aux[i] = i;
	
	for(i = 0; i < 2; i++){
		obj[i] = 'o';
		obj_col[i] = i+10;
		obj_row[i] = i+16;
	}

	
	setPlayData_intrf(ic, 'P', obj, 2, 6, 6, obj_col, obj_row);
	setField_intrf(ic, 26, 54, getPict_Space(getByID_world(w,getWaI_player(getPlayer_world(w)))));
	setMenu_intrf(ic, str, stats, 10, 2);
	
	drawField_intrf(ic, aux, 0);
	addObjects_intrf(ic, obj_row, 2);	
	/*removeObject(ic, 3, 3);*/
	
	setStats_intrf(ic, stats);
	/*movePlayer_intrf(ic, SOUTH);*/
	
	
	fprintf(stdout, "%c[%d;%dH", 27, 8, 8);
	fflush(stdout);
	while(1)
		movePlayer_intrf(ic, - _read_key());

	delete_world(w);
	delete_intrf(ic);

	return 1;

}

