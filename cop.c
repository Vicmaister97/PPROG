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
world *q = (world *) dummy;
}

int cmd2(void *dummy, char *obj, char **str, int n) {
world *q = (world *) dummy;
}

int cmd3(void *dummy, char *obj, char **str, int n) {
world *q = (world *) dummy;
}

int err(void *dummy, char *obj, char **str, int n) {
world *q = (world *) dummy;
}

CoP *CoP_create (FILE *fp){
	CoP *c = (CoP *) malloc (sizeof (CoP));
	if (c == NULL)
		return NULL;
	
	char buf[100];
	int i;
	int cmds = atoi(fgets(buf, 100, fp)); //This number from the file doesn't count the last command, the error one
	c->e_lst = (ext_cmd **) malloc (sizeof (ext_cmd *)*(cmds));
	//CDE
	for (i = 0; i < cmds; i++){
		ext_cmd *pe = (ext_cmd *) malloc (sizeof (ext_cmd));
		if (pe == NULL) exit(1);

		fgets(buf, 100, fp);
		pe->cmd = (char *) malloc (sizeof (char)*(strlen(buf)+1));
		if (pe->cmd == NULL) exit(1);
		strcpy (pe->cmd, buf);
		fgets(buf, 100, fp);
		pe->internal = (char *) malloc (sizeof (char)*(strlen(buf)+1));
		if (pe->internal == NULL) exit(1);
		strcpy (pe->internal, buf);
		pe->n_msg = atoi(fgets(buf, 100, fp));
		pe->msg = (char **) malloc (sizeof (char *)*(pe->n_msg));
		if (pe->msg == NULL) exit(1);
		int j;
		for (j = 0; j < pe->n_msg; j++){
			fgets(buf, 100, fp);
			pe->msg[j] = (char *) malloc (sizeof (char)*(strlen(buf)+1));
			if (pe->msg[j] == NULL) exit(1);
			strcpy(pe->msg[j], buf);
		}

		c->e_lst[i] = pe;
	}

	c->ext_no = cmds; //Although the file has cmds+1 commands, we do not consider
					  //the last command, the error one, as it's an special one
	ext_cmd *error = (ext_cmd *) malloc (sizeof (ext_cmd));
	if (error == NULL) exit(1);
	fgets(buf, 100, fp);
	error->cmd = (char *) malloc (sizeof (char)*(strlen(buf)+1));
	if (error->cmd == NULL) exit(1);
	strcpy (error->cmd, buf);
	fgets(buf, 100, fp);
	error->internal = (char *) malloc (sizeof (char)*(strlen(buf)+1));
	if (error->internal == NULL) exit(1);
	strcpy (error->internal, buf);
	pe->n_msg = atoi(fgets(buf, 100, fp));
	pe->msg = (char **) malloc (sizeof (char *)*(pe->n_msg));
	if (pe->msg == NULL) exit(1);
	int k;
	for (k = 0; k < pe->n_msg; k++){
		fgets(buf, 100, fp);
		pe->msg[k] = (char *) malloc (sizeof (char)*(strlen(buf)+1));
		if (pe->msg[k] == NULL) exit(1);
		strcpy(pe->msg[k], buf);
	}
	
	c->error = error;
	c->int_no = 0;
	c->int_max = 10; //We choose 10 as an example
	c->i_list = (int_cmd **) malloc (sizeof (int_cmd *)*(c->int_max));
	if (c->i_list == NULL) exit(1);
	return c;
}


void free_extcmd (ext_cmd *list){
	if (list == NULL)
		return;

	free (list->cmd);
	free (list->internal);
	free (*(list->msg));
	free (list->msg);
	free (list);
	return;
}

int CoP_execute(CoP *c, char *cmd, void *pt) {
	char *verb;
	char *obj;

	verb = strtok(buf," ");
	object = strtok(NULL, " ");
	/* First, search the list of external commands for the right one */
	ext_cmd *e = _ext_src(c, name);
	if (!e) {
		char **str = _unpack(c->error, verb);
		cmdfun_type f = _assoc_search(c, c->error->internal);
		if(!f) {
			abort("catastrophic error");
		}
	return (*f)(pt, verb, str, c->error->n_msg);
	for (i)
	}
	/* The command has been found */
	char **str = _unpack(e, obj);
	cmdfun_type f = _assoc_search(c, e->internal);
	if(!f) {
	abort("catastrophic error");
	}
	return (*f)(pt, obj, str, e->n_msg);
	/* There are some frees to do before returning... */
}

char *_unpack(char *str, char *repl) {
	char *ret, *pt;
	int n = 0;
	15/* count the number of stars in the first string */
	for (p=str; *p; p++) {
		if (*p == ’*’) n++
	}
	/* allocates the array with enough space for the final string (I add
	1 to store the final zero) */
	ret = (char *) malloc(str + n*repl);
	p = ret;
	while (*str) {
		if (*str!=’*’) {
		*p++ = *str++;
		}
		else {
		strcpy(p, repl);
		p += strlen(repl);
		str++;
		}
	}
	return ret;
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
	while(1) {
		printf("> ");
		fflush(stdout);
		fgets(buf, 100, stdin);
		CoP execute(c, buf, (void *) w);
	}
}