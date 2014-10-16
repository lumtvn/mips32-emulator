#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct mword { char x[4]; } mword;
typedef char mbyte;


int main()
{	
	mword palabra;
	size_t wordsize;
	wordsize = sizeof(palabra);
	short int pepe;
	wordsize = sizeof(pepe);

	printf("palabra : %zu\n", wordsize);
}