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

	mword sixmsb; //the first six more significant bits
	mword opcode;

	if(a == 0){mips->operation = "NOP"; return mips;}

	sixmsb = a & 0xFC000000;
	sixmsb = sixmsb >> 26; //we shift 26 places to the right, so we get the first bits in the least significant byte

	char *sopcode = malloc(20); //string operation code
	if(sopcode == NULL){/*error de memoria*/return mips;}
	char *psopcode = malloc(10); //string operation code with the prefix
	if(psopcode == NULL){/*error de memoria*/return mips;}

	struct nlist *np;

	if(sixmsb == SPECIAL)
	{
		strcpy(psopcode,"S_OPCODE_");
		opcode = a & 0x3F;
	}
	else if(sixmsb == SPECIAL3)
	{
		strcpy(psopcode,"S3_OPCODE_");
		opcode = a & 0x7C0;
		opcode = opcode >> 6;
	}
	else if(sixmsb == REGIMM)
	{
		strcpy(psopcode,"RG_OPCODE_");
		opcode = a & 0x1F0000;
		opcode = opcode >> 16;
	}
	else
	{
		strcpy(psopcode,"OPCODE_");
		opcode = sixmsb;
	}

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