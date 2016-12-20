#ifndef INTERFACE_H
#define INTERFACE_H
 
#include "rectangles.h" 
#include <string.h> 


#define BACKGROUND   40  /* Black background */
#define FOREGROUND   32  /* Green foreground... for a "retro" look */

#define NORTH    0
#define EAST     1
#define SOUTH    2
#define WEST     3
#define HERE     4

typedef struct _intrf intrf;

intrf *create_intrf(const char*);
int setMenu_intrf(intrf *ic, char *menu_cap, int *stats, int stats_col, int cap_col);
int setPlayData_intrf(intrf *ic, char player, char *obj, int num_obj, int player_row, int player_col, int *obj_col, int *obj_row);
int setField_intrf(intrf *ic, int map_rows, int map_cols, char **map);
int addObjects_intrf(intrf *ic);
int removeObject(intrf *ic, int row, int col);
int drawField_intrf(intrf *ic, int clear);
int setStats_intrf(intrf *ic, int *stats);
int movePlayer_intrf(intrf *ic, int dir);
int isOnObject_intrf(intrf *ic);
void delete_intrf(intrf *ic);
void extra_write_message_object_intrf(intrf *ic, char *mg);
int isOnDoor_intrf(intrf *ic);

#endif
