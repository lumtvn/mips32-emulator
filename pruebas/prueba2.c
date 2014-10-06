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
	int i = system("diff prueba2.c prueba.c");
	printf("%d\n", i);
}