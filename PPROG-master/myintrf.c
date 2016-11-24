
#include "myintrf.h"


struct _intrf{
	/*General info*/
	int rows; /*Total rows, only rows-2 usasble*/
	int cols; /*Total columns, only cols-2 usable*/
	sc_rectangle *menu; 
	sc_rectangle *field;
	sc_rectangle *extra;
	int menu_cols; /*Columns for the menu*/
	int extra_rows; /*Rows for the extra*/
	/*Map info*/
	int map_cols; /*Columns for the map*/
	int map_rows; /*Rows for the map*/
	char **map; /*Picture of the map*/
	/*Player info*/
	char player; /*Representation for the player*/
	int player_row, player_col; /*Coordenates of the player*/
	/*Object info*/
	int num_obj; /*Number of objects*/
	char *obj; /*Array containing the representations of the ojects*/
	int *obj_row, *obj_col; /*Arrays containing the coordenates of the objects*/
	/*Captions info*/
	char *menu_cap, *extra_cap; /*Captions*/
	int menucap_col, extracap_row, extracap_col; /*Situation for the captions*/
	/*Menu info*/
	int *stats; 
	int stats_col; /*Calculamos a ojo y es la columna en la que van a estar todas ordenadas*/
};


void _i_redraw(intrf *ic){
	int k = 0;

	fprintf(stdout, "%c[1;1H", 27);
	fprintf(stdout, "+");

	/*Marco superior*/
	for( ; k < (ic->cols - ic->menu_cols); k++)
		fprintf(stdout, "-");
	fprintf(stdout, "+");

	k++;
	for( ; k < ic->cols-1; k++)
		fprintf(stdout, "-");
	fprintf(stdout, "+");

	/*Marco inferior*/
	fprintf(stdout, "%c[%d;1H", 27, ic->rows);
	fprintf(stdout, "+");

	for(k = 0; k < ic->cols-1; k++)
		fprintf(stdout, "-");
	fprintf(stdout, "+");

	/*Separación horizontal*/
	fprintf(stdout, "%c[%d;1H", 27, ic->rows - ic->extra_rows);
	fprintf(stdout, "+");
	for(k = 0; k < ic->cols-1; k++)
		fprintf(stdout, "-");
	fprintf(stdout, "+");

	/*Verticales*/
	for(k = 2; k < ic->rows; k++){
		fprintf(stdout, "%c[%d;1H", 27, k);
		fprintf(stdout, "|");
		if(k < ic->rows - ic->extra_rows){
			fprintf(stdout, "%c[%d;%dH", 27, k, ic->cols - ic->menu_cols);
			fprintf(stdout, "|");
		}
		fprintf(stdout, "%c[%d;%dH", 27, k, ic->cols);
		fprintf(stdout, "|");
	}
	return;
}

void _cap_redraw(intrf *ic){
	win_bgcol(ic->menu, BACKGROUND);
	win_fgcol(ic->menu, FOREGROUND);
	win_cls(ic->menu);

	win_write_line_at(ic->menu, 2, ic->menucap_col, ic->menu_cap);
	setStats_intrf(ic, ic->stats);
	return;
}




/*Sets the general info and creates the windows but doesn't draw anything inside them*/
intrf *create_intrf(int rows, int cols, int menu, int extra){
	intrf *ic = NULL;

	if(rows < 0 || cols < 0) return NULL;
	
	ic = (intrf *)malloc(sizeof(intrf));
	ic->rows = rows;
	ic->cols = cols;
	ic->menu_cols = menu;
	ic->extra_rows = extra;
	ic->menu = win_new(1, cols-menu, rows-extra-2, menu, BACKGROUND, FOREGROUND);
	ic->field = win_new(1, 1, rows-extra-2, cols-menu-2, BACKGROUND, FOREGROUND);
	ic->extra = win_new(rows-extra, 1, extra, cols-2, BACKGROUND, FOREGROUND);
	ic->player = 'p';
	ic->num_obj = 0;

	fprintf(stdout, "%c[2J", 27);
	_i_redraw(ic);

	return ic;

}

/*Sets the menu info and redraws the window*/
int setMenu_intrf(intrf *ic, char *menu_cap, int *stats, int stats_col, int cap_col){
	if(!ic) return 0;
	ic->menu_cap = menu_cap;
	ic->stats = stats; /*?*/
	ic->stats_col = stats_col;
	ic->menucap_col = cap_col;

	_cap_redraw(ic);
	win_cls(ic->menu);
  	fflush(stdout); /*obliga al buffer a vaciarse e imprimirlo todo*/
	return 1;
}

/*Sets the playfield data (player and objects) but doesn't draw anything*/
int setPlayData_intrf(intrf *ic, char player, char *obj, int num_obj, int player_row, int player_col, int *obj_col, int *obj_row){
	if(!ic)	return 0;
	/*Player*/
	ic->player = player;
	ic->player_row = player_row;
	ic->player_col = player_col;

	/*Objects*/
	ic->num_obj = num_obj;
	ic->obj = obj;
	ic->obj_row = obj_row;
	ic->obj_col = obj_col;

	return 1;

}

/*Sets the map info but doesn't print anything*/
int setField_intrf(intrf *ic, int map_rows, int map_cols, char **map){
	if(!ic || map_rows > ic->rows || map_cols < 0 || map_cols >= (ic->cols - ic->menu_cols)) return 0;

	ic->map_cols = map_cols;
	ic->map_rows = map_rows;
	ic->map = map;

	return 1;
}

/*Draws the selected objects in their positions?????*/
/*sel_obj is an array containing the indexes? of the objects that we want to print*/
int addObjects_intrf(intrf *ic, int *sel_obj, int sel_num_obj){
	int i = 0;

	if(!ic || !sel_obj) return 0;

	for( ; i < sel_num_obj; i++){
		int ind = sel_obj[i];
		win_write_char_at(ic->field, ic->obj_row[ind], ic->obj_col[ind], ic->obj[ind]);
	}	
	return 1;

}

/*Removes an object*/
int removeObject(intrf *ic, int row, int col){
	int i = 0;
	for( ; i < ic->num_obj; i++){
		if(ic->obj_row[i] == row && ic->obj_col[i] == col){
			win_write_char_at(ic->field, row, col, ' ');
			win_write_char_at(ic->field, ic->player_row, ic->player_col, ic->player);
			return 1;
		}
	}
	return 0;
}

/*Draws the field with all the info*/
/*int *sel_obj is the array containing the indexes of the objects that we want to print*/
int drawField_intrf(intrf *ic, int *sel_obj, int clear){
	int i = 0;

	if(!ic || !sel_obj) return 0;

	if(clear)
		win_cls(ic->field);
	
	for( ; i < ic->map_rows; i++)
		win_write_line_at(ic->field, i, 0, ic->map[i]);
	addObjects_intrf(ic, sel_obj, sizeof(sel_obj)/sizeof(sel_obj[0]));
	win_write_char_at(ic->field, ic->player_row, ic->player_col, ic->player);

	return 1;
}

/*Prints the stats*/
int setStats_intrf(intrf *ic, int *stats){
	int i = 0;
	char buf[10];

	if(!ic || !stats) return 0;

	ic->stats = stats;
	for( ; i < sizeof(ic->stats)/sizeof(ic->stats[0]); i++){
		win_write_line_at(ic->menu, 0, ic->stats_col, "     ");
		sprintf(buf, "%3d", stats[i]);
		win_write_line_at(ic->menu, i, ic->stats_col, buf);
	}
	return 1;
}


/*Moves the player and redraws it*/
int movePlayer_intrf(intrf *ic, int dir){
	if(!ic || dir < 0 || dir > 4) return 0;

	if(dir == NORTH || dir == SOUTH){
		int new_row = ic->player_row;
		if(dir == NORTH)
			new_row --;
		else
			new_row ++;
		if(new_row >= 0 && new_row <= (ic->rows - ic->extra_rows) && ic->map[new_row][ic->player_col] == ' '){
			win_write_char_at(ic->field, ic->player_row, ic->player_col, ' ');
			ic->player_row = new_row;
			win_write_char_at(ic->field, ic->player_row, ic->player_col, ic->player);
			return 1;
		}
	}
	else if(dir == EAST || dir == WEST){
		int new_col = ic->player_col;
		if(dir == EAST)
			new_col ++;
		else
			new_col --;
		if(new_col >= 0 && new_col <= (ic->cols - ic->menu_cols) && ic->map[ic->player_row][new_col] == ' '){
			win_write_char_at(ic->field, ic->player_row, ic->player_col, ' ');
			ic->player_col = new_col;
			win_write_char_at(ic->field, ic->player_row, ic->player_col, ic->player);
			return 1;
		}
	}
	else if(dir == HERE){
		win_write_char_at(ic->field, ic->player_row, ic->player_col, ' ');
		win_write_char_at(ic->field, ic->player_row, ic->player_col, ic->player);
		return 1;
	}
	return 0;
}

int isOnObject_intrf(intrf *ic){
	int i = 0;
	if(!ic) return 0;
	for( ; i < ic->num_obj; i++)
		if(ic->obj_row[i] == ic->player_row && ic->obj_col[i] == ic->player_col)
			return 1;
	return 0;
}

void delete_intrf(intrf *ic){
	if(!ic) return;
	win_delete(ic->field);
	win_delete(ic->menu);
	win_delete(ic->extra);
	free(ic);
}







