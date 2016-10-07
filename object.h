
#ifndef OBJECT_H
#define OBJECT_H
#include "types.h"

typedef struct _Object Object;

Bool isInInventory (Object *o);
Object * create_objet ();
void delete_object (Object *o);
Status pick_object (Object *o);
Status drop_object (Object *o);
Status isUsable_object (Object *o);
char* getName_object (Object *o);
Status setName_object (Object *o, char *name);
char* desc_object (Object *o);
Status setdesc_object (Object *o, char *desc);
Status use_Object (Object *o);

#endif