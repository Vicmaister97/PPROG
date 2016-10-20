#ifndef OBJECT_H
#define OBJECT_H

#include "types.h"
#include <stdio.h>

typedef struct _Object Object;

/*struct _Object{
	int id;
	Bool isPicked;
	char *name;
	char *desc;
	int *properties; /*[0]: Strength; [1]: HP; [2]: Speed; [3]: Wisdom; [4]: Defense*/
/*	int location;
}
*/

Object* create_objet (FILE *fp); /* Function that creates an object reading from a file */
void delete_object (Object *po); /* Function that destroys an object */
Bool isInInventory (Object *po); /* Function that tells you if an object is in the player inventory or not */
Status move_object (Object *po, int location); /* Function that moves an object to a location (space) */
Bool isUsable_object (Object *po, );  /* Function that tells you if you are able to use an object or not */
int getId_object (Object *po);   /* Function that returns the ID an object */
Status setName_object (Object *po, char *name);  /* Function that changes the name of an object */
char* getName_object (Object *po);  /* Function that returns the name of an object */
char* desc_object (Object *po);   /* Function that returns the description of an object */
Status setProp_object (Object *po, int *pi);  /* Function that changes the properties of an object */
int* getProp_object (Object *po);  /* Function that returns the properties of an object */
int getLocation_object (Object *po);  /* Function that returns the location of an object */

#endif
