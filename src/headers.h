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
#define MAXBREAKPOINTS 20 //20 is more than enough to debug

typedef int bool;
#define true 1
#define false 0

typedef unsigned int mword;

typedef unsigned int *reg;
typedef unsigned short int halfword;
typedef unsigned char mbyte;

static char *regnames[32] = {"$zero", "$at", "$v0", "$v1", "$a0", "$a1", "$a2", "$a3", "$t0"
		, "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7", "$s0", "$s1", "$s2"
		, "$s3", "$s4", "$s5", "$s6", "$s7", "$t8", "$t9", "$k0", "$k1", "$gp"
		, "$sp", "$fp", "$ra"};

static char *opnames[42] = {"ADD", "ADDI", "ADDIU", "ADDU", "AND", "ANDI", "BEQ", "BGEZ", "BGTZ"
		, "BLEZ", "BLTZ", "BNE", "BREAK", "DIV", "J", "JAL", "JALR", "JR", "LB", "LBU", "LUI", "LW"
		, "MFHI", "MFLO", "MULT", "NOP", "OR", "ORI", "SB", "SEB", "SLL", "SLT", "SLTI", "SLTIU"
		, "SLTU", "SRA", "SRL", "SUB", "SUBU", "SW", "SYSCALL", "XOR"};



struct mipsstr /// it's a structure that has all elements that are involved in the simulator
{   

	///integer for error handling
	int report; 

	///program counter
	word PC;

	//debugging

	///breakpoint array
	uint breakpoints[MAXBREAKPOINTS];
	///step into flag
	bool fl_step_into;
	///stop flag
	bool fl_stop;

	/// the operation in a string
	char *operation; 


	///memory
	struct elfstr *elfdata;
	///for reading files in elfmanager.c
	byte bdata;
	///for reading files in elfmanager.c
	word wdata;
	///has the current reading address (similar to PC but with other purposes)
	word pc_temp;

	///for information read in words from segment text
	byte n_arg1;
	byte n_arg2;
	word inmediate;
	byte s_arg1;
	byte s_arg2;
	byte s_arg3;
	byte s_arg4;

	char *instr_output;
	char *disasm_output;
	///index for array opnames
	int opnum;


	///general purpose registers
	reg regs[32];

	reg hi;
	reg lo;

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
	int report;
};