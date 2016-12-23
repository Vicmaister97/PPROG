#include <string.h>
#include "space.h"
#define MAX_CHAR 20

struct _Space{
	int id;
	char *name;
	char *desc;
	char *long_desc;
	int rows;
	int cols;
	
	int neigh[4];/*refers to all four neighbor spaces by their id*/
	Status locked[4];/*refers to the neighbor spaces
	if there is some type of of door blocking the path*/	
	/*North=0
	East=1
	South=2
	West=3
	*/
	int unlock[4];

	char **pict;
	/*Object *o;*/
	/*two different options in order to store objects from a space*/
};

int getID_Space(Space *s){
if (!s)return 0;
return s->id;
}/*we obtain space id which help us identify it*/




char *name_Space(Space *s){
	if(!s)return NULL;
	return s->name;
}

char *desc_Space(Space *s){

if (!s)return NULL;
return s->desc;
}
char *long_desc_Space(Space *s){
if (!s)return NULL;
return s->long_desc;
}
Bool isLocked_Space(Space *s, int direction){
	if(!s)return FALSE;
if(s->locked[direction])return TRUE;
return FALSE;
}/*tell us if we need some special stuf(RELATE TO object.c) to be able to move there*/

Space *create_Space(FILE *fp){
	Space*s=(Space*)malloc (sizeof(Space));
	int i;
	char buf[150];
	if(!s)return NULL;
	s->id = atoi(fgets(buf, 100, fp));

	fgets(buf, 100, fp);
	s->name = (char *)malloc(sizeof(char)*(strlen(buf)+1));
	strcpy(s->name, buf);

	fgets(buf, 100, fp);
	s->desc = (char *)malloc(sizeof(char)*(strlen(buf)+1));
	strcpy(s->desc, buf);

	fgets(buf, 100, fp);
	s->long_desc = (char *)malloc(sizeof(char)*(strlen(buf)+1));
	strcpy(s->long_desc, buf);

	s->rows=atoi(fgets(buf, 100, fp));

	s->cols=atoi(fgets(buf, 100, fp));

	fgets(buf,100,fp);
	for(i=0; i<4; i++)
		s->locked[i] = buf[i]-'0';

	fgets(buf,100,fp);
	for(i=0; i<4; i++)
		s->neigh[i] = buf[i]-'0';
	
	fgets(buf,100,fp);
	for(i=0; i<4; i++)
		s->unlock[i] = buf[i]-'0';
	
	s->pict = (char **)malloc(sizeof(char*)*s->rows);
	for(i=0;i<s->rows;i++){
		fgets(buf, 150, fp);
		s->pict[i] = (char *)malloc(sizeof(char)*strlen(buf) + 1);
		strcpy(s->pict[i], buf);
	}
	return s;

  }

  int pictRows_Space(Space *s){
  	if(!s) return 0;
  	return s->rows;
  }
   int pictCols_Space(Space *s){
  	if(!s) return 0;
  	return s->cols;
  }

  int getNeigh_Space(Space *s, int dir){
  	if(!s || dir < 0 || dir > 3) return 0;
  	return s->neigh[dir];
  }

  char **getPict_Space(Space *s){
  	if(!s) return NULL;
  	return s->pict;
  }

  int getUnlock_Space(Space *s, int dir){
  	if(!s || dir < 0 || dir > 3) return 0;
  	return s->unlock[dir];
  }

  void delete_Space(Space *s){
  	int i = 0;
  	if(!s) return;
  	if(s->name) free(s->name);
  	if(s->desc) free(s->desc);
  	if(s->long_desc) free(s->long_desc);
  	for( ; i < s->rows; i++)
  		if(s->pict[i]) free(s->pict[i]);
  	if(s->pict) free(s->pict);
  	free(s);
  }
 