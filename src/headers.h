#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../elfapi/include/common/bits.h"
#include "../elfapi/include/common/notify.h"
#include "../elfapi/include/elf/elf.h"
#include "../elfapi/include/elf/syms.h"
#include "../elfapi/include/mem.h"

#define MAXSIZE 512
#define MAXFILESIZE 2048

typedef int bool;
#define true 1
#define false 0

typedef unsigned int mword;

typedef unsigned int *reg;
typedef unsigned short int mhalfword;
typedef unsigned char mbyte;

static mword const SPECIAL = 0X0;
static mword const SPECIAL3 = 0X1F;
static mword const REGIMM = 0X1;

static char *regnames[32] = {"$zero", "$at", "$v0", "$v1", "$a0", "$a1", "$a2", "$a3", "$t0"
		, "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7", "$s0", "$s1", "$s2"
		, "$s3", "$s4", "$s5", "$s6", "$s7", "$t8", "$t9", "$k0", "$k1", "$gp"
		, "$sp", "$fp", "$ra"};



struct ptype /// it's a structure that has all elements that are involved in the simulator
{   
	///integer for error handling
	int report; 
	

	//concerning an operation

	///size of the elf file
	size_t filesize;
	///the label of a line
	char *label; 
	/// the tag of a line
	char *tag;	
	///the operation of a line
	char *operation; 
	/// line arguments. four is the maximum amount of arguments that a command can have
	char *argline[4];


	//concerning the memory and its segments

	//a segment

	/// segment's name(.text, .data, etc)
	char *segname;
	///segment size
	int segsize;
	///real pointer to segment (used to run over the segment) (in host RAM)
	mbyte *segrealpoint;
	///real pointer to beggining of memory segment (remains unchanged once initialized)
	mbyte *segrealpointbase;
	///the segment's read and write permissions
	int segpermissions;


	//the entire memory

	///number of memory segments
	unsigned int nsegs;
	///real memory pointer (in host RAM)
	mbyte *memrealpoint; 
	///real memory pointer with fixed direction to the start of the memory segment. This is for making the reading easier
	mbyte *memrealpointbase; 
	/// memory block size
	int memsize;

	///memory
	struct elfstr *elfdata;
	///for reading files in elfmanager.c
	byte bdata;
	word wdata;


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

	///flag to know if there's a file loaded
	bool fl_file_loaded; 
	///exit flag
	bool fl_exit;

};

struct elfstr{
	mem memory;
	stab symtab;
	FILE *pf_elf;
	bool success;
};