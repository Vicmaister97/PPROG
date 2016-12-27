#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "cop.h"

/*char *strdup(char *);*/

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
	ext_cmd **e_lst; /*list with all the external (normal) commands*/
	int ext_no; /*number of external commands*/
	ext_cmd *error; /*the special error command*/
	int_cmd **i_list; /*list with associations between internal commands and functions*/
	int int_no;  /*number of elements of the internal list (0 at the beginning)*/
	int int_max; /*the number of pointers i_lst that are actually allocated*/
};


CoP *CoP_create(FILE *fp){
	CoP *c = (CoP *)malloc(sizeof (CoP));
	if (c == NULL) return NULL;

	char buf[100];
	int i;
	int cmds = atoi(fgets(buf, 100, fp)); /*This number from the file doesn't count the last command, the error one*/
	
	c->e_lst = (ext_cmd **) malloc (sizeof (ext_cmd *)*(cmds));
	if (c->e_lst == NULL) exit(1);

	for (i = 0; i < cmds; i++){
		ext_cmd *pe = (ext_cmd *) malloc (sizeof (ext_cmd));
		if (pe == NULL) exit(1);

		fgets(buf, 100, fp);
		if (buf[strlen(buf)-1] == '\n') buf[strlen(buf)-1] = 0; 
		pe->cmd = (char *) malloc (sizeof (char)*(strlen(buf)+1));
		if (pe->cmd == NULL) exit(1);
		strcpy (pe->cmd, buf);
		fgets(buf, 100, fp);
		if (buf[strlen(buf)-1] == '\n') buf[strlen(buf)-1] = 0; 
		pe->internal = (char *) malloc (sizeof (char)*(strlen(buf)+1));
		if (pe->internal == NULL) exit(1);
		strcpy (pe->internal, buf);
		pe->n_msg = atoi(fgets(buf, 100, fp));
		pe->msg = (char **) malloc (sizeof (char *)*(pe->n_msg));
		if (pe->msg == NULL) exit(1);
		int j;
		for (j = 0; j < pe->n_msg; j++){
			fgets(buf, 100, fp);
			if (buf[strlen(buf)-1] == '\n') buf[strlen(buf)-1] = 0; 
			pe->msg[j] = (char *) malloc (sizeof (char)*(strlen(buf)+1));
			if (pe->msg[j] == NULL) exit(1);
			strcpy(pe->msg[j], buf);
		}

		c->e_lst[i] = pe;

	}

	c->ext_no = cmds; /*Although the file has cmds+1 commands written, we do not consider
					    the last command, the error one, as it's an special one*/
	ext_cmd *error = (ext_cmd *) malloc (sizeof (ext_cmd));
	if (error == NULL) exit(1);
	fgets(buf, 100, fp);
	if (buf[strlen(buf)-1] == '\n') buf[strlen(buf)-1] = 0; 
	error->cmd = (char *) malloc (sizeof (char)*(strlen(buf)+1));
	if (error->cmd == NULL) exit(1);
	strcpy (error->cmd, buf);
	fgets(buf, 100, fp);
	if (buf[strlen(buf)-1] == '\n') buf[strlen(buf)-1] = 0; 
	error->internal = (char *) malloc (sizeof (char)*(strlen(buf)+1));
	if (error->internal == NULL) exit(1);
	strcpy (error->internal, buf);
	error->n_msg = atoi(fgets(buf, 100, fp));
	error->msg = (char **) malloc (sizeof (char *)*(error->n_msg));
	if (error->msg == NULL) exit(1);
	int k;
	for (k = 0; k < error->n_msg; k++){
		fgets(buf, 100, fp);
		if (buf[strlen(buf)-1] == '\n') buf[strlen(buf)-1] = 0;
		error->msg[k] = (char *) malloc (sizeof (char)*(strlen(buf)+1));
		if (error->msg[k] == NULL) exit(1);
		strcpy(error->msg[k], buf);
	}
	
	c->error = error;
	c->int_no = 0;
	c->int_max = 10; /*We choose 10 as an example*/

	c->i_list = (int_cmd **) malloc (sizeof (int_cmd *)*(c->int_max));
	if (c->i_list == NULL) exit(1);
	return c;
}

static cmdfun_type _assoc_search(CoP *c, char *i_name) {
	int i;

	for (i = 0; i < c->int_no; i++) {
		if (!strcmp(i_name, c->i_list[i]->i_name))
			return c->i_list[i]->fct;	
	}

	return NULL;
}


int CoP_assoc(CoP *c, char *int_name, cmdfun_type cfun) {
	if (_assoc_search(c, int_name) != NULL) return -1;  /*the internal command already existed */

	/*if (c->int_no >= c->int_max - 1) {     list full: get more space
		c->int_max += 10;
		c->i_lst = (int_cmd **)realloc(c->i_lst, c->int_max);
	}*/

	if (c->int_no >= c->int_max) { /* list full: get more space */
		c->int_max += 10;
		c->i_list = (int_cmd **)realloc(c->i_list, c->int_max);
	}

	int_cmd *new_a = (int_cmd *)malloc(sizeof(int_cmd));
	/*new_a->i_name = strdup(int_name);*/
	new_a->i_name = (char *) malloc(sizeof(char)*strlen(int_name)+1);
	strcpy(new_a->i_name, int_name);
	new_a->fct = cfun;

	/*c->i_lst[c->int_no++] = new_a;
	  return c->int_no;*/
	c->i_list[c->int_no] = new_a;
	c->int_no++;
	return c->int_no;
}


/*int _assoc_search(CoP *c, char* int_name){
	int i;
	for (i = 0; i<c->int_no; i++){
		if (strcmp(int_name, c->i_lst[i]->i_name) == 0) return 1;
	}
	return NULL;
}*/


static ext_cmd *_ext_src(CoP *c, char *name) {
	int i;
		for (i = 0; i < c->ext_no; i++){
		if (strcmp(name, c->e_lst[i]->cmd) == 0){
			return c->e_lst[i];
		}
	}

	/*If the function reaches this point, that means there's no coincidence*/
	return NULL;
}


char *_unpack(char *str, char *repl) {
	char *ret, *p;
	int n = 0;
	/* count the number of stars in the first string */
	for (p=str; *p; p++) {
		if (*p == '*') n++;
	}
	/* allocates the array with enough space for the final string (I add
	1 to store the final zero) */
	ret = (char *) malloc(strlen(str) + n*strlen(repl));
	p = ret;
	while (*str) {
		if (*str != '*') {
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


static char **_unpack_all(ext_cmd *e, char *obj) {
	char **str = (char **) malloc(e->n_msg*sizeof(char *));
	int i;
	for (i = 0; i < e->n_msg; i++)
		str[i] = _unpack(e->msg[i], obj);
	return str;
}


int CoP_execute(CoP *c, char *cmd, void *pt) {
	char *verb;
	char *obj;

	verb = strtok(cmd," ");
	obj = strtok(NULL, " ");

	/* First, search the list of external commands for the right one */
	ext_cmd *e = _ext_src(c, verb);

	if (e == NULL) {
		char **str1 = _unpack_all(c->error, verb);
		cmdfun_type f = _assoc_search(c, c->error->internal);

		if(!f) abort();
		
		int r = (*f)(pt, verb, str1, c->error->n_msg);
		int i;
		for (i = 0; i < c->error->n_msg; i++)
			free (str1[i]);
	
		free (str1);
		return r;
	}

	/* The command has been found */
	char **str2 = _unpack_all(e, obj);
	cmdfun_type f = _assoc_search(c, e->internal);

	if(!f) abort();

	int s = (*f)(pt, obj, str2, e->n_msg);
	int j;

	for (j = 0; j < e->n_msg; j++)
		free (str2[j]);

	free (str2);
	return s;
}


void CoP_delete(CoP *c){
	if (c == NULL) return;

	for (int i = 0; i < c->ext_no; i++){
		free(c->e_lst[i]->cmd);
		free(c->e_lst[i]->internal);
		for (int j = 0; j < c->e_lst[i]->n_msg; j++)
			free(c->e_lst[i]->msg[j]);
		free(c->e_lst[i]->msg);
		free(c->e_lst[i]);
	}
	free(c->e_lst);

	free(c->error->cmd);
	free(c->error->internal);
	for (int j = 0; j < c->error->n_msg; j++)
			free(c->error->msg[j]);
	free(c->error->msg);
	free(c->error);

	for (int i = 0; i < c->int_no; i++){
		free(c->i_list[i]->i_name);
		free(c->i_list[i]);
	}
	
	free(c->i_list);

	free(c);
}

