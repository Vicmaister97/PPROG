
#ifndef SPACE_H
#define SPACE_H

#include <stdio.h>
#include <types.h>

typedef struct _Space Space;

int getID(Space *s);
char *get_name(Space *s);
char *desc(Space *s);
char *long_desc(Space *s);
int go(Space *s, int status, int dir);
Bool isSpace(Space *s);
Bool isLocked(Space *s, int status, int dir);
Space *create_Space();/*lo vamos a crear de un fichero de txt??*/
Bool delete_space(Space *s);/* eliminamos el fichero??*/
Space *load_space(FILE *f);


#endif
