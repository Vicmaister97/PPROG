#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "cop.h"

typedef struct {
	int n;
} world;

typedef struct {
	char *cmd;
	char *internal;
	int n_msg;
	char **msg;
} ext_cmd;

typedef struct {
	char *i_name;
	cmdfun_type fct;
} int_cmd;

struct _CoP{
	ext_cmd **e_lst; //list with all the external (normal) commands
	int ext_no; //Number of external commands
	ext_cmd *error; //the special error command
	int_cmd **i_list; //List with associations between internal commands and functions
	int int_no;  //number of elements of the internal list (0 at the beginning)
	int int_max; //the number of pointers i_lst that are actually allocated
};
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "cop.h"

typedef struct {
	int n;
} world;

typedef struct {
	char *cmd;
	char *internal;
	int n_msg;
	char **msg;
} ext_cmd;

typedef struct {
	char *i_name;
	cmdfun_type fct;
} int_cmd;

struct _CoP{
	ext_cmd **e_lst; //list with all the external (normal) commands
	int ext_no; //Number of external commands
	ext_cmd *error; //the special error command
	int_cmd **i_list; //List with associations between internal commands and functions
	int int_no;  //number of elements of the internal list (0 at the beginning)
	int int_max; //the number of pointers i_lst that are actually allocated
};

int cmd1(void *dummy, char *obj, char **str, int n) {
	world *q = (world *)dummy;
}

int cmd2(void *dummy, char *obj, char **str, int n) {
	world *q = (world *)dummy;
}

int cmd3(void *dummy, char *obj, char **str, int n) {
	world *q = (world *)dummy;
}

int err(void *dummy, char *obj, char **str, int n) {
	world *q = (world *)dummy;
}

CoP *CoP_create(FILE *fp){
	CoP *c = (CoP *)malloc(sizeof (CoP));
	if (c == NULL)
		return NULL;

	char buf[100];
	int i;
	int cmds = atoi(fgets(buf, 100, fp)); //This number from the file doesn't count the last command, the error one
	c->e_lst = (ext_cmd **)malloc(sizeof (ext_cmd *)*(cmds);
	//CDE
	for (i = 0; i < cmds; i++){
		ext_cmd *pe = (ext_cmd *)malloc(sizeof (ext_cmd));
		if (pe == NULL){
			while (i != 0){
				free_extcmd(c->e_lst[i]);
				i--;
			}
			free(c->e_lst);
		}

		fgets(buf, 100, fp);
		pe->cmd = (char *)malloc(sizeof (char)*(strlen(buf) + 1));
		//CDE
		strcpy(pe->cmd, buf);
		fgets(buf, 100, fp);
		pe->internal = (char *)malloc(sizeof (char)*(strlen(buf) + 1));
		//CDE
		strcpy(pe->internal, buf);
		pe->n_msg = atoi(fgets(buf, 100, fp));
		pe->msg = (char **)malloc(sizeof (char *)*(pe->n_msg));
		//CDE
		int j;
		for (j = 0; j < pe->n_msg; j++){
			fgets(buf, 100, fp);
			pe->msg[j] = (char *)malloc(sizeof (char)*(strlen(buf) + 1));
			//CDE
			strcpy(pe->msg[j], buf);
		}

		c->e_lst[i] = pe;
	}

	c->ext_no = cmds; //Although the file has cmds+1 commands, we do not consider
	//the last command, the error one, as it's an special one
	ext_cmd *error = (ext_cmd *)malloc(sizeof (ext_cmd));
	//CDE
	fgets(buf, 100, fp);
	error->cmd = (char *)malloc(sizeof (char)*(strlen(buf) + 1));
	//CDE
	strcpy(error->cmd, buf);
	fgets(buf, 100, fp);
	error->internal = (char *)malloc(sizeof (char)*(strlen(buf) + 1));
	//CDE
	strcpy(error->internal, buf);
	pe->n_msg = atoi(fgets(buf, 100, fp));
	pe->msg = (char **)malloc(sizeof (char *)*(pe->n_msg));
	//CDE
	int k;
	for (k = 0; k < pe->n_msg; k++){
		fgets(buf, 100, fp);
		pe->msg[k] = (char *)malloc(sizeof (char)*(strlen(buf) + 1));
		//CDE
		strcpy(pe->msg[k], buf);
	}

	c->error = error;
	c->int_no = 0;
	c->int_max = 10; //We choose 10 as an example
	c->i_list = (int_cmd **)malloc(sizeof (int_cmd *)*(c->int_max));
	//CDE
	return c;
}

void free_extcmd(ext_cmd *list){
	if (list == NULL)
		return;

	free(list->cmd);
	free(list->internal);
	free(*(list->msg));
	free(list->msg);
	free(list);
	return;
}
int CoP_assoc(CoP *c, char *int_name, cmdfun_type cfun) {
	if (_assoc_search(c, int_name) != NULL) {
		return -1; /* the internal command already existed */
	}
	if (c->int_no >= c->int_max - 1) { /* list full: get more space */
		c->int_max += 10;
		c->i_lst = (int_cmd **)realloc(c->i_lst, c->int_max);
	}
	int_cmd *new_a = (int_cmd *)malloc(sizeof(int_cmd));
	new_a->i_name = strdup(int_name);
	new_a->fct = cfun;
	c->i_lst[c->int_no++] = new_a;
	return c->int_no;
}

int _assoc_search(CoP *c, char* int_name){
	int i;
	for (i = 0; i<c->int_no; i++){
		if (strcmp(int_name, c->i_lst[i]->i_name) == 0) return 1;
	}
	return NULL;
}


int main() {
	char buf[100];
	world *w;
	FILE *fp = fopen("cmdfile.txt", "r");
	CoP *c = CoP create(fp);
	CoP assoc(c, "cmd1 internal", cmd1);
	CoP assoc(c, "cmd2 internal", cmd2);
	CoP assoc(c, "cmd3 internal", cmd3);
	CoP assoc(c, "error internal", err);
	while (1) {
		printf("> ");
		fflush(stdout);
		fgets(buf, 100, stdin);
		CoP execute(c, buf, (void *)w);
	}
}