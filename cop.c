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