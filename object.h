#ifndef OBJECT_H
#define OBJECT_H

#include "types.h"
#include <stdio.h>

typedef struct _Object Object;

/*struct _Object{
	int id;
	Status isPicked;
	char *name;
	char *desc;
	int *properties; /*[0]: Strength; [1]: HP; [2]: Speed; [3]: Wisdom; [4]: Defense*/
/*	int location;
}
*/

Object* create_objet ();
void delete_object (Object *po);
Bool isInInventory (Object *po);
Status move_object (Object *po, int room);
Status isUsable_object (Object *po);
Status setName_object (Object *po, char *name);
char* getName_object (Object *po);
Status setdesc_object (Object *po, char *desc);
char* desc_object (Object *po);

#endif
