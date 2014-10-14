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
	char *full_script;     //the script without the commentaries
	char *incoming_line;   //an entire line of the script without commentary (parsed out)
	char *label; //the label of a line
	char *tag;	// the tag of a line
	char *operation; //the operation of a line
	char *argline[4]; /// line arguments. four is the maximum amount of arguments that a command can have

	//concerning an entry for the IDE of the simulator
	int n_arg; //number of arguments of the entry
	char *entry; //the complete entry
	char *command; //the command of the entry
	char *filename; //the filename, if any
	char *arg[]; //the arguments array
};

