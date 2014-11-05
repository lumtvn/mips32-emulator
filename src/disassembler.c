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

int load_opcodes()
{
    struct nlist *np;
    np = install("100000", "ADD"); if(np == NULL){return -1;}
    return 0;
}

struct ptype *getopcode(struct ptype *mips, mword a)
{
	char opcode;
	char *sopcode = malloc(sizeof(int));
	struct nlist *np;

	printf("%x\n", a);
	opcode = a & 0xFC000000;
	printf("%x\n", opcode);

	if(sopcode == NULL){/*error de memoria*/return mips;}
	
	sprintf(sopcode,"%x",opcode);

	printf("sopcode: %s\n", sopcode);
	np = lookup(sopcode);

	if(np == NULL){printf("lookup no encontro nadaaaa\n"); return mips;}

	mips->operation = np->defn;

	free(sopcode);

	return mips;
	
}