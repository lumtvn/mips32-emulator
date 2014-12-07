#include "headers.h"
#include "stack.h"

//Add word
int op_add(struct ptype *mips, byte rs, byte rt, byte rd)
{
	word temp;
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

/////////////////////////////////////////////////////////////////////////////////////////////

//Add Inmidiate word
int op_addi(struct ptype *mips, byte rs, byte rt, halfword inm)
{	
	word temp;
	temp = *(mips->regs[rs]) + inm;
	if(temp < *(mips->regs[rs]))  
		return 1; //overflow
	*(mips->regs[rt]) = temp;
	return 0;
}

struct ptype *print_addi(struct ptype *mips, byte rs, byte rt, halfword inm)
{
	sprintf(mips->disasm_output, "ADDI %s, %s, 0x%x", regnames[rt], regnames[rs], inm);
	return mips;
}

/////////////////////////////////////////////////////////////////////////////////////////////

//Add Inmidiate Unsigned Word
int op_addiu(struct ptype *mips, byte rs, byte rt, halfword inm)
{	
	*(mips->regs[rt]) = *(mips->regs[rs]) + inm;
	return 0;
}

struct ptype *print_addiu(struct ptype *mips, byte rs, byte rt, halfword inm)
{
	sprintf(mips->disasm_output, "ADDIU %s, %s, 0x%x", regnames[rt], regnames[rs], inm);
	return mips;
}

/////////////////////////////////////////////////////////////////////////////////////////////

// Add unsigned word
int op_addu(struct ptype *mips, byte rs, byte rt, byte rd)
{
	*(mips->regs[rd]) = *(mips->regs[rs]) + *(mips->regs[rt]);
	return 0;
}
struct ptype *print_addu(struct ptype *mips, byte rs, byte rt, byte rd)
{
	sprintf(mips->disasm_output, "ADDU %s, %s, %s", regnames[rd], regnames[rs], regnames[rt]);
	return mips;
}


/////////////////////////////////////////////////////////////////////////////////////////////

//and
int op_and(struct ptype *mips, byte rs, byte rt, byte rd)
{
	*(mips->regs[rd]) = *(mips->regs[rs]) & *(mips->regs[rt]);
	return 0;
}

struct ptype *print_and(struct ptype *mips, byte rs, byte rt, byte rd)
{
	sprintf(mips->disasm_output, "AND %s, %s, %s", regnames[rd], regnames[rs], regnames[rt]);
	return mips;
}

/////////////////////////////////////////////////////////////////////////////////////////////

//and Inmidiate word
int op_andi(struct ptype *mips, byte rs, byte rt, halfword inm)
{	
	*(mips->regs[rt]) = *(mips->regs[rs]) & inm;
	return 0;
}

struct ptype *print_andi(struct ptype *mips, byte rs, byte rt, halfword inm)
{
	sprintf(mips->disasm_output, "ANDI %s, %s, 0x%x", regnames[rt], regnames[rs], inm);
	return mips;
}

/////////////////////////////////////////////////////////////////////////////////////////////

//Branch on Equal
int op_beq(struct ptype *mips, byte rs, byte rt, halfword inm)
{	
	word offset = inm;
	if(*(mips->regs[rt]) == *(mips->regs[rs]))
		mips->PC += offset << 2;
		
	return 0;
}

struct ptype *print_beq(struct ptype *mips, byte rs, byte rt, halfword offset)
{
	sprintf(mips->disasm_output, "BEQ %s, %s, 0x%x", regnames[rs], regnames[rt], offset);
	return mips;
}

/////////////////////////////////////////////////////////////////////////////////////////////

//Branch on Greater Than or Equal to Zero
int op_bgez(struct ptype *mips, byte rs, halfword inm)
{	
	word offset = inm;
	if((signed)*(mips->regs[rs]) >= 0)
		mips->PC += offset << 2;
		
	return 0;
}

struct ptype *print_bgez(struct ptype *mips, byte rs, halfword offset)
{
	sprintf(mips->disasm_output, "BGEZ %s, 0x%x", regnames[rs], offset);
	return mips;
}

/////////////////////////////////////////////////////////////////////////////////////////////

//Branch on Greater Than Zero
int op_bgtz(struct ptype *mips, byte rs, halfword inm)
{	
	word offset = inm;
	if((signed)*(mips->regs[rs]) > 0)
		mips->PC += offset << 2;
		
	return 0;
}

struct ptype *print_bgtz(struct ptype *mips, byte rs, halfword offset)
{
	sprintf(mips->disasm_output, "BGTZ %s, 0x%x", regnames[rs], offset);
	return mips;
}

/////////////////////////////////////////////////////////////////////////////////////////////

//Branch on Less Than or Equal to Zero
int op_blez(struct ptype *mips, byte rs, halfword inm)
{	
	word offset = inm;
	if((signed)*(mips->regs[rs]) <= 0)
		mips->PC += offset << 2;
		
	return 0;
}

struct ptype *print_blez(struct ptype *mips, byte rs, halfword offset)
{
	sprintf(mips->disasm_output, "BLEZ %s, 0x%x", regnames[rs], offset);
	return mips;
}

/////////////////////////////////////////////////////////////////////////////////////////////

//Branch on less Than Zero
int op_bltz(struct ptype *mips, byte rs, halfword inm)
{	
	word offset = inm;
	if((signed)*(mips->regs[rs]) < 0)
		mips->PC += offset << 2;
		
	return 0;
}

struct ptype *print_bltz(struct ptype *mips, byte rs, halfword offset)
{
	sprintf(mips->disasm_output, "BLTZ %s, 0x%x", regnames[rs], offset);
	return mips;
}

/////////////////////////////////////////////////////////////////////////////////////////////

//Branch on Not Equal
int op_bne(struct ptype *mips, byte rs, byte rt, halfword inm)
{	
	word offset = inm;
	if(*(mips->regs[rt]) != *(mips->regs[rs]))
		mips->PC += offset << 2;

	return 0;
}

struct ptype *print_bne(struct ptype *mips, byte rs, byte rt, halfword offset)
{
	sprintf(mips->disasm_output, "BNE %s, %s, 0x%x", regnames[rs], regnames[rt], offset);
	return mips;
}

/////////////////////////////////////////////////////////////////////////////////////////////

//divide word
int op_div(struct ptype *mips, byte rs, byte rt)
{
	if( *(mips->regs[rt]) == 0){return 10;}
	*(mips->lo) =  *(mips->regs[rs]) / *(mips->regs[rt]);
	*(mips->hi) =  *(mips->regs[rs]) % *(mips->regs[rt]);
	return 0;

}
struct ptype *print_div(struct ptype *mips, byte rs, byte rt)
{
	sprintf(mips->disasm_output, "DIV %s, %s", regnames[rs], regnames[rt]);
	return mips;
}

/////////////////////////////////////////////////////////////////////////////////////////////

//Jump
int op_j(struct ptype *mips, word idx)
{	
	mips->PC = (0xC0000000 & mips->PC) + (idx << 2);
	return 0;
}

struct ptype *print_j(struct ptype *mips, word idx)
{
	sprintf(mips->disasm_output, "J 0x%x", idx);
	return mips;
}

/////////////////////////////////////////////////////////////////////////////////////////////

//move from HI register
int op_mfhi(struct ptype *mips, byte rd)
{
	*(mips->regs[rd]) = *(mips->hi);
	return 0;
}

struct ptype *print_mfhi(struct ptype *mips, byte rd)
{
	sprintf(mips->disasm_output, "MFHI %s", regnames[rd]);
	return mips;
}

/////////////////////////////////////////////////////////////////////////////////////////////

//move from LO register
int op_mflo(struct ptype *mips, byte rd)
{
	*(mips->regs[rd]) = *(mips->lo);
	return 0;
}

struct ptype *print_mflo(struct ptype *mips, byte rd)
{
	sprintf(mips->disasm_output, "MFLO %s", regnames[rd]);
	return mips;
}

/////////////////////////////////////////////////////////////////////////////////////////////

//multiply word
int op_mult(struct ptype *mips, byte rs, byte rt)
{
	long long res = (long long)*(mips->regs[rs]) * *(mips->regs[rt]);

	*(mips->lo) =  0x00000000FFFFFFFF & res;
	*(mips->hi) =  0x00000000FFFFFFFF & (res >> 32);
	return 0;

}
struct ptype *print_mult(struct ptype *mips, byte rs, byte rt)
{
	sprintf(mips->disasm_output, "MULT %s, %s", regnames[rs], regnames[rt]);
	return mips;
}

/////////////////////////////////////////////////////////////////////////////////////////////

//No Operation
int op_nop(struct ptype *mips)
{	
	return 0;
}

struct ptype *print_nop(struct ptype *mips)
{
	sprintf(mips->disasm_output, "NOP");
	return mips;
}

/////////////////////////////////////////////////////////////////////////////////////////////

//or
int op_or(struct ptype *mips, byte rs, byte rt, byte rd)
{
	*(mips->regs[rd]) = *(mips->regs[rs]) | *(mips->regs[rt]);
	return 0;
}

struct ptype *print_or(struct ptype *mips, byte rs, byte rt, byte rd)
{
	sprintf(mips->disasm_output, "OR %s, %s, %s", regnames[rd], regnames[rs], regnames[rt]);
	return mips;
}

/////////////////////////////////////////////////////////////////////////////////////////////

//or Inmidiate word
int op_ori(struct ptype *mips, byte rs, byte rt, halfword inm)
{	
	*(mips->regs[rt]) = *(mips->regs[rs]) | inm;
	return 0;
}

struct ptype *print_ori(struct ptype *mips, byte rs, byte rt, halfword inm)
{
	sprintf(mips->disasm_output, "ORI %s, %s, 0x%x", regnames[rt], regnames[rs], inm);
	return mips;
}

///////////////////////////////////////////////////////////

// Sign-Extend Byte
int op_seb(struct ptype *mips, byte rt, byte rd)
{
	char temp;
	temp = 0xFF & *(mips->regs[rt]);
	*(mips->regs[rd]) = temp;
	return 0;
}

struct ptype *print_seb(struct ptype *mips, byte rt, byte rd)
{
	sprintf(mips->disasm_output, "SEB %s, %s", regnames[rd], regnames[rt]);
	return mips;
}

/////////////////////////////////////////////////////////////////////////////////////////////

//Shift Word Left Logical
int op_sll(struct ptype *mips, byte rt, byte rd, byte sa)
{
	*(mips->regs[rd]) = *(mips->regs[rt]) << sa;
	return 0;
}

struct ptype *print_sll(struct ptype *mips, byte rt, byte rd, byte sa)
{
	sprintf(mips->disasm_output, "SLL %s, %s, %d", regnames[rd], regnames[rt], sa);
	return mips;
}

/////////////////////////////////////////////////////////////////////////////////////////////

//Set on Less Than
int op_slt(struct ptype *mips, byte rs, byte rt, byte rd)
{
	*(mips->regs[rd]) = (signed)(*(mips->regs[rs])) < (signed)(*(mips->regs[rt]));
	return 0;
}

struct ptype *print_slt(struct ptype *mips, byte rs, byte rt, byte rd)
{
	sprintf(mips->disasm_output, "SLT %s, %s, %s", regnames[rd], regnames[rs], regnames[rt]);
	return mips;
}

/////////////////////////////////////////////////////////////////////////////////////////////

//Set on Less Than Inmidiate
int op_slti(struct ptype *mips, byte rs, byte rt, halfword inm)
{	
	*(mips->regs[rt]) = (signed)(*(mips->regs[rs])) < (signed)inm;
	return 0;
}

struct ptype *print_slti(struct ptype *mips, byte rs, byte rt, halfword inm)
{
	sprintf(mips->disasm_output, "SLTI %s, %s, 0x%x", regnames[rt], regnames[rs], inm);
	return mips;
}

/////////////////////////////////////////////////////////////////////////////////////////////

//Set on Less Than Inmidiate Unsigned
int op_sltiu(struct ptype *mips, byte rs, byte rt, halfword inm)
{	
	*(mips->regs[rt]) = (*(mips->regs[rs])) < inm;
	return 0;
}

struct ptype *print_sltiu(struct ptype *mips, byte rs, byte rt, halfword inm)
{
	sprintf(mips->disasm_output, "SLTIU %s, %s, 0x%x", regnames[rt], regnames[rs], inm);
	return mips;
}

/////////////////////////////////////////////////////////////////////////////////////////////

//Set on Less Than Unsigned
int op_sltu(struct ptype *mips, byte rs, byte rt, byte rd)
{
	*(mips->regs[rd]) = (*(mips->regs[rs])) < (*(mips->regs[rt]));
	return 0;
}

struct ptype *print_sltu(struct ptype *mips, byte rs, byte rt, byte rd)
{
	sprintf(mips->disasm_output, "SLTU %s, %s, %s", regnames[rd], regnames[rs], regnames[rt]);
	return mips;
}

/////////////////////////////////////////////////////////////////////////////////////////////

//Shift Word Right Arithmetic
int op_sra(struct ptype *mips, byte rt, byte rd, byte sa)
{
	*(mips->regs[rd]) = (signed)*(mips->regs[rt]) >> (signed char)sa;
	return 0;
}

struct ptype *print_sra(struct ptype *mips, byte rt, byte rd, byte sa)
{
	sprintf(mips->disasm_output, "SRA %s, %s, %d", regnames[rd], regnames[rt], sa);
	return mips;
}

/////////////////////////////////////////////////////////////////////////////////////////////

//Shift Word Right Logical
int op_srl(struct ptype *mips, byte rt, byte rd, byte sa)
{
	*(mips->regs[rd]) = *(mips->regs[rt]) >> sa;
	return 0;
}

struct ptype *print_srl(struct ptype *mips, byte rt, byte rd, byte sa)
{
	sprintf(mips->disasm_output, "SRL %s, %s, %d", regnames[rd], regnames[rt], sa);
	return mips;
}

/////////////////////////////////////////////////////////////////////////////////////////////

//Substract word
int op_sub(struct ptype *mips, byte rs, byte rt, byte rd)
{
	word temp;
	temp = (signed)(*(mips->regs[rs])) - (signed)(*(mips->regs[rt]));
	if(((signed)temp >> 31) & 0xFFFFFFFE  == (((signed)*(mips->regs[rs])) >> 31) & 0xFFFFFFFE) 
		return 1; //overflow
	*(mips->regs[rd]) = temp;
	return 0;
}

struct ptype *print_sub(struct ptype *mips, byte rs, byte rt, byte rd)
{
	sprintf(mips->disasm_output, "SUB %s, %s, %s", regnames[rd], regnames[rs], regnames[rt]);
	return mips;
}

/////////////////////////////////////////////////////////////////////////////////////////////

//Substract Unsigned word
int op_subu(struct ptype *mips, byte rs, byte rt, byte rd)
{
	*(mips->regs[rd]) = *(mips->regs[rs]) + ~(*(mips->regs[rt])) + 1;
	return 0;
}

struct ptype *print_subu(struct ptype *mips, byte rs, byte rt, byte rd)
{
	sprintf(mips->disasm_output, "SUBU %s, %s, %s", regnames[rd], regnames[rs], regnames[rt]);
	return mips;
}

/////////////////////////////////////////////////////////////////////////////////////////////

//xor
int op_xor(struct ptype *mips, byte rs, byte rt, byte rd)
{
	*(mips->regs[rd]) = *(mips->regs[rs]) ^ *(mips->regs[rt]);
	return 0;
}

struct ptype *print_xor(struct ptype *mips, byte rs, byte rt, byte rd)
{
	sprintf(mips->disasm_output, "XOR %s, %s, %s", regnames[rd], regnames[rs], regnames[rt]);
	return mips;
}