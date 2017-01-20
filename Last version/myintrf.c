
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
	sc_rectangle *cmd;
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
	
	/*Enemy info*/
	int num_enemy;
	char *enemy;
	int *enemy_row,*enemy_col;

	/*people info*/
	int  num_people;
	char *people;
	int *people_row, *people_col;


	/*Captions info*/
	char *menu_cap, *extra_cap; /*Captions*/
	int menucap_col, extracap_row, extracap_col; /*Situation for the captions*/
	/*Menu info*/
	int *stats; 
	char **name_stats;
	int num_stats;
	int *limit_stats;
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
	for( ; k < ic->cols-3; k++)
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
	for( ; k < ic->cols-3; k++)
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

	fprintf(stdout, "%c[%d;1H", 27, ic->rows - 3);
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
		if(k != ic->rows - 3){
			fprintf(stdout, "%c[%d;1H", 27, k);
			fprintf(stdout, "|");
			fprintf(stdout, "%c[%d;%dH", 27, k, ic->cols - ic->menu_cols - 3);
			fprintf(stdout, "|");
		}
		else
			;
	}

	for(k = 2; k < ic->rows -1; k++){
		fprintf(stdout, "%c[%d;%dH", 27, k, ic->cols - ic->menu_cols - 1);
		fprintf(stdout, "|");
		fprintf(stdout, "%c[%d;%dH", 27, k, ic->cols - 1);
		fprintf(stdout, "|");
	}

	return;
}

static void _print_justif_left(sc_rectangle *win, char *buf, int row, int col){
	int i = 0;
	for( ; i <= strlen(buf); i++)
		win_write_char_at(win, row, col-i, buf[strlen(buf)-i]);
}

void _cap_redraw(intrf *ic){

	int i = 0;
	char buf[5];

	win_bgcol(ic->menu, BACKGROUND);
	win_fgcol(ic->menu, FOREGROUND);
	win_cls(ic->menu, 0);
	
	for( ; i < ic->num_stats; i++){
		_print_justif_left(ic->menu, ic->name_stats[i], i+2, ic->stats_col);
		win_write_char_at(ic->menu, i+2, ic->stats_col-1, ':');
		win_write_char_at(ic->menu, i+2, ic->stats_col+4, '/');
		sprintf(buf, "%d", ic->limit_stats[i]);
		_print_justif_left(ic->menu, buf, i+2, ic->stats_col+8);
	}

	setStats_intrf(ic, ic->stats);
	win_write_line_at(ic->menu, 10, ic->menucap_col, ic->menu_cap);/*menucap_col ahora 9 porque si 
	no se mete en mierda y peta en esta funcion*/
	
	fflush(stdout);
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
	ic->field = win_new(1, 1, rows-extra-4, cols-menu-3, BACKGROUND, FOREGROUND);
	ic->extra = win_new(rows-extra-2, 1, extra-1, cols-menu-3, BACKGROUND, FOREGROUND);
	ic->cmd = win_new(rows-3, 1, 1, cols-menu-3, BACKGROUND, FOREGROUND);
	ic->player = 'p';
	ic->num_obj = 0;
	ic->num_enemy=0;
	ic->num_people = 0;
	ic->menu_cap=(char*)malloc(sizeof(char)*10);/*reservado para uso posterior que no pete*/

	fprintf(stdout, "%c[2J", 27);
	win_cls(ic->total, 1);
	_i_redraw(ic);

	return ic;

}

/*Sets the menu info and redraws the window*/
int setMenu_intrf(intrf *ic, char *menu_cap, int *stats, int stats_col, int cap_col, char **name_stats, int num_stats, int *limit_stats){
	if(!ic) return 0;
	strcpy(ic->menu_cap, menu_cap);
	ic->stats = stats; /*?*/
	ic->stats_col = stats_col;
	ic->name_stats = name_stats;
	ic->num_stats = num_stats;
	ic->limit_stats = limit_stats;
	ic->menucap_col = cap_col;

	_cap_redraw(ic);
	win_cls(ic->menu, 0);
  	fflush(stdout); /*obliga al buffer a vaciarse e imprimirlo todo*/
	return 1;
}

/*Sets the playfield data (player and objects) but doesn't draw anything*/
int setPlayData_intrf(intrf *ic, char player, char *obj, int num_obj, int player_row, int player_col, int *obj_col, int *obj_row, /*new stuff*/char *enemy,int num_enemy,int *enemy_col,int *enemy_row, int num_people, int *people_col, int *people_row, char *people){
	int i = 0;
	if(!ic)	return 0;
	/*Player*/
	ic->player = player;
	ic->player_row = player_row;
	ic->player_col = player_col;

	/*Objects*/
	ic->num_obj = num_obj;
	ic->obj = (char *) malloc(sizeof(int)*num_obj);
	ic->obj_row = (int *) malloc(sizeof(int)*num_obj);
	ic->obj_col = (int *) malloc(sizeof(int)*num_obj);
	for( ; i < num_obj; i++){
		ic->obj[i] = obj[i];
		ic->obj_row[i] = obj_row[i];
		ic->obj_col[i] = obj_col[i];
	}
	/*if(num_obj == 3){
		sprintf(buf, "%d %d %d %d %d %d", ic->obj_row[0], ic->obj_col[0], ic->obj_row[1], ic->obj_col[1], ic->obj_row[2], ic->obj_col[2]);
		extra_write_message_object_intrf(ic, buf);
	}*/

	/*Enemies*/
	ic->num_enemy = num_enemy;

	ic->enemy = (char *) malloc(sizeof(int)*num_enemy);
	ic->enemy_row = (int *) malloc(sizeof(int)*num_enemy);
	ic->enemy_col = (int *) malloc(sizeof(int)*num_enemy);
	for( i=0; i < num_enemy; i++){
		ic->enemy[i] = enemy[i];
		ic->enemy_col[i] = enemy_col[i];
		ic->enemy_row[i] = enemy_row[i];
	}

	/*People*/
	ic->num_people = num_people;

	ic->people = (char *) malloc(sizeof(int)*num_people);
	ic->people_row = (int *)malloc(sizeof(int)*num_people);
	ic->people_col = (int *)malloc(sizeof(int)*num_people);
	for(i = 0; i < num_people; i++){
		ic->people[i] = people[i];
		ic->people_col[i] = people_col[i];
		ic->people_row[i] = people_row[i];
	}

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




/*new enemy Stuff*/

int addEnemies_intrf(intrf *ic){
	int i = 0;

	if(!ic) return 0;

	for( ; i < ic->num_enemy; i++)
		win_write_char_at(ic->field, ic->enemy_row[i], ic->enemy_col[i], ic->enemy[i]);
	
	return 1;

}

int addPeople_intrf(intrf *ic){
	int i = 0;

	if(!ic) return 0;

	for( ; i < ic->num_people; i++)
		win_write_char_at(ic->field, ic->people_row[i], ic->people_col[i], ic->people[i]);

	return 1;
}

int removeEnemy(intrf *ic, int row, int col){
	int i = 0;
	if(!ic) return 0;

	for( ; i < ic->num_enemy; i++)
		if(ic->enemy_row[i] == row && ic->enemy_col[i] == col){
			ic->enemy_col[i] *= -1;
			ic->enemy_row[i] *= -1;
			/*extra_write_message_object_intrf(ic, "Prepare to fight!");*/
		}

	return 1;
}

/*int isOnEnemy_intrf(intrf *ic,int *row,int *col){
	int i = 0;
	if(!ic) return 0;
	for( ; i < ic->num_enemy; i++)
		/*sprintf(buf, "%d %d %d %d ", ic->obj_row[i], ic->obj_col[i], ic->player_row, ic->player_col);
		extra_write_message_object_intrf(ic, buf);*/
		/*if(ic->enemy_row[i] == ic->player_row && ic->enemy_col[i] == ic->player_col){
				*row=ic->enemy_row[i];
				*col=ic->enemy_col[i];
				return 1;
		}
			
	
	return 0;
}*/

int isOnEnemy_intrf(intrf *ic, int row, int col){
	if(!ic) return 0;
	for(int i = 0; i < ic->num_enemy; i++)
		if(ic->enemy_col[i] == col && ic->enemy_row[i] == row)
			return 1;

	return 0;
}

int isNearEnemy_intrf(intrf *ic, int *row, int *col){
	int i = 0;
	if(!ic) return 0;
	for( ; i < ic->num_enemy; i++){
		if(ic->enemy_row[i] == ic->player_row+1 ){
			/*if(ic->people_col[i] == ic->player_col+1){
				*row=ic->player_row+1;
				*col=ic->player_col+1;
				return 1; 
			}
			if(ic->people_col[i] == ic->player_col-1){
				*row=ic->player_row+1;
				*col=ic->player_col-1;
				return 1; 
			}*/
			if(ic->enemy_col[i] == ic->player_col){
				*row = ic->player_row+1;
				*col = ic->player_col;
				return 1;
			}

		}
		if(ic->enemy_row[i] == ic->player_row-1 ){
			/*if(ic->people_col[i] == ic->player_col+1){
				*row=ic->player_row-1;
				*col=ic->player_col+1;
				return 1;
			} 
			if(ic->people_col[i] == ic->player_col-1){
				*row=ic->player_row-1;
				*col=ic->player_col-1;
				return 1;
			}*/
			if(ic->enemy_col[i] == ic->player_col){
				*row = ic->player_row-1;
				*col = ic->player_col;
				return 1;
			}
		}
		if(ic->enemy_row[i] == ic->player_row){
			if(ic->enemy_col[i] == ic->player_col-1){
				*row = ic->player_row;
				*col = ic->player_col-1;
				return 1;
			}
			if(ic->enemy_col[i] == ic->player_col+1){
				*row = ic->player_row;
				*col = ic->player_col+1;
				return 1;
			}
		}
	}
		
	return 0;

}



int addObjects_intrf(intrf *ic){
	int i = 0;

	if(!ic) return 0;

	for( ; i < ic->num_obj; i++)
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
			/*extra_write_message_object_intrf(ic, "You have found an object!");*/
		}

	return 1;
}



int drawField_intrf(intrf *ic, int clear){
	int i = 0;

	if(!ic) return 0;

	if(clear)
		win_cls(ic->field, 0);
	
	for( ; i < ic->map_rows; i++)
		win_write_line_at(ic->field, i+1, 1, ic->map[i]);
	addObjects_intrf(ic);
	addEnemies_intrf(ic);
	addPeople_intrf(ic);
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
		win_write_line_at(ic->menu, i+2, ic->stats_col+1, buf);
	}
	return 1;
}


/*Moves the player and redraws it*/
/*El -1 viene de la diferencia entre field_rows/cols y map_rows/cols*/
int movePlayer_intrf(intrf *ic, int dir){
	if(!ic || dir < 0 || dir > 4) return -1;
	
	if(dir == NORTH || dir == SOUTH){
		int new_row = ic->player_row;
		/*printf("%d", ic->player_row);*/
		if(dir == NORTH)
			new_row --;
		if(dir == SOUTH)
			new_row ++;
		
		if(new_row >= 0 && new_row <= (ic->rows - ic->extra_rows) && ic->map[new_row - 1][ic->player_col - 1] == ' ' && !isOnPeople(ic, new_row, ic->player_col) && !isOnEnemy_intrf(ic, new_row, ic->player_col)){
			win_write_char_at(ic->field, ic->player_row, ic->player_col, ' ');
			ic->player_row = new_row;
			win_write_char_at(ic->field, ic->player_row, ic->player_col, ic->player);
			/*printf("%d", ic->player_row);*/
			return dir;
		}
	}
	else if(dir == EAST || dir == WEST){
		int new_col = ic->player_col;
		if(dir == EAST)
			new_col ++;
		if(dir == WEST)
			new_col --;

		if(new_col >= 0 && new_col <= (ic->cols - ic->menu_cols) && ic->map[ic->player_row - 1][new_col - 1] == ' ' && !isOnPeople(ic, ic->player_row, new_col) && !isOnEnemy_intrf(ic, ic->player_row, new_col)){
			win_write_char_at(ic->field, ic->player_row, ic->player_col, ' ');
			ic->player_col = new_col;
			win_write_char_at(ic->field, ic->player_row, ic->player_col, ic->player);
			return dir;
		}
	}
	else if(dir == HERE){
		win_write_char_at(ic->field, ic->player_row, ic->player_col, ' ');
		win_write_char_at(ic->field, ic->player_row, ic->player_col, ic->player);
		return dir;
	}
	return -1;
}

int isOnObject_intrf(intrf *ic){
	int i = 0;
	if(!ic) return 0;
	for( ; i < ic->num_obj; i++)
		/*sprintf(buf, "%d %d %d %d ", ic->obj_row[i], ic->obj_col[i], ic->player_row, ic->player_col);
		extra_write_message_object_intrf(ic, buf);*/
		if(ic->obj_row[i] == ic->player_row && ic->obj_col[i] == ic->player_col)
			return 1;
	
	return 0;
}

int isOnDoor_intrf(intrf *ic){
	if(!ic) return 0;

	if(ic->player_col == 1 || ic->player_row == 1 || ic->player_row == ic->map_rows || ic->player_col == ic->map_cols) return 1;

	return 0;
}

void extra_write_message_object_intrf(intrf *ic, char * mg){
	if(!ic) return;
	win_cls(ic->extra, 1);
	win_write_line_at(ic->extra, 2, 2, mg);
	/*fprintf(stdout, "%c[%d;%dH", 27, ic->player_row, ic->player_col);*/
}

void extra_write_lngmess_intrf(intrf *ic, char *mg){
	if(!ic) return;
	win_cls(ic->extra, 1);
	win_write_line_at(ic->extra, 1, 2, mg);
}

void prepare_to_write_cmd_intrf(intrf *ic){
	if(!ic) return;
	fprintf(stdout, "%c[%d;%dH", 27, ic->rows-2, 3);
	printf("> ");
	fflush(stdout);
	
}

void clear_cmd_intrf(intrf *ic){
	char *buf;
	if(!ic) return;

	buf = (char *) malloc((ic->cols-ic->menu_cols-4)*sizeof(char));
	memset(buf, ' ', (ic->cols-ic->menu_cols-4));
	buf[ic->cols-ic->menu_cols-5] = 0;
	fprintf(stdout, "%c[%d;%dH", 27, ic->rows-2, 2);
	printf("%s", buf);
	fflush(stdout);
	free(buf);
	
}

int dark_spaces_intrf(intrf *ic){
	if(!ic) return -1;
	return win_fgcol(ic->field, BACKGROUND);
}

void display_inventory(intrf *ic, char *pict, char **names, int num){
	int i = 0, j = 0, h = 0;
	char buf[30];
	if(!ic || !pict || !names){
		win_write_line_at(ic->extra, 2, 2, "nop");
		return;
	}

	win_cls(ic->extra, 1);
	for( ; i < num; i++){
		sprintf(buf, "%c  --%s", pict[i], names[i]);
		if(i+1 < ic->extra_rows)
			win_write_line_at(ic->extra, i+1, 2, buf);
		else if(j+1 < ic->extra_rows){
			win_write_line_at(ic->extra, j+1, 40, buf);
			j++;
		}
		else{
			win_write_line_at(ic->extra, h+1, 78, buf);
			h++;
		}
	}

	for(i = 0; i < num; i ++)
		free(names[i]);
	free(names);
}

void smth_useful(intrf *ic, int col){
	if(!ic) return;
	win_write_char_at(ic->cmd, 0, col, ' ');
	fprintf(stdout, "%c[%d;%dH", 27, ic->rows-2, col+2);
}

int isNearPeople_intrf(intrf *ic,int *row,int *col){
	int i = 0;
	if(!ic) return 0;
	for( ; i < ic->num_people; i++){
		if(ic->people_row[i] == ic->player_row+1 ){
			/*if(ic->people_col[i] == ic->player_col+1){
				*row=ic->player_row+1;
				*col=ic->player_col+1;
				return 1; 
			}
			if(ic->people_col[i] == ic->player_col-1){
				*row=ic->player_row+1;
				*col=ic->player_col-1;
				return 1; 
			}*/
			if(ic->people_col[i] == ic->player_col){
				*row = ic->player_row+1;
				*col = ic->player_col;
				return 1;
			}

		}
		if(ic->people_row[i] == ic->player_row-1 ){
			/*if(ic->people_col[i] == ic->player_col+1){
				*row=ic->player_row-1;
				*col=ic->player_col+1;
				return 1;
			} 
			if(ic->people_col[i] == ic->player_col-1){
				*row=ic->player_row-1;
				*col=ic->player_col-1;
				return 1;
			}*/
			if(ic->people_col[i] == ic->player_col){
				*row = ic->player_row-1;
				*col = ic->player_col;
				return 1;
			}
		}
		if(ic->people_row[i] == ic->player_row){
			if(ic->people_col[i] == ic->player_col-1){
				*row = ic->player_row;
				*col = ic->player_col-1;
				return 1;
			}
			if(ic->people_col[i] == ic->player_col+1){
				*row = ic->player_row;
				*col = ic->player_col+1;
				return 1;
			}
		}
	}
		
	return 0;

}

int isOnPeople(intrf *ic, int row, int col){
	if(!ic) return 0;
	for(int i = 0; i < ic->num_people; i++)
		if(ic->people_col[i] == col && ic->people_row[i] == row)
			return 1;

	return 0;
}

void prepare_to_write_mgextra(intrf *ic){
	if(!ic) return;
	fprintf(stdout, "%c[%d;%dH", 27, 100, 2);
	fflush(stdout);
}


void delete_intrf(intrf *ic){
	if(!ic) return;
	free(ic->obj);
	free(ic->obj_row);
	free(ic->obj_col);
	free(ic->menu_cap);
	win_delete(ic->field);
	win_delete(ic->menu);
	win_delete(ic->extra);
	win_delete(ic->cmd);
	win_delete(ic->total);
	free(ic);
}


