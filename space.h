
#ifndef SPACE_H
#define SPACE_H

#include <stdio.h>
#include <types.h>

typedef struct _Space Space;

int getID(Space *s);
Status deleteID(Space *s);
Status change_ID(Space *s,int id){
char *get_name(Space *s);
Status modify_name(Space *s,char *c)
char *desc(Space *s);
char *long_desc(Space *s);
Space * go_toSpace(int id);
Bool isSpace(Space *s);
Bool isLocked(Space *s, int status, int dir);
Space *create_Space();/*lo vamos a crear de un fichero de txt??*/
Status delete_space(Space *s);/* eliminamos el fichero??*/
Space *load_space(FILE *f);
Status save_space(Space *s,FILE *f);


#endif
