#include "object.h"

struct _Object{
	int id; /* id >= 0 */
	char *name;
	char *desc;
	int *properties; /*[0]: Strength; [1]: HP; [2]: Speed; [3]: Wisdom; [4]: Defense */
	int location; /*If location is -1, we say that the object is in the Inventory of the player, is picked */
}

Object* create_objet (FILE *fp){
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
	for (pt = buf, nsp = 0; *pt; pt++){ /*Podría sustituirse por poner directamente nsp = 3 si al final hay sólo 4 propiedades */
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

void delete_object (Object *po){
	if (po == NULL)
		return;

	free (po->name);
	free (po->desc);
	free (po->properties);
	free (po);
	return
}

Bool isInInventory (Object *po){
	if (po == NULL)
		return FALSE;

	if (po->location == -1){
		return TRUE;
	}

	return FALSE;
}

Status move_object (Object *po, int location){
	if (po == NULL || location < -1)
		return ERROR;

	po->location = location;

	return OK;
}

Object* pick_object (Object *po){
	if (po == NULL)
		return NULL;

	po->location == -1;

	return po;
}

/*Bool isUsable_object (Object *po){
	if (po == NULL)
		return FALSE;

	if (po->location != -1)
		return FALSE;


}*/

int getId_object (Object *po){
	if (po == NULL)
		return -1;

	return po->id;
}

Status setName_object (Object *po, char *name){
	if (po == NULL || name == NULL)
		return ERROR;

	free (po->name);
	po->name = strdup(name);

	return OK;
}