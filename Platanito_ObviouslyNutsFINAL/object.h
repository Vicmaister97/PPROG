#ifndef OBJECT_H
#define OBJECT_H

#include "types.h"
#include <stdio.h>

typedef struct _Object Object;
typedef struct _People People;

People* create_people (FILE *fp); /*Fuction that creates and allocs memory for a person, reading from a file*/
void delete_people (People *po); /*Fuction that receives a person and deletes it, freeing its memory*/
char* getText_people (People *po); /*Function that returns the text (conversation) of a given person*/
int getId_people (People *po); /*Function that returns the Id of a given person*/
int getLocation_people (People *po); /*Function that returns the location of a given person*/
int getRow_people (People *po);
int getCol_People (People *po);
char getPicture_people(People *po);


Object* create_object (FILE *fp); /* Function that creates an object reading from a file */
void delete_object (Object *po); /* Function that destroys an object */
Bool isInInventory (Object *po); /* Function that tells you if an object is in the player inventory or not */
Status move_object (Object *po, int location); /* Function that moves an object to a location (space) */
Object* pick_object (Object *po); /* Function that picks an object (so the player can use it) */
Bool isUsable_object (Object *po); /* Function that tells you if you are able to use an object or not */
int getId_object (Object *po); /* Function that returns the ID an object */
Status setName_object (Object *po, char *name); /* Function that changes the name of an object */
char* getName_object (Object *po); /* Function that returns the name of an object */
char* getDesc_object (Object *po); /* Function that returns the description of an object */
Status setProp_object (Object *po, int prop, int nv); /* Function that changes a certain property of an object to a given value */
int* getProp_object (Object *po); /* Function that returns the properties of an object */
int getLocation_object (Object *po); /* Function that returns the location of an object */
Status drop_object(Object *po);
char getPicture_object (Object *po);
int getRow_object (Object *po);
int getCol_object (Object *po);
Status use_object (Object *po);
int getType_object(Object *po);

#endif
