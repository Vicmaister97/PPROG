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
	char name[MAX_CHAR];
	char desc[MAX_CHAR];
	char long_desc[MAX_CHAR];
	int length;
	int width;
	
	int neigh[4];/*refers to all four neighbor spaces by their id*/
	Status locked[4];/*refers to the neighbor spaces
	if there is some type of of door blocking the path*/	
	/*North=0
	East=1
	South=2
	West=3
	*/
	char **table;
	Object *o;
	/*two different options in order to store objects from a space*/
}
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


Bool isSpace(Space *s,int direction){/*indicates if he can move to adjacent
places,maybe he cant there is a wall*/

}
Bool isLocked(Space *s, int direction){
	if(!s)return FALSE;
if(s->locked[direction]==TRUE)return TRUE;
return FALSE;
}/*tell us if we need some special stuf(RELATE TO object.c) to be able to move there*/
Space *create_Space(FILE *fp){
	Space*s=(Space*)malloc (sizeof(Space));
	if(!s)return NULL;
	int i;
	char buf[100];
	s->id = atoi(fgets(buf, 100, fp));
	fgets(buf, 100, fp);
	/*buf[strlen(buf)-1] = 0;*/
	s->name = strdup(buf);
	fgets(buf, 100, fp);
	s->desc=strdup(buf);
	fgets(buf, 100, fp);
	s->long_desc=strdup(buf);
	s->length=atoi(fgets(buf, 100, fp));
	s->width=atoi(fgets(buf, 100, fp));
	for(i=0;i<4;i++){
		s->locked[i]=strdup(buf);
		s->neighbor[i]=atoi(fgets(buf,100,fp221));
	}

  }
   int go_toSpace(Space*s,int direction){
   	if(!s)return ERR;
   	if(isLocked(s,direction)==FALSE)return ERR;
   	return s->neighbor[direction];
   }

/*these functions below should be called from world.c*/
Status delete_space(Space *s);
Space *load_space(FILE *f);
Status save_space(Space *s,FILE *f);/*we write the space and all its info on a new
empty document so we can the load it*/
