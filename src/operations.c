/**
 * @file operations.c
 * @author Luciano Mantovani
 * @date November 2014
 * @brief this file contains all the implementations for the operations required from the mips processor. For executing them and printing them
 * @details each excecution function may return an integer bigger than 0 if and only if the 
 * description of the operation has exceptions. If not it does what it can with what it has.
 * 
 */

#include "headers.h"
#include "elfmanager.h"

//Add word
int op_add(struct mipsstr *mips, byte rs, byte rt, byte rd)
{
	word temp;
	temp = *(mips->regs[rs]) + *(mips->regs[rt]);
	if(temp < *(mips->regs[rs]))  
		return 1; //overflow
	*(mips->regs[rd]) = temp;
	
	mips->PC = mips->PC + 4;
	return 0;
}

struct mipsstr *print_add(struct mipsstr *mips, byte rs, byte rt, byte rd)
{
	sprintf(mips->disasm_output, "ADD %s, %s, %s", regnames[rd], regnames[rs], regnames[rt]);
	return mips;
}

/////////////////////////////////////////////////////////////////////////////////////////////

//Add Inmidiate word
int op_addi(struct mipsstr *mips, byte rs, byte rt, halfword inm)
{	
	word temp;
	temp = *(mips->regs[rs]) + (signed)inm;
	if(temp < *(mips->regs[rs]))  
		return 1; //overflow
	*(mips->regs[rt]) = temp;
	
	mips->PC = mips->PC + 4;
	return 0;
}

struct mipsstr *print_addi(struct mipsstr *mips, byte rs, byte rt, halfword inm)
{
	sprintf(mips->disasm_output, "ADDI %s, %s, 0x%x", regnames[rt], regnames[rs], inm);
	return mips;
}

/////////////////////////////////////////////////////////////////////////////////////////////

//Add Inmidiate Unsigned Word
int op_addiu(struct mipsstr *mips, byte rs, byte rt, halfword inm)
{	
	*(mips->regs[rt]) = *(mips->regs[rs]) + inm;
	
	mips->PC = mips->PC + 4;
	return 0;
}

struct mipsstr *print_addiu(struct mipsstr *mips, byte rs, byte rt, halfword inm)
{
	sprintf(mips->disasm_output, "ADDIU %s, %s, 0x%x", regnames[rt], regnames[rs], inm);
	return mips;
}

/////////////////////////////////////////////////////////////////////////////////////////////

// Add unsigned word
int op_addu(struct mipsstr *mips, byte rs, byte rt, byte rd)
{
	*(mips->regs[rd]) = *(mips->regs[rs]) + *(mips->regs[rt]);
	
	mips->PC = mips->PC + 4;
	return 0;
}
struct mipsstr *print_addu(struct mipsstr *mips, byte rs, byte rt, byte rd)
{
	sprintf(mips->disasm_output, "ADDU %s, %s, %s", regnames[rd], regnames[rs], regnames[rt]);
	return mips;
}


/////////////////////////////////////////////////////////////////////////////////////////////

//and
int op_and(struct mipsstr *mips, byte rs, byte rt, byte rd)
{
	*(mips->regs[rd]) = *(mips->regs[rs]) & *(mips->regs[rt]);
	
	mips->PC = mips->PC + 4;
	return 0;
}

struct mipsstr *print_and(struct mipsstr *mips, byte rs, byte rt, byte rd)
{
	sprintf(mips->disasm_output, "AND %s, %s, %s", regnames[rd], regnames[rs], regnames[rt]);
	return mips;
}

/////////////////////////////////////////////////////////////////////////////////////////////

//and Inmidiate word
int op_andi(struct mipsstr *mips, byte rs, byte rt, halfword inm)
{	
	*(mips->regs[rt]) = *(mips->regs[rs]) & inm;
	
	mips->PC = mips->PC + 4;
	return 0;
}

struct mipsstr *print_andi(struct mipsstr *mips, byte rs, byte rt, halfword inm)
{
	sprintf(mips->disasm_output, "ANDI %s, %s, 0x%x", regnames[rt], regnames[rs], inm);
	return mips;
}

/////////////////////////////////////////////////////////////////////////////////////////////

//Branch on Equal
int op_beq(struct mipsstr *mips, byte rs, byte rt, halfword inm)
{	
	word offset = (signed)inm;
	if(*(mips->regs[rt]) == *(mips->regs[rs]))
		mips->PC += (offset << 2);
	// else
		mips->PC = mips->PC + 4; 		
	
	return 0;
}

struct mipsstr *print_beq(struct mipsstr *mips, byte rs, byte rt, halfword inm)
{	
	word offset = (signed)inm;
	sprintf(mips->disasm_output, "BEQ %s, %s, 0x%x", regnames[rs], regnames[rt], (offset << 2) + mips->pc_temp);
	return mips;
}

/////////////////////////////////////////////////////////////////////////////////////////////

//Branch on Greater Than or Equal to Zero
int op_bgez(struct mipsstr *mips, byte rs, halfword inm)
{	
	word offset = (signed)inm;
	if((signed)*(mips->regs[rs]) >= 0)
		mips->PC += (offset << 2);
	// else
		mips->PC = mips->PC + 4; 

	return 0;
}

struct mipsstr *print_bgez(struct mipsstr *mips, byte rs, halfword inm)
{
	word offset = (signed)inm;
	sprintf(mips->disasm_output, "BGEZ %s, 0x%x", regnames[rs], (offset << 2) + mips->pc_temp);
	return mips;
}

/////////////////////////////////////////////////////////////////////////////////////////////

//Branch on Greater Than Zero
int op_bgtz(struct mipsstr *mips, byte rs, halfword inm)
{	
	word offset = (signed)inm;
	if((signed)*(mips->regs[rs]) > 0)
		mips->PC += (offset << 2);
	// else
		mips->PC = mips->PC + 4; 		
	
	return 0;
}

struct mipsstr *print_bgtz(struct mipsstr *mips, byte rs, halfword inm)
{
	word offset = (signed)inm;
	sprintf(mips->disasm_output, "BGTZ %s, 0x%x", regnames[rs], (offset << 2) + mips->pc_temp);
	return mips;
}

/////////////////////////////////////////////////////////////////////////////////////////////

//Branch on Less Than or Equal to Zero
int op_blez(struct mipsstr *mips, byte rs, halfword inm)
{	
	word offset = (signed)inm;
	if((signed)*(mips->regs[rs]) <= 0)
		mips->PC += (offset << 2);
	// else
		mips->PC = mips->PC + 4; 		
	
	return 0;
}

struct mipsstr *print_blez(struct mipsstr *mips, byte rs, halfword inm)
{
	word offset = (signed)inm;
	sprintf(mips->disasm_output, "BLEZ %s, 0x%x", regnames[rs], (offset << 2) + mips->pc_temp);
	return mips;
}

/////////////////////////////////////////////////////////////////////////////////////////////

//Branch on less Than Zero
int op_bltz(struct mipsstr *mips, byte rs, halfword inm)
{	
	word offset = (signed)inm;
	if((signed)*(mips->regs[rs]) < 0)
		mips->PC += (offset << 2);
	// else
		mips->PC = mips->PC + 4; 		
	
	return 0;
}

struct mipsstr *print_bltz(struct mipsstr *mips, byte rs, halfword inm)
{
	word offset = (signed)inm;
 	sprintf(mips->disasm_output, "BLTZ %s, 0x%x", regnames[rs], (offset << 2) + mips->pc_temp);
	return mips;
}

/////////////////////////////////////////////////////////////////////////////////////////////

//Branch on Not Equal
int op_bne(struct mipsstr *mips, byte rs, byte rt, halfword inm)
{	
	word offset = (signed)inm;
	if(*(mips->regs[rt]) != *(mips->regs[rs]))
		mips->PC += (offset << 2);
	// else
		mips->PC = mips->PC + 4; 
	
	return 0;
}

struct mipsstr *print_bne(struct mipsstr *mips, byte rs, byte rt, halfword inm)
{
	word offset = (signed)inm;
	sprintf(mips->disasm_output, "BNE %s, %s, 0x%x", regnames[rs], regnames[rt], (offset << 2) + mips->pc_temp);
	return mips;
}

/////////////////////////////////////////////////////////////////////////////////////////////

//divide word
int op_div(struct mipsstr *mips, byte rs, byte rt)
{
	if( *(mips->regs[rt]) == 0){return 10;}
	*(mips->lo) =  *(mips->regs[rs]) / *(mips->regs[rt]);
	*(mips->hi) =  *(mips->regs[rs]) % *(mips->regs[rt]);
	
	mips->PC = mips->PC + 4;
	return 0;

}
struct mipsstr *print_div(struct mipsstr *mips, byte rs, byte rt)
{
	sprintf(mips->disasm_output, "DIV %s, %s", regnames[rs], regnames[rt]);
	return mips;
}

/////////////////////////////////////////////////////////////////////////////////////////////

//Jump
int op_j(struct mipsstr *mips, word idx)
{	
	mips->PC = (0xF0000000 & mips->PC) + (idx << 2);
	
	return 0;
}

struct mipsstr *print_j(struct mipsstr *mips, word idx)
{
	sprintf(mips->disasm_output, "J 0x%x", (0xF0000000 & mips->pc_temp) + (idx << 2));
	return mips;
}

/////////////////////////////////////////////////////////////////////////////////////////////

//Jump and Link
int op_jal(struct mipsstr *mips, word idx)
{	
	*(mips->regs[31]) = mips->PC + 8;
	mips->PC = (0xF0000000 & mips->PC) + (idx << 2);
	
	return 0;
}

struct mipsstr *print_jal(struct mipsstr *mips, word idx)
{
	sprintf(mips->disasm_output, "JAL 0x%x",(0xF0000000 & mips->pc_temp) + (idx <<2));
	return mips;
}

/////////////////////////////////////////////////////////////////////////////////////////////

//Jump and Link Register
int op_jalr(struct mipsstr *mips, byte rs, byte rd)
{	
	word temp;
	temp = *(mips->regs[rs]);
	*(mips->regs[rd]) = mips->PC + 8;
	if(temp%4 != 0)
	{
		mips->PC = mips->PC + 4;
		return 20;
	}
	else mips->PC = temp;

	
	return 0;
}

struct mipsstr *print_jalr(struct mipsstr *mips, byte rs, byte rd)
{
	sprintf(mips->disasm_output, "JALR %s, %s", regnames[rd], regnames[rs]);
	return mips;
}

/////////////////////////////////////////////////////////////////////////////////////////////

//Jump Register
int op_jr(struct mipsstr *mips, byte rs)
{	
	word temp;
	temp = *(mips->regs[rs]);
	if(temp%4 != 0)
		return 21;
	else mips->PC = temp;
	
	return 0;
}

struct mipsstr *print_jr(struct mipsstr *mips, byte rs, byte rd)
{
	sprintf(mips->disasm_output, "JR %s", regnames[rs]);
	return mips;
}

/////////////////////////////////////////////////////////////////////////////////////////////

//Load Byte
int op_lb(struct mipsstr *mips, byte base, byte rt, halfword offset)
{	
	vaddr32 addr = *(mips->regs[base]) + (signed) offset;
	mips = elfreadbyte(mips, mips->elfdata->memory, addr);
	if(mips->report == 502)
		return 30;
	if(mips->report == 501)
		return 31;
	*(mips->regs[rt]) = mips->bdata;
	
	mips->PC = mips->PC + 4;
	return 0;
}

struct mipsstr *print_lb(struct mipsstr *mips, byte base, byte rt, halfword offset)
{
	sprintf(mips->disasm_output, "LB %s, %d(%s)", regnames[rt], offset, regnames[base]);
	return mips;
}

/////////////////////////////////////////////////////////////////////////////////////////////

//Load Byte Unsigned
int op_lbu(struct mipsstr *mips, byte base, byte rt, halfword offset)
{	
	vaddr32 addr = *(mips->regs[base]) + offset;
	mips = elfreadbyte(mips, mips->elfdata->memory, addr);
	if(mips->report == 502)
		return 40;
	if(mips->report == 501)
		return 41;
	*(mips->regs[rt]) = mips->bdata;
	
	mips->PC = mips->PC + 4;
	return 0;
}

struct mipsstr *print_lbu(struct mipsstr *mips, byte base, byte rt, halfword offset)
{
	sprintf(mips->disasm_output, "LBU %s, %d(%s)", regnames[rt], offset, regnames[base]);
	return mips;
}

/////////////////////////////////////////////////////////////////////////////////////////////

//Load Upper Inmediate
int op_lui(struct mipsstr *mips, byte rt, halfword inmediate)
{	
	 *(mips->regs[rt]) = inmediate << 16;
	 
	 mips->PC = mips->PC + 4;
	 return 0;
}

struct mipsstr *print_lui(struct mipsstr *mips, byte rt, halfword inmediate)
{
	sprintf(mips->disasm_output, "LUI %s, %x", regnames[rt], inmediate);
	return mips;
}

/////////////////////////////////////////////////////////////////////////////////////////////

//Load Word
int op_lw(struct mipsstr *mips, byte base, byte rt, halfword offset)
{	
	vaddr32 addr = *(mips->regs[base]) + offset;
	if(addr%4 != 0)
		return 50;
	mips = elfreadword(mips, mips->elfdata->memory, addr);
	if(mips->report == 502)
		return 51;
	if(mips->report == 501)
		return 52;

	*(mips->regs[rt]) = mips->wdata;
	
	mips->PC = mips->PC + 4;
	return 0;
}

struct mipsstr *print_lw(struct mipsstr *mips, byte base, byte rt, halfword offset)
{
	sprintf(mips->disasm_output, "LW %s, %d(%s)", regnames[rt], offset, regnames[base]);
	return mips;
}

/////////////////////////////////////////////////////////////////////////////////////////////

//move from HI register
int op_mfhi(struct mipsstr *mips, byte rd)
{
	*(mips->regs[rd]) = *(mips->hi);
	
	mips->PC = mips->PC + 4;
	return 0;
}

struct mipsstr *print_mfhi(struct mipsstr *mips, byte rd)
{
	sprintf(mips->disasm_output, "MFHI %s", regnames[rd]);
	return mips;
}

/////////////////////////////////////////////////////////////////////////////////////////////

//move from LO register
int op_mflo(struct mipsstr *mips, byte rd)
{
	*(mips->regs[rd]) = *(mips->lo);
	
	mips->PC = mips->PC + 4;
	return 0;
}

struct mipsstr *print_mflo(struct mipsstr *mips, byte rd)
{
	sprintf(mips->disasm_output, "MFLO %s", regnames[rd]);
	return mips;
}

/////////////////////////////////////////////////////////////////////////////////////////////

//multiply word
int op_mult(struct mipsstr *mips, byte rs, byte rt)
{
	long long res = (long long)*(mips->regs[rs]) * *(mips->regs[rt]);

	*(mips->lo) =  0x00000000FFFFFFFF & res;
	*(mips->hi) =  0x00000000FFFFFFFF & (res >> 32);
	
	mips->PC = mips->PC + 4;
	return 0;

}
struct mipsstr *print_mult(struct mipsstr *mips, byte rs, byte rt)
{
	sprintf(mips->disasm_output, "MULT %s, %s", regnames[rs], regnames[rt]);
	return mips;
}

/////////////////////////////////////////////////////////////////////////////////////////////

//No Operation
int op_nop(struct mipsstr *mips)
{	
	mips->PC = mips->PC + 4;
	return 0;
}

struct mipsstr *print_nop(struct mipsstr *mips)
{
	sprintf(mips->disasm_output, "NOP");
	return mips;
}

/////////////////////////////////////////////////////////////////////////////////////////////

//or
int op_or(struct mipsstr *mips, byte rs, byte rt, byte rd)
{
	*(mips->regs[rd]) = *(mips->regs[rs]) | *(mips->regs[rt]);
	
	mips->PC = mips->PC + 4;
	return 0;
}

struct mipsstr *print_or(struct mipsstr *mips, byte rs, byte rt, byte rd)
{
	sprintf(mips->disasm_output, "OR %s, %s, %s", regnames[rd], regnames[rs], regnames[rt]);
	return mips;
}

/////////////////////////////////////////////////////////////////////////////////////////////

//or Inmidiate word
int op_ori(struct mipsstr *mips, byte rs, byte rt, halfword inm)
{	
	*(mips->regs[rt]) = *(mips->regs[rs]) | inm;
	
	mips->PC = mips->PC + 4;
	return 0;
}

struct mipsstr *print_ori(struct mipsstr *mips, byte rs, byte rt, halfword inm)
{
	sprintf(mips->disasm_output, "ORI %s, %s, 0x%x", regnames[rt], regnames[rs], inm);
	return mips;
}

/////////////////////////////////////////////////////////////////////////////////////////////

//Store Byte
int op_sb(struct mipsstr *mips, byte base, byte rt, halfword offset)
{	
	vaddr32 addr = *(mips->regs[base]) + (signed) offset;
	mips = elfwritebyte(mips, mips->elfdata->memory, *(mips->regs[rt]), addr);
	if(mips->report == 502)
		return 60;
	if(mips->report == 501)
		return 61;
	if(mips->report == 503)
		return 62;
	
	mips->PC = mips->PC + 4;
	return 0;
}

struct mipsstr *print_sb(struct mipsstr *mips, byte base, byte rt, halfword offset)
{
	sprintf(mips->disasm_output, "SB %s, %d(%s)", regnames[rt], offset, regnames[base]);
	return mips;
}

///////////////////////////////////////////////////////////

// Sign-Extend Byte
int op_seb(struct mipsstr *mips, byte rt, byte rd)
{
	char temp;
	temp = 0xFF & *(mips->regs[rt]);
	*(mips->regs[rd]) = temp;
	
	mips->PC = mips->PC + 4;
	return 0;
}

struct mipsstr *print_seb(struct mipsstr *mips, byte rt, byte rd)
{
	sprintf(mips->disasm_output, "SEB %s, %s", regnames[rd], regnames[rt]);
	return mips;
}

/////////////////////////////////////////////////////////////////////////////////////////////

//Shift Word Left Logical
int op_sll(struct mipsstr *mips, byte rt, byte rd, byte sa)
{
	*(mips->regs[rd]) = *(mips->regs[rt]) << sa;
	
	mips->PC = mips->PC + 4;
	return 0;
}

struct mipsstr *print_sll(struct mipsstr *mips, byte rt, byte rd, byte sa)
{
	sprintf(mips->disasm_output, "SLL %s, %s, %d", regnames[rd], regnames[rt], sa);
	return mips;
}

/////////////////////////////////////////////////////////////////////////////////////////////

//Set on Less Than
int op_slt(struct mipsstr *mips, byte rs, byte rt, byte rd)
{
	*(mips->regs[rd]) = (signed)(*(mips->regs[rs])) < (signed)(*(mips->regs[rt]));
	
	mips->PC = mips->PC + 4;
	return 0;
}

struct mipsstr *print_slt(struct mipsstr *mips, byte rs, byte rt, byte rd)
{
	sprintf(mips->disasm_output, "SLT %s, %s, %s", regnames[rd], regnames[rs], regnames[rt]);
	return mips;
}

/////////////////////////////////////////////////////////////////////////////////////////////

//Set on Less Than Inmidiate
int op_slti(struct mipsstr *mips, byte rs, byte rt, halfword inm)
{	
	*(mips->regs[rt]) = (signed)(*(mips->regs[rs])) < (signed)inm;
	
	mips->PC = mips->PC + 4;
	return 0;
}

struct mipsstr *print_slti(struct mipsstr *mips, byte rs, byte rt, halfword inm)
{
	sprintf(mips->disasm_output, "SLTI %s, %s, 0x%x", regnames[rt], regnames[rs], inm);
	return mips;
}

/////////////////////////////////////////////////////////////////////////////////////////////

//Set on Less Than Inmidiate Unsigned
int op_sltiu(struct mipsstr *mips, byte rs, byte rt, halfword inm)
{	
	*(mips->regs[rt]) = (*(mips->regs[rs])) < inm;
	
	mips->PC = mips->PC + 4;
	return 0;
}

struct mipsstr *print_sltiu(struct mipsstr *mips, byte rs, byte rt, halfword inm)
{
	sprintf(mips->disasm_output, "SLTIU %s, %s, 0x%x", regnames[rt], regnames[rs], inm);
	return mips;
}

/////////////////////////////////////////////////////////////////////////////////////////////

//Set on Less Than Unsigned
int op_sltu(struct mipsstr *mips, byte rs, byte rt, byte rd)
{
	*(mips->regs[rd]) = (*(mips->regs[rs])) < (*(mips->regs[rt]));
	
	mips->PC = mips->PC + 4;
	return 0;
}

struct mipsstr *print_sltu(struct mipsstr *mips, byte rs, byte rt, byte rd)
{
	sprintf(mips->disasm_output, "SLTU %s, %s, %s", regnames[rd], regnames[rs], regnames[rt]);
	return mips;
}

/////////////////////////////////////////////////////////////////////////////////////////////

//Shift Word Right Arithmetic
int op_sra(struct mipsstr *mips, byte rt, byte rd, byte sa)
{
	*(mips->regs[rd]) = (signed)*(mips->regs[rt]) >> (signed char)sa;
	
	mips->PC = mips->PC + 4;
	return 0;
}

struct mipsstr *print_sra(struct mipsstr *mips, byte rt, byte rd, byte sa)
{
	sprintf(mips->disasm_output, "SRA %s, %s, %d", regnames[rd], regnames[rt], sa);
	return mips;
}

/////////////////////////////////////////////////////////////////////////////////////////////

//Shift Word Right Logical
int op_srl(struct mipsstr *mips, byte rt, byte rd, byte sa)
{
	*(mips->regs[rd]) = *(mips->regs[rt]) >> sa;
	
	mips->PC = mips->PC + 4;
	return 0;
}

struct mipsstr *print_srl(struct mipsstr *mips, byte rt, byte rd, byte sa)
{
	sprintf(mips->disasm_output, "SRL %s, %s, %d", regnames[rd], regnames[rt], sa);
	return mips;
}

/////////////////////////////////////////////////////////////////////////////////////////////

//Substract word
int op_sub(struct mipsstr *mips, byte rs, byte rt, byte rd)
{
	word temp;
	temp = (signed)(*(mips->regs[rs])) - (signed)(*(mips->regs[rt]));
	if((0x80000000 & temp) != (0x80000000 & *(mips->regs[rs]))) 
		return 1; //overflow
	*(mips->regs[rd]) = temp;
	
	mips->PC = mips->PC + 4;
	return 0;
}

struct mipsstr *print_sub(struct mipsstr *mips, byte rs, byte rt, byte rd)
{
	sprintf(mips->disasm_output, "SUB %s, %s, %s", regnames[rd], regnames[rs], regnames[rt]);
	return mips;
}

/////////////////////////////////////////////////////////////////////////////////////////////

//Substract Unsigned word
int op_subu(struct mipsstr *mips, byte rs, byte rt, byte rd)
{
	*(mips->regs[rd]) = *(mips->regs[rs]) + ~(*(mips->regs[rt])) + 1;
	
	mips->PC = mips->PC + 4;
	return 0;
}

struct mipsstr *print_subu(struct mipsstr *mips, byte rs, byte rt, byte rd)
{
	sprintf(mips->disasm_output, "SUBU %s, %s, %s", regnames[rd], regnames[rs], regnames[rt]);
	return mips;
}

/////////////////////////////////////////////////////////////////////////////////////////////

//Store Word
int op_sw(struct mipsstr *mips, byte base, byte rt, halfword offset)
{	
	vaddr32 addr = *(mips->regs[base]) + (signed) offset;
	if(addr%4 != 0)
		return 73;
    segment *seg;
    seg = which_seg(mips->elfdata->memory,addr,4);

    // printf("0x%x\n", *(seg->content + addr - seg->start._32));
    *(seg->content + addr - seg->start._32) = (*(mips->regs[rt]) >> 24) & 0xFF;
    *(seg->content + addr - seg->start._32 + 1) = (*(mips->regs[rt]) >> 16) & 0xFF;
    *(seg->content + addr - seg->start._32 + 2) = (*(mips->regs[rt]) >> 8) & 0xFF;
    *(seg->content + addr - seg->start._32 + 3) = *(mips->regs[rt]);
	
	mips->PC = mips->PC + 4;
	return 0;
}

struct mipsstr *print_sw(struct mipsstr *mips, byte base, byte rt, halfword offset)
{
	sprintf(mips->disasm_output, "SW %s, %d(%s)", regnames[rt], offset, regnames[base]);
	return mips;
}

/////////////////////////////////////////////////////////////////////////////////////////////

//Store Word
int op_syscall(struct mipsstr *mips)
{	
	printf("program ended at address %08x with the next values for special registers: \n", mips->PC);
	printf( "%s: %08x\n" ,regnames[2], *mips->regs[2]);
	printf( "%s: %08x\n" ,regnames[4], *mips->regs[4]);
	printf( "%s: %08x\n" ,regnames[5], *mips->regs[5]);
	printf( "%s: %08x\n" ,regnames[6], *mips->regs[6]);
	printf( "%s: %08x\n" ,regnames[7], *mips->regs[7]);

	mips->fl_end = true;
	
	mips->PC = mips->PC + 4;
	return 0;
}

struct mipsstr *print_syscall(struct mipsstr *mips)
{
	sprintf(mips->disasm_output, "SYSCALL");
	return mips;
}

/////////////////////////////////////////////////////////////////////////////////////////////

//xor
int op_xor(struct mipsstr *mips, byte rs, byte rt, byte rd)
{
	*(mips->regs[rd]) = *(mips->regs[rs]) ^ *(mips->regs[rt]);
	
	mips->PC = mips->PC + 4;
	return 0;
}

struct mipsstr *print_xor(struct mipsstr *mips, byte rs, byte rt, byte rd)
{
	sprintf(mips->disasm_output, "XOR %s, %s, %s", regnames[rd], regnames[rs], regnames[rt]);
	return mips;
}