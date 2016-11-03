#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "object.h"

struct _Object{
	int id; /* id >= 0 */
	char *name;
	char *desc;
	int *properties; /* [0]: Strength; [1]: HP; [2]: Speed; [3]: Wisdom; [4]: Defense;  [5]: Luck */
	int location; /* If location is -1, we say that the object is in the Inventory of the player, is picked */
}

Object* create_objet (FILE *fp){ /*Fuction that creates and allocs memory for an object, reading from a file*/
	Object *po = (Object *) malloc (sizeof (Object));
	if (po == NULL)
		return NULL;

	char buf[100];
	po->id = atoi(fgets(buf, 100, fp));
	fgets(buf, 100, fp);
	buf[strlen(buf)-1] = 0;
	po->name = strdup(buf);
	fgets(buf, 100, fp);
	buf[strlen(buf)-1] = 0;
	po->desc = strdup(buf);
	fgets(buf, 100, fp);
	int nsp;
	char *pt;
	for (pt = buf, nsp = 0; *pt; pt++){ /*Podría sustituirse por poner directamente nsp = 4 si al final hay sólo 4 propiedades */
		if (*pt == ' ')
			nsp++;	
	}

	po->properties = (int *) malloc((nsp+1)*sizeof(int));
	if (po->properties == NULL){
		free (po->name);
		free (po->desc);
		free (po);
		return NULL;
	}


	for (pt = buf, int i = 0; i < nsp; i++){
		char *c = strchr(pt,' ');
		if (!c) {
			po->properties[i] = atoi(pt);
			free (po->name);
			free (po->desc);
			free (po->properties);
			free (po);
			break;
		}
		*c = 0;
		po->properties[i] = atoi(pt);
		pt = c+1;
	}

	po->location = atoi(fgets(buf, 100, fp));

	return po;
}

void delete_object (Object *po){ /*Fuction that receives an object and deletes it, freeing its memory*/
	if (po == NULL)
		return;

	free (po->name);
	free (po->desc);
	free (po->properties);
	free (po);
	return
}

Bool isInInventory (Object *po){ /*Function that returns wether an object is in the Inventory of the player or not*/
	if (po == NULL)
		return FALSE;

	if (po->location == -1){
		return TRUE;
	}

	return FALSE;
}

Status move_object (Object *po, int location){ /*Function that moves an object to a given location(space)*/
	if (po == NULL || location < -1)
		return ERROR;

	po->location = location;

	return OK;
}

Object* pick_object (Object *po){ /*Function that moves a given object to the Inventory of the player*/
	if (po == NULL)
		return NULL;

	po->location == -1;

	return po;
}

/*Bool isUsable_object (Object *po){  Function that tells you if you are able to use a given object or not
	if (po == NULL)
		return FALSE;

	if (po->location != -1)
		return FALSE;


}*/

int getId_object (Object *po){ /*Function that returns the Id of a given object*/
	if (po == NULL)
		return -1;

	return po->id;
}

Status setName_object (Object *po, char *name){ /*Function that changes the name of a given object to a given name*/
	if (po == NULL || name == NULL)
		return ERROR;

	free (po->name);
	po->name = strdup(name);

	return OK;
}

char* getName_object (Object *po){ /*Function that returns the name of a given object*/
	if (po == NULL)
		return NULL;

	return po->name;
}

char* getDesc_object (Object *po){ /*Function that returns the description of a given object*/
	if (po == NULL)
		return NULL;

	return po->desc;
}

Status setProp_object (Object *po, int prop, int nv){ /*Function that changes a certain property of a given object to a given value*/
	if (po == NULL || -1 < prop < 5)
		return ERROR;

	po->properties[prop] = nv;
	return OK;
}

int* getProp_object (Object *po){ /*Function that returns the properties of a given object*/
	if (po == NULL)
		return NULL;

	return po->properties;
}

int getLocation_object (Object *po){ /*Function that returns the location of a given object*/
	if (po == NULL)
		return -2;

	return po->location;
}