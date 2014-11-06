/**
 * @file disassembler.c
 * @author Luciano Mantovani
 * @date October 2014
 * @brief file containing functions meant to assemble the code from an elf script
 *
 * This file has functions called by the main program when it has to assemble an elf script.
 * 
 * for now, it only has two main functions: compile and parseline. The idea is to parse line per line
 * and store the disassembler code in memory, but this is not yet implemented. For now, the only thing
 * this disassembler does is read a text from an .elf file, remove the commentary and store it in a 
 * string, which is a field of the general structure ptype.
 *
 * there's an extra function called splitscript that is used by compile
 **/
#include "headers.h"
#include "disassembler.h"
#include "errors.h"
#include "environment.h"
#include "lookup.h"




struct ptype *getopcode(struct ptype *mips, mword a)
{
	mword opcode;
	char *sopcode = malloc(10); //string operation code
	char *psopcode = malloc(10); //string operation code with the prefix
	strcpy(psopcode,"OPCODE_");
	struct nlist *np;

	opcode = a & 0xFC000000;
	opcode = opcode >> 26; //we shift 26 places to the right, so we get the code in the least significant byte

	if(sopcode == NULL){/*error de memoria*/return mips;}
	
	sprintf(sopcode,"%x",opcode); // we turn the number into a readable string for lookup
    strcat(psopcode,sopcode); // we add the prefix

	np = lookup(psopcode);

	if(np == NULL){printf("lookup no encontro nadaaaa\n"); return mips;}

	mips->operation = np->defn;

	free(sopcode);
	free(psopcode);

	return mips;
	
}


int load_opcodes()
{
    struct nlist *np;
    np = install("OPCODE_8", "ADDI"); if(np == NULL){return -1;}
    np = install("OPCODE_9", "ADDIU"); if(np == NULL){return -1;}
    np = install("OPCODE_c", "ANDI"); if(np == NULL){return -1;}
    np = install("OPCODE_4", "BEQ"); if(np == NULL){return -1;}
    np = install("OPCODE_7", "BGTZ"); if(np == NULL){return -1;}
    np = install("OPCODE_6", "BLEZ"); if(np == NULL){return -1;}
    np = install("OPCODE_5", "BNE"); if(np == NULL){return -1;}
    np = install("OPCODE_2", "J"); if(np == NULL){return -1;}
    np = install("OPCODE_3", "JAL"); if(np == NULL){return -1;}
    np = install("OPCODE_20", "LB"); if(np == NULL){return -1;}
    np = install("OPCODE_24", "LBU"); if(np == NULL){return -1;}
    np = install("OPCODE_f", "LUI"); if(np == NULL){return -1;}
    np = install("OPCODE_23", "LW"); if(np == NULL){return -1;}
    np = install("OPCODE_d", "ORI"); if(np == NULL){return -1;}
    np = install("OPCODE_28", "SB"); if(np == NULL){return -1;}
    np = install("OPCODE_a", "SLTI"); if(np == NULL){return -1;}
    np = install("OPCODE_b", "SLTIU"); if(np == NULL){return -1;}
    np = install("OPCODE_2b", "SW"); if(np == NULL){return -1;}
    return 0;
}