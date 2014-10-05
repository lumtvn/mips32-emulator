struct montoto
{
	int n_arg;
	// char *entry;
	// char **arg;
};

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAXSIZE 512

int main(int argc, char *argv[])
{
	struct montoto hola;
	struct montoto *phola = &hola;
	phola->n_arg = 1;

	printf("puto: %d\n", phola->n_arg);
}