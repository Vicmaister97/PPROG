#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "cop.h"

typedef struct {
	int n;
} world;


int cmd1(void *dummy, char *obj, char **str, int n) {
	world *q = (world *) dummy;
	printf("cmd1: %s\n", str[0]);
}


int cmd2(void *dummy, char *obj, char **str, int n) {
	printf("cmd2: %s\n", str[0]);
}


int cmd3(void *dummy, char *obj, char **str, int n) {
	printf("cmd3: %s\n", str[0]);
}


int cmd4(void *dummy, char *obj, char **str, int n) {
	printf("cmd4: %s\n", str[0]);
}


int err(void *dummy, char *obj, char **str, int n) {
	printf("error: %s\n", str[0]);
}


int main() {
	char buf[100];
	world *w;
	FILE *fp = fopen("cmdfile.txt", "r");
	CoP *c = CoP_create(fp);
	if (c == NULL) return -1;

	if (CoP_assoc(c, "cmd1_internal", cmd1) == -1){
		printf("Error in the first association");
		return -1;
	}
	if (CoP_assoc(c, "cmd2_internal", cmd2) == -1){
		printf("Error in the second association");
		return -1;
	}
	if (CoP_assoc(c, "cmd3_internal", cmd3) == -1){
		printf("Error in the third association");
		return -1;
	}
	if (CoP_assoc(c, "cmd4_internal", cmd4) == -1){
		printf("Error in the fourth association");
		return -1;
	}
	if (CoP_assoc(c, "error_internal", err) == -1){
		printf("Error with the error (curious)");
		return -1;
	}

	while (1) {
		printf("> ");
		fflush(stdout);
		fgets(buf, 100, stdin);
		CoP_execute(c, buf, (void *) w);
	}
}