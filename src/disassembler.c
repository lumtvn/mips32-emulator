/**
 * @file disassembler.c
 * @author Luciano Mantovani
 * @date November 2014
 * @brief file containing functions meant to disassemble the code from an elf script
 *
 * This file has functions called by the main program when it has to disassemble an elf script.
 * 
 * for now, it has two functions. One that loads all the code operations into a lookup table, and
 * another that recieves as a parameter a 32 bit word and returns the operation given by the word.
 *
 * @todo function to get the operation prequisites, such as number of arguments, etc.
 * 
 *
 **/
#include "headers.h"
#include "disassembler.h"
#include "errors.h"
#include "environment.h"
#include "lookup.h"


/**
*@brief this function obtains the operation code, coded in a 32 bit word
*
*@param word the word to be analized
*
*@return mips it returns the emulator structure with a new value for the field mips->operation
*
*@note for this function to work correctly, the function load_opcodes MUST be called before its execution
**/
struct ptype *getopcode(struct ptype *mips, mword word)
{

	mword sixmsb; //the first six more significant bits
	mword opcode;

	if(word == 0){mips->operation = "NOP"; return mips;}

	sixmsb = word & 0xFC000000;
	sixmsb = sixmsb >> 26; //we shift 26 places to the right, so we get the first bits in the least significant byte

	char *sopcode = malloc(20); //string operation code
	if(sopcode == NULL){/*error de memoria*/return mips;}
	char *psopcode = malloc(10); //string operation code with the prefix
	if(psopcode == NULL){/*error de memoria*/return mips;}

	struct nlist *np;

	if(sixmsb == SPECIAL)
	{
		strcpy(psopcode,"S_OPCODE_");
		opcode = word & 0x3F;
	}
	else if(sixmsb == SPECIAL3)
	{
		strcpy(psopcode,"S3_OPCODE_");
		opcode = word & 0x7C0;
		opcode = opcode >> 6;
	}
	else if(sixmsb == REGIMM)
	{
		strcpy(psopcode,"RG_OPCODE_");
		opcode = word & 0x1F0000;
		opcode = opcode >> 16;
	}
	else
	{
		strcpy(psopcode,"OPCODE_");
		opcode = sixmsb;
	}

	sprintf(sopcode,"%x",opcode); // we turn the number into word readable string for lookup
    strcat(psopcode,sopcode); // we add the prefix	

    np = lookup(psopcode);

	if(np == NULL){printf("installation or lookup error. this should never appear\n"); return mips;}

	mips->operation = np->defn;

	free(sopcode);
	free(psopcode);

	return mips;
	
}
/**
*@brief this function loads all the operation codes in a lookup table for future reference.
*
* the main program has to call this function in order to get getopcode function working correctly.
*
*@return int it returns 0 if no error, -1 if there was an error in install function.
**/
int load_opcodes()
{
    struct nlist *np;
    np = install("S_OPCODE_20", "ADD"); if(np == NULL){return -1;}
    np = install("OPCODE_8", "ADDI"); if(np == NULL){return -1;}
    np = install("OPCODE_9", "ADDIU"); if(np == NULL){return -1;}
    np = install("S_OPCODE_21", "ADDU"); if(np == NULL){return -1;}
    np = install("S_OPCODE_24", "AND"); if(np == NULL){return -1;}
    np = install("OPCODE_c", "ANDI"); if(np == NULL){return -1;}
    np = install("OPCODE_4", "BEQ"); if(np == NULL){return -1;}
    np = install("RG_OPCODE_1", "BGEZ"); if(np == NULL){return -1;}
    np = install("OPCODE_7", "BGTZ"); if(np == NULL){return -1;}
    np = install("OPCODE_6", "BLEZ"); if(np == NULL){return -1;}
    np = install("RG_OPCODE_0", "BLTZ"); if(np == NULL){return -1;}
    np = install("OPCODE_5", "BNE"); if(np == NULL){return -1;}
    np = install("S_OPCODE_d", "BREAK"); if(np == NULL){return -1;}
    np = install("S_OPCODE_1a", "DIV"); if(np == NULL){return -1;}
    np = install("OPCODE_2", "J"); if(np == NULL){return -1;}
    np = install("OPCODE_3", "JAL"); if(np == NULL){return -1;}
    np = install("S_OPCODE_9", "JALR"); if(np == NULL){return -1;}
    np = install("S_OPCODE_8", "JR"); if(np == NULL){return -1;}
    np = install("OPCODE_20", "LB"); if(np == NULL){return -1;}
    np = install("OPCODE_24", "LBU"); if(np == NULL){return -1;}
    np = install("OPCODE_f", "LUI"); if(np == NULL){return -1;}
    np = install("OPCODE_23", "LW"); if(np == NULL){return -1;}
    np = install("S_OPCODE_10", "MFHI"); if(np == NULL){return -1;}
    np = install("S_OPCODE_12", "MFLO"); if(np == NULL){return -1;}
    np = install("S_OPCODE_18", "MULT"); if(np == NULL){return -1;}
    np = install("S_OPCODE_NOP", "NOP"); if(np == NULL){return -1;}
    np = install("S_OPCODE_25", "OR"); if(np == NULL){return -1;}
    np = install("OPCODE_d", "ORI"); if(np == NULL){return -1;}
    np = install("OPCODE_28", "SB"); if(np == NULL){return -1;}
    np = install("S3_OPCODE_10", "SEB"); if(np == NULL){return -1;}
    np = install("S_OPCODE_0", "SLL"); if(np == NULL){return -1;}
    np = install("S_OPCODE_2a", "SLT"); if(np == NULL){return -1;}
    np = install("OPCODE_a", "SLTI"); if(np == NULL){return -1;}
    np = install("OPCODE_b", "SLTIU"); if(np == NULL){return -1;}
    np = install("S_OPCODE_2b", "SLTU"); if(np == NULL){return -1;}
    np = install("S_OPCODE_3", "SRA"); if(np == NULL){return -1;}
    np = install("S_OPCODE_2", "SRL"); if(np == NULL){return -1;}
    np = install("S_OPCODE_22", "SUB"); if(np == NULL){return -1;}
    np = install("S_OPCODE_23", "SUBU"); if(np == NULL){return -1;}
    np = install("OPCODE_2b", "SW"); if(np == NULL){return -1;}
    np = install("S_OPCODE_c", "SYSCALL"); if(np == NULL){return -1;}
    np = install("S_OPCODE_26", "XOR"); if(np == NULL){return -1;}

    return 0;
}
/*
int load_prequisites()
{
	struct nlist *np;
	np = install("PREQ_ADD","3,3"); if(np == NULL){return -1;}
}*/