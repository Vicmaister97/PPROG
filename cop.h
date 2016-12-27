/*  
	Group: Obviously nut
		Alfonso Villar
		Arturo Turmo
		Blanca Martín
		Víctor Gracía
*/

#ifndef COP_H
#define COP_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "types.h"

typedef struct _CoP CoP;
typedef int (*cmdfun_type)(void *, char *, char **, int n);

CoP *CoP_create(FILE *cmdfile);
int CoP_assoc(CoP *c, char *int_name, cmdfun_type cfun);
int CoP_execute(CoP *c, char *cmd, void *pt);
void CoP_delete(CoP *c);


#endif
