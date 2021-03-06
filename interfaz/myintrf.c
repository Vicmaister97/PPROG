
#include "myintrf.h"


struct _intrf{
	/*Para que todo sea de colorines*/
	sc_rectangle *total;
	/*General info*/
	int rows; /*Total rows, only rows-2 usasble*/
	int cols; /*Total columns, only cols-2 usable*/
	sc_rectangle *menu; 
	sc_rectangle *field;
	sc_rectangle *extra;
	int menu_cols; /*Columns for the menu*/
	int menu_rows;
	int extra_cols;
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
	for(k = 2; k < (ic->cols - ic->menu_cols - 3); k++)
		fprintf(stdout, "-");
	fprintf(stdout, "+");

	fprintf(stdout, " +");
	k++;
	for( ; k < ic->cols-2; k++)
		fprintf(stdout, "-");
	fprintf(stdout, "+");

	/*Marco inferior*/
	fprintf(stdout, "%c[%d;1H", 27, ic->rows - 1);
	fprintf(stdout, "+");

	for(k = 2; k < (ic->cols - ic->menu_cols - 3); k++)
		fprintf(stdout, "-");
	fprintf(stdout, "+");

	fprintf(stdout, " +");
	k++;
	for( ; k < ic->cols-2; k++)
		fprintf(stdout, "-");
	fprintf(stdout, "+");

	/*Separaciones horizontales*/
	fprintf(stdout, "%c[%d;1H", 27, ic->rows - ic->extra_rows - 2);
	fprintf(stdout, "+");
	for(k = 2; k < (ic->cols - ic->menu_cols - 3); k++)
		fprintf(stdout, "-");
	fprintf(stdout, "+");

	fprintf(stdout, "%c[%d;1H", 27, ic->rows - ic->extra_rows - 3);
	fprintf(stdout, "+");
	for(k = 2; k < (ic->cols - ic->menu_cols - 3); k++)
		fprintf(stdout, "-");
	fprintf(stdout, "+");

	/*Verticales*/
	for(k = 2; k < ic->rows - ic->extra_rows - 3; k++){
		fprintf(stdout, "%c[%d;1H", 27, k);
		fprintf(stdout, "|");
		fprintf(stdout, "%c[%d;%dH", 27, k, ic->cols - ic->menu_cols - 3);
		fprintf(stdout, "|");
	}
	
	k += 2;
	for( ; k < ic->rows - 1; k++){
		fprintf(stdout, "%c[%d;1H", 27, k);
		fprintf(stdout, "|");
		fprintf(stdout, "%c[%d;%dH", 27, k, ic->cols - ic->menu_cols - 3);
		fprintf(stdout, "|");
	}

	for(k = 2; k < ic->rows -1; k++){
		fprintf(stdout, "%c[%d;%dH", 27, k, ic->cols - ic->menu_cols - 1);
		fprintf(stdout, "|");
		fprintf(stdout, "%c[%d;%dH", 27, k, ic->cols);
		fprintf(stdout, "|");
	}

	return;
}

void _cap_redraw(intrf *ic){

	win_bgcol(ic->menu, BACKGROUND);
	win_fgcol(ic->menu, FOREGROUND);
	win_cls(ic->menu, 0);
	
	win_write_line_at(ic->menu, 1, 1, "Strength:    /100");
	win_write_line_at(ic->menu, 2, 1, "      HP:    /100");
	win_write_line_at(ic->menu, 3, 1, "   Speed:    /100");
	win_write_line_at(ic->menu, 4, 1, "  Wisdom:    /100");
	win_write_line_at(ic->menu, 5, 1, " Defense:    /100");
	win_write_line_at(ic->menu, 6, 1, "    Luck:    /100");
	win_write_line_at(ic->menu, 10, ic->menucap_col, ic->menu_cap);/*menucap_col ahora 9 porque si 
	no se mete en mierda y peta en esta funcion*/
	
	fflush(stdout);
	setStats_intrf(ic, ic->stats);
	return;
}




/*Sets the general info and creates the windows but doesn't draw anything inside them*/
intrf *create_intrf(const char* file_intrfc){
	intrf *ic = NULL;
	int rows,cols,menu,extra;
	FILE *pfi=fopen(file_intrfc,"r");
	char buf[100];

	rows=atoi(fgets(buf,100,pfi));
	cols=atoi(fgets(buf,100,pfi));
	menu=atoi(fgets(buf,100,pfi));
	extra=atoi(fgets(buf,100,pfi));
	if(rows < 0 || cols < 0) return NULL;


	ic = (intrf *)malloc(sizeof(intrf));
	ic->rows = rows;
	ic->cols = cols;
	ic->menu_cols = menu;
	ic->extra_rows = extra;
	ic->total = win_new(0, 0, rows, cols, BACKGROUND, FOREGROUND);
	ic->menu = win_new(1, cols-menu-1, rows-2, menu, BACKGROUND, FOREGROUND);
	ic->field = win_new(1, 1, rows-extra-2, cols-menu-2, BACKGROUND, FOREGROUND);
	ic->extra = win_new(rows-extra-1, 1, extra, cols-menu-2, BACKGROUND, FOREGROUND);
	ic->player = 'p';
	ic->num_obj = 0;
	ic->menu_cap=(char*)malloc(sizeof(char)*10);/*reservado para uso posterior que no pete*/

	fprintf(stdout, "%c[2J", 27);
	win_cls(ic->total, 1);
	_i_redraw(ic);

	return ic;

}

/*Sets the menu info and redraws the window*/
int setMenu_intrf(intrf *ic, char *menu_cap, int *stats, int stats_col, int cap_col){
	if(!ic) return 0;
	strcpy(ic->menu_cap, menu_cap);
	ic->stats = stats; /*?*/
	ic->stats_col = stats_col;
	ic->menucap_col = cap_col;

	_cap_redraw(ic);
	win_cls(ic->menu, 0);
  	fflush(stdout); /*obliga al buffer a vaciarse e imprimirlo todo*/
	return 1;
}

/*Sets the playfield data (player and objects) but doesn't draw anything*/
int setPlayData_intrf(intrf *ic, char player, char *obj, int num_obj, int player_row, int player_col, int *obj_col, int *obj_row){
	int i = 0;
	if(!ic)	return 0;
	/*Player*/
	ic->player = player;
	ic->player_row = player_row;
	ic->player_col = player_col;

	/*Objects*/
	ic->num_obj = num_obj;
	ic->obj = obj;
	ic->obj_row = (int *) malloc(sizeof(int)*num_obj);
	ic->obj_col = (int *) malloc(sizeof(int)*num_obj);
	for( ; i < num_obj; i++){
		ic->obj_row[i] = obj_row[i];
		ic->obj_col[i] = obj_col[i];
	}
	/*if(num_obj == 3){
		sprintf(buf, "%d %d %d %d %d %d", ic->obj_row[0], ic->obj_col[0], ic->obj_row[1], ic->obj_col[1], ic->obj_row[2], ic->obj_col[2]);
		extra_write_message_object_intrf(ic, buf);
	}*/
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

	for( ; i < sel_num_obj; i++)
		win_write_char_at(ic->field, ic->obj_row[i], ic->obj_col[i], ic->obj[i]);
	
	return 1;

}

/*Removes an object*/
int removeObject(intrf *ic, int row, int col){
	int i = 0;
	if(!ic) return 0;

	for( ; i < ic->num_obj; i++)
		if(ic->obj_row[i] == row && ic->obj_col[i] == col){
			ic->obj_row[i] *= -1;
			ic->obj_col[i] *= -1;
		}
	win_write_char_at(ic->field, row, col, ' ');
	win_write_char_at(ic->field, ic->player_row, ic->player_col, ic->player);
	return 1;
}

/*Draws the field with all the info*/
/*int *sel_obj is the array containing the indexes of the objects that we want to print*/
int drawField_intrf(intrf *ic, int *sel_obj, int clear){
	int i = 0;

	if(!ic || !sel_obj) return 0;

	if(clear)
		win_cls(ic->field, 0);
	
	for( ; i < ic->map_rows; i++)
		win_write_line_at(ic->field, i+1, 1, ic->map[i]);
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
	for( ; i < 6; i++){
		win_write_line_at(ic->menu, 3, ic->stats_col, " ");
		sprintf(buf, "%3d", stats[i]);
		win_write_line_at(ic->menu, i+1, ic->stats_col, buf);
	}
	return 1;
}


/*Moves the player and redraws it*/
/*El -1 viene de la diferencia entre field_rows/cols y map_rows/cols*/
int movePlayer_intrf(intrf *ic, int dir){
	if(!ic || dir < 0 || dir > 4) return 0;

	if(dir == NORTH || dir == SOUTH){
		int new_row = ic->player_row;
		/*printf("%d", ic->player_row);*/
		if(dir == NORTH)
			new_row --;
		else
			new_row ++;
		
		if(new_row >= 0 && new_row <= (ic->rows - ic->extra_rows) && ic->map[new_row - 1][ic->player_col - 1] == ' '){
			win_write_char_at(ic->field, ic->player_row, ic->player_col, ' ');
			ic->player_row = new_row;

			if(isOnObject_intrf(ic)){
				removeObject(ic, ic->player_row, ic->player_col);
				extra_write_message_object_intrf(ic, "You have found an object!");
			}
			else
				win_write_char_at(ic->field, ic->player_row, ic->player_col, ic->player);
			/*printf("%d", ic->player_row);*/
			return 1;
		}
	}
	else if(dir == EAST || dir == WEST){
		int new_col = ic->player_col;
		if(dir == EAST)
			new_col ++;
		else
			new_col --;

		if(new_col >= 0 && new_col <= (ic->cols - ic->menu_cols) && ic->map[ic->player_row - 1][new_col - 1] == ' '){
			win_write_char_at(ic->field, ic->player_row, ic->player_col, ' ');
			ic->player_col = new_col;
			if(isOnObject_intrf(ic)){
				removeObject(ic, ic->player_row, ic->player_col);
				extra_write_message_object_intrf(ic, "You have found an object!");
			}
			else
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
		/*sprintf(buf, "%d %d %d %d ", ic->obj_row[i], ic->obj_col[i], ic->player_row, ic->player_col);
		extra_write_message_object_intrf(ic, buf);*/
		if(ic->obj_row[i] == 
			ic->player_row && 
			ic->obj_col[i] == 
			ic->player_col)
			return 1;
	
	return 0;
}

int isOnDoor_intrf(intrf *ic){
	if(!ic) return 0;

	if(ic->player_col == 1 || ic->player_row == 1 || ic->player_row == ic->map_rows || ic->player_col == ic->map_cols) return 1;

	return 0;
}

void extra_write_message_object_intrf(intrf *ic, char * mg){
	/*char *str = malloc(sizeof(char)*strlen(mg) + 1);*/
	if(!ic) return;
	win_cls(ic->extra, 0);
	win_write_line_at(ic->extra, 2, 2, mg);
	/*win_write_line_at(ic->extra, 2, 2, str);*/
}

void delete_intrf(intrf *ic){
	if(!ic) return;
	free(ic->obj_row);
	free(ic->obj_col);
	free(ic->menu_cap);
	win_delete(ic->field);
	win_delete(ic->menu);
	win_delete(ic->extra);
	free(ic);
}

