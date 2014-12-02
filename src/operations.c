#include "headers.h"


int op_add(struct ptype *mips, byte rs, byte rt, byte rd)
{
	word temp;
	int i = 0;

	temp = *(mips->regs[rs]) + *(mips->regs[rt]);
	if(temp < *(mips->regs[rs]))  
		return 1; //overflow

	*(mips->regs[rd]) = temp;

	return 0;
}

struct ptype *print_add(struct ptype *mips, byte rs, byte rt, byte rd)
{
	sprintf(mips->disasm_output, "ADD %s, %s, %s", regnames[rd], regnames[rs], regnames[rt]);
	return mips;
}