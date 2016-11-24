/*Main de prueba de objecto*/

#include <stdio.h>
#include <stdlib.h>
#include "object.h"

int main (){
	FILE* fo = fopen("test1ob.txt", "r");
	int n;
	char buf[100];
	int i = 0;

	n = atoi(fgets(buf, 100, fo));
	for ( ; i < n; i++){
		Object *po = create_object(fo);
		int *props = NULL;
		if (po == NULL) return -1; 
		props = getProp_object(po);
		printf (" Id: %d\n Name: %s\n Description: %s\n Properties:\n Strength: %d\n HP: %d\n Speed: %d\n Wisdom: %d\n Defense: %d\n Luck: %d\n Location: %d\n", 
			getId_object(po), getName_object(po), getDesc_object(po), props[0], props[1], 
			props[2], props[3], props[4], props[5], getLocation_object(po));
		delete_object(po);
	}
	fclose (fo);
	return 0;
}