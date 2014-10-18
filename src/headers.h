#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
	int report; ///error handling
	
	//concerning a script
	char *full_script;     //the script without the commentaries
	char *incoming_line;   //an entire line of the script without commentary (parsed out)
	char *label; //the label of a line
	char *tag;	// the tag of a line
	char *operation; //the operation of a line
	char *argline[4]; /// line arguments. four is the maximum amount of arguments that a command can have


	//concerning the processors memory
	char *memorytag; /// block's tag (.text, .data, etc)
	mbyte *realpoint; ///real memory pointer (in host RAM)
	mbyte *realpointbase; ///real memory pointer with fixed direction to the start of the memory segment. This is for making the reading easier
	int blocksize;

	//general purpose registers
	reg regs[32];

	// reg $zero, $at, $v0, $v1, $a0, $a1, $a2, $a3, $t0
	// , $t1, $t2, $t3, $t4, $t5, $t6, $t7, $s0, $s1, $s2
	// , $s3, $s4, $s5, $s6, $s7, $t8, $t9, $k0, $k1, $gp
	// , $sp, $fp, $ra;

	//concerning an entry for the IDE of the simulator
	int n_argenv; //number of arguments of the entry
	char *entry; //the complete entry
	char *command; //the command of the entry
	char *filename; //the filename, if any
	char *argenv[]; //the arguments array. 10 is a temporal value, i will change it



};

