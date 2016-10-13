/*Group:Obviously nut
	Arturo Turmo
	Blanca Martin
	Alfonso Villar
	Victor*/
#include <string.h>
#include "space.h"
#include "space.h"

struct _Space{
	int id;
	char *name;
	char *desc;
	char *long_desc;
	int lenght;
	int width;
	int neigh[4];/*refers to all four neighbor points*/
	int locked[4];/*refers to the neighbor spaces
	if there is some type of of door blocking the path*/	
} 
/*typedef enum {
    RIGHT = 0,
    UP = 1,
    LEFT = 2,
    DOWN = 3,
    STAY = 4
} Move;maybe this goes on a file who regulates actions from character*/

int createID(FILE *f);

char *create_name(Space *s);
char * create_desc();
/*these functions obtain the info from a created text file*/
int getID(Space *s){
if (!s)return NULL;
return s->id;
}/*we obtain space id which help us identify it*/

Status deleteID(Space *s){
if(s->id)
s->id=-1;
return OK;
}

Status change_ID(Space *s,int id){
if(!s)return ERR;
s->id=id;
return OK; 
}
/*these two functions modify the space id from an existant ID*/

char *get_name(Space *s){
if (!s)return NULL;
return s->name;
}

Status modify_name(Space *s,char *c){
if(!s)return ERR;
strcpy(s->name,c);
assert(s->name);
return OK;
}/*used when the space has been modified, we may want to change its name too*/


char *desc(Space *s){
if (!s)return NULL;
return s->desc;
}
char *long_desc(Space *s){
if (!s)return NULL;
return s->long_desc;
}
/*obtain different and complementary descriptions of the space*/
Space* go_toSpace(int id);
/*we move to another space using the id to select it*/


Bool isSpace(Space *s){/*indicates if he can move to adjacent
places,maybe he cant there is a wall*/
}
Bool isLocked(Space *s, int status, int dir){
}/*tell us if we need some special stuf(RELATE TO object.c) to be able to move there*/
Space *create_Space(FILE *fp);/*do we need it? or it just creates the space
at world.c while reading the text*/
{  }

/*these functions below should be called from world.c*/
Status delete_space(Space *s);
Space *load_space(FILE *f);
Status save_space(Space *s,FILE *f);/*we write the space and all its info on a new
empty document so we can the load it*/
