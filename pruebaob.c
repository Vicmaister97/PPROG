/*Main de prueba de objecto*/

#include <stdio.h>
#include <stdlib.h>
#include "object.h"

int main (){
	FILE* fo = fopen("ficheroob.txt", "r");
	int n;
	fscanf (fo, "%d", &n);
	int i = 0;
	for ( ; i < n; i++){
		Object *po = create_object (fo);
		if (po == NULL)
		fprintf (fo, " Id: %d\n Name: %s\n Description: %s\n Properties:\n Strength: %d\n HP: %d\n Speed: %d\n Wisdom: %d\n
			           Defense: %d\n Luck: %d\n Location: %d\n", po->id, po->name, po->desc, po->properties[0], po->properties[1], 
			           po->properties[2], po->properties[3], po->properties[4], po->properties[5], po->location);
		delete_object(po);
	}
	fclose (fo);
	return -1;
}