#include "object.h"

struct _Object{
	int id;
	Status isPicked;
	char *name;
	char *desc;
	int *properties; /*[0]: Strength; [1]: HP; [2]: Speed; [3]: Wisdom; [4]: Defense*/
	int location;
}