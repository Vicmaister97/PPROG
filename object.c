#include "object.h"

struct _Object{
	int id;
	Status isPicked;
	char *name;
	char *desc;
	int *properties; /*[0]: Strength; [1]: HP; [2]: Speed; [3]: Wisdom; [4]: Defense*/
	int location;
}

Object* create_objet (FILE *fp){
	Object *po = (Object *) malloc (sizeof (Object));
	if (po == NULL){
		return;
	}
	char buf[100];
	po->id = atoi(fgets(buf, 100, fp));
	fgets(buf, 100, fp)
	buf[strlen(buf)-1] = 0;
	po->name = strdup(buf);
