#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct ptype /// it's a structure that has all elements that are involved in the emulation
{            
	char *incoming_line;
	char *tag;
	char *operation;
	char *argument1;
	char *argument2;
	char *argument3;
	char *argument4;
	char *comment;
};