#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

extern int errno;
#define MAXSIZE 256

typedef int bool;
#define true 1
#define false 0

struct ptype /// it's a structure that has all elements that are involved in the simulator
{   
	//concerning a script
	char *full_script;     
	char *parsed_script;    
	char *incoming_line;
	char *label;
	char *tag;
	char *operation;
	char *argline[4]; /// four is the maximum amount of arguments that a command can have

	//concerning an entry for the IDE of the simulator
	int n_arg;
	char *entry;
	char *command;
	char *filename;
	char *arg[];
};

