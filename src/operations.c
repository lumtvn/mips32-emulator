#include "headers.h"


int op_add(struct ptype *mips, byte rs, byte rt, byte rd)
{
	word temp;
	int i = 0;

	temp = (*(mips->regs[rs]) >> 31) & 0xFFFE + (*(mips->regs[rt]) >> 31) & 0xFFFE; //checking for overflow
	if(temp == 2)  
		return -1; //overflow

	*(mips->regs[rd]) = *(mips->regs[rs]) + *(mips->regs[rt]);

	return 0;
}

struct ptype *print_add(struct ptype *mips, byte rs, byte rt, byte rd)
{
	sprintf(mips->disasm_output, "ADD %s, %s, %s", regnames[rd], regnames[rs], regnames[rt]);
	return mips;
}