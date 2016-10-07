
#ifndef OBJECT_H
#define OBJECT_H
	
typedef struct _Object Object;

int isInInventory(Object *ob);
int pick(Object *ob);
int drop(Object *ob);
int usable(Object *ob);
char *getName(Object *ob);
char *desc(Object *ob);

#endif
