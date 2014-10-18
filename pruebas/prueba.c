#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct mword { char x[4]; } mword;
typedef char mbyte;


int main()
{	
	char * s = "4";
	int pepe = atoi(s);


	printf("palabra : %d\n", pepe + 1);
}