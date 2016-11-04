#ifndef INTERFACE_H
#define INTERFACE_H
 
#include <rectangles.h>  


#define BACKGROUND   40  /* Black background */
#define FOREGROUND   32  /* Green foreground... for a "retro" look */

#define NORTH    0
#define EAST     1
#define SOUTH    2
#define WEST     3
#define HERE     4


typedef struct {
	int rows;
	int cols;
	sc_rectangle *menu;
	sc_rectangle *field;
	sc_rectangle *extra;
	int menu_rows;
	int extra_cols;
	int map_cols;
	int map_rows;
	char **map;
	char player;
	int player_row, player_col;
	/*OBJETOS*/
	int num_obj;
	char *obj;
	int *obj_row, *obj_col;
	char *menu_cap, *extra_cap;
	int menucap_col, extracap_row, extracap_col; /*Dónde está*/
	int *stats;
	int stats_col; /*Calculamos a ojo y es la columna en la que van a estar todas ordenadas*/
} intrf;

intrf *create_intfr(int rows, int cols, int menu, int extra){
	if(rows < 0 || cols < 0) return NULL;
	intrf *ic = (intrf *)malloc(sizeof(intrf));
	ic->rows = rows;
	ic->cols = cols;
	ic->menu_rows = menu;
	ic->extra_cols = extra;
	ic->menu = win_new(2, 20, 50, 15, 49, 60);
	ic->field = win_new();
	ic->extra = win_new();
	ic->player = 'p';
	ic->num_obj = 0;

	fprintf(stdout, "%c[2J", 27);
	_i_redraw(ic);

	return ic;

}

int setMenu_intrf(intrf *ic, char *menu_cap, int *stats, int stats_col, int cap_col){
	if(!ic) return ERROR;
	strcpy(ic->menu_cap, menu_cap);
	ic->stats = stats;
	ic->stats_col = stats_col;
	ic->menucap_col = cap_col;

	_cap_redraw(ic);
	/*win_cls(itf->field);
  fflush(stdout)obliga al buffer a vaciarse e imprimirlo todo;*/
	return OK;
}

int setPlayData_intrf(intrf *ic, char player, char *obj, int num_obj, int player_row, int player_col, int *obj_col, int *obj_row){
	if(!ic)	return ERROR;
	ic->player=player;
	ic->player_row=player_row;
	ic->player_col=player_col;
}

int setBoard_intrf











