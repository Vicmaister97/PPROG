#ifndef SPACE_H
#define SPACE_H

#include <stdio.h>
#include <stdlib.h>
#include "types.h"

typedef struct _Space Space;

int getID_Space(Space *s);/*we obtain space id which help us identify it*/

int getID_Space(Space *s);/*we obtain space id which help us identify it*/

/*obtain different and complementary descriptions of the space*/
Bool isLocked_Space(Space *s, int direction);/*tell us if we need some special stuf(RELATE TO object.c) to be able to move there*/
Space *create_Space(FILE *f);
int pictRows_Space(Space *s);
int pictCols_Space(Space *s);
int getNeigh_Space(Space *s, int dir);
char **getPict_Space(Space *s);
void delete_Space(Space *s);
 int getUnlock_Space(Space *s, int dir);
Bool isDark_Space(Space *s, int dir);
char *getDesc_space(Space *s);

#endif
