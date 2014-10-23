#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

#define MAXSIZE 256

typedef int bool;
#define true 1
#define false 0

typedef unsigned int mword;
typedef unsigned int *reg;
typedef unsigned short int mhalfword;
typedef unsigned char mbyte;

static char *regnames[32] = {"$zero", "$at", "$v0", "$v1", "$a0", "$a1", "$a2", "$a3", "$t0"
		, "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7", "$s0", "$s1", "$s2"
		, "$s3", "$s4", "$s5", "$s6", "$s7", "$t8", "$t9", "$k0", "$k1", "$gp"
		, "$sp", "$fp", "$ra"};

struct ptype /// it's a structure that has all elements that are involved in the simulator
{   
	///integer for error handling
	int report; 
	
	//concerning a script
	///the script without the commentaries
	char *full_script;     
	///an entire line of the script without commentary (parsed out)
	char *incoming_line;   
	///the label of a line
	char *label; 
	/// the tag of a line
	char *tag;	
	///the operation of a line
	char *operation; 
	/// line arguments. four is the maximum amount of arguments that a command can have
	char *argline[4]; 


	//concerning the processors memory
	/// block's tag (.text, .data, etc)
	char *memorytag; 
	///real memory pointer (in host RAM)
	mbyte *realpoint; 
	///real memory pointer with fixed direction to the start of the memory segment. This is for making the reading easier
	mbyte *realpointbase; 
	/// memory block size
	int blocksize;

	///general purpose registers
	reg regs[32];

	//concerning an entry for the IDE of the simulator
	///number of arguments of the entry
	int n_argenv; 
	///the complete entry
	char *entry; 
	///the command of the entry
	char *command; 
	///the filename, if any
	char *filename; 
	///the arguments array. 32 is a temporal value, i will change it
	char *argenv[32]; 


	//the script in a char * matrix, with nlines lines
	///number of elements of scriptlines array
	int nlines;
	///array containing each line in a script
	char *scriptlines[];


};

