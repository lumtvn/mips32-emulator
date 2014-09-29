#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAXSIZE 512

struct ptype /// it's a structure that has all elements that are involved in the emulation
{            
	char *incoming_line;
	char *tag;
	char *operation;
	char *arg[4]; /// four is the maximum amount of arguments that a command can have
};

