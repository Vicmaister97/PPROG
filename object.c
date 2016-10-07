
#include "object.h"

struct _Object{
	int id;
	char *name;
	char *desc;
	int opens;
	int *improves;
	int location;
}
