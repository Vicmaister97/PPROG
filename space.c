
#include "space.h"
#include "space.h"

struct _Space{
	int id;
	char *name;
	char *desc;
	char *long_desc;
	int lenght;
	int width;
	int neigh[4];
	int locked[4];/*0 no 1 si se pasa*/	
} 
int createID(Space *s);
Status deleteID(int id);
char *create_name(Space *s);
Status delete_name(char *c);
char * create_desc();


int getID(Space *s){
assert(s!=NULL);
return s->id;
}
char *get_name(Space *s){
assert(s!=NULL);
return s->name;
}
char *desc(Space *s){
assert(s!=NULL);
return s->desc;
}
char *long_desc(Space *s){
assert(s!=NULL);
return s->desc;
}
int go(Space *s, int status, int dir){
{


}

Bool isSpace(Space *s);
Bool isLocked(Space *s, int status, int dir);
Space *create_Space();/*lo vamos a crear de un fichero de txt??*/
{  



}
Bool delete_space(Space *s);/* eliminamos el fichero??*/
Space *load_space(FILE *f);
