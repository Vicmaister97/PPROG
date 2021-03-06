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
int setMenu_intrf(intrf *ic, char *menu_cap, int *stats, int stats_col, int cap_col, char **name_stats, int num_stats, int *limit_stats);
int setPlayData_intrf(intrf *ic, char player, char *obj, int num_obj, int player_row, int player_col, int *obj_col, int *obj_row, /*new stuff*/char *enemy,int num_enemy,int *enemy_col,int *enemy_row, int num_people, int *people_col, int *people_row, char *people);
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
void prepare_to_write_cmd_intrf(intrf *ic);
void clear_cmd_intrf(intrf *ic);
int dark_spaces_intrf(intrf *ic);
void display_inventory(intrf *ic, char *pict, char **names, int num);
void smth_useful(intrf *ic, int col);
void extra_write_lngmess_intrf(intrf *ic, char *mg);
void prepare_to_write_mgextra(intrf *ic);


/*enemy functions*/
int isOnEnemy_intrf(intrf *ic,int row,int col);
int addEnemies_intrf(intrf *ic);
int removeEnemy(intrf *ic, int row, int col);
int isNearEnemy_intrf(intrf *ic, int *row, int *col);

int addPeople_intrf(intrf *ic);
int isNearPeople_intrf(intrf *ic, int *row, int *col);
int isOnPeople(intrf *ic, int row, int col);

void delete_internal_intrf(intrf *ic);

#endif
