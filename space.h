#ifndef SPACE_H
#define SPACE_H

#include <stdio.h>
#include <stdlib.h>
#include "types.h"

typedef struct _Space Space;

int getID(Space *s);/*we obtain space id which help us identify it*/
char *desc(Space *s);
char *long_desc(Space *s);
/*obtain different and complementary descriptions of the space*/
Bool isLocked(Space *s, int direction);/*tell us if we need some special stuf(RELATE TO object.c) to be able to move there*/
Space *create_Space(FILE *f);
int pictRows_space(Space *s);
int getNeigh_space(Space *s, int dir);
char **getPict_space(Space *s);
void delete_space(Space *s);

#endif
