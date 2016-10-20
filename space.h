
#ifndef SPACE_H
#define SPACE_H

#include <stdio.h>
#include <types.h>

typedef struct _Space Space;
/*struct _Space{
	int id;
	char name[MAX_CHAR];
	char desc[MAX_CHAR];
	char long_desc[MAX_CHAR];
	int length;
	int width;
	
	int neigh[4];/*refers to all four neighbor spaces by their id
	Status locked[4];/*refers to the neighbor spaces
	if there is some type of of door blocking the path
	North=0
	East=1
	South=2
	West=3
	
	
	Object *o[Max-objects];
	
}*/
int getID(Space *s);/*we obtain space id which help us identify it*/
Status deleteID(Space *s);
Status change_ID(Space *s,int id);
/*these two functions modify the space id from an existant ID*/
char *get_name(Space *s);
Status modify_name(Space *s,char *c);/*used when the space has been modified, we may want to change its name too*/
char *desc(Space *s);
char *long_desc(Space *s);
/*obtain different and complementary descriptions of the space*/
Space * go_toSpace(int id);
Bool isSpace(Space *s);/*indicates if he can move to adjacent
places,maybe he cant there is a wall*/
Bool isLocked(Space *s, int direction);/*tell us if we need some special stuf(RELATE TO object.c) to be able to move there*/
Space *create_Space(FILE *f);
Status delete_space(Space *s);
Space *load_space(FILE *f);/*we obtain info from a text file where we has saved the space*/
Status save_space(Space *s,FILE *f);/*we write the space and all its info on a new
empty document so we can the load it*/



#endif
