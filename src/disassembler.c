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
#include "operations.h"
#include "errors.h"
#include "elfmanager.h"
#include "environment.h"
#include "lookup.h"

#define SIX_MSB 0xFC000000
#define S_OPCODE_BITS 0x3F
#define S3_OPCODE_BITS 0x7C0
#define RG_OPCODE_BITS 0x1F0000


word get_loc(word instr)
{
    word opcodeloc;
    opcodeloc = instr & SIX_MSB;
    opcodeloc = opcodeloc >> 26; //we shift 26 places to the right, so we get the first bits in the least significant byte
    return opcodeloc;
}

//dissassembles one instruction found in address addr from section text
// act == D_EXEC : execute instruccion (execute code)
// act == D_PRINT : print instruccion (disasm)
struct ptype *disasm_instr(struct ptype *mips, vaddr32 addr, action act)
{
    word instr;
    segment *segtest;

    if(mips->elfdata->memory == NULL){mips->report = 601; return mips;}
    
    segtest = which_seg(mips->elfdata->memory, addr, 4);
    if(segtest == NULL){mips->report = 602; return mips;}
    if(strcmp(segtest->name, ".text")){mips->report = 603; return mips;}

    mips = elfreadword(mips, mips->elfdata->memory, addr);
    instr = mips->wdata;

    word opcodeloc = get_loc(instr);

    if(opcodeloc == SPECIAL){mips = manage_special(mips, instr);}
    else if(opcodeloc == SPECIAL3){mips = manage_special3(mips, instr);}
    else if(opcodeloc == REGIMM){mips = manage_regimm(mips, instr);}
    else {mips = manage_normal(mips, instr);}


    mips = getopcode(mips,instr);

    mips = which_operation_number(mips); //changes value of mips->opnum to actual operation number
    if(mips->opnum < 0){mips->report = 604; return mips;}

    send_operation(mips, act);

    // printf("hexa in 0x%x: 0x%x, operation: %s\n",i, mips->instr, mips->operation);

    return mips;
}

struct ptype *send_operation(struct ptype *mips, action act)
{
    int op_error;
    switch(mips->opnum)
    {
        case 0:
        if(act == D_EXEC)
        {op_error = op_add(mips, mips->s_arg1, mips->s_arg2, mips->s_arg3); break;}
        else if(act == D_PRINT) 
        {print_add(mips, mips->s_arg1, mips->s_arg2, mips->s_arg3); break;}
        // case 2: op_error = op_addi(act) break;
        // case 3: op_error = op_addiu(act) break;
        // case 4: op_error = op_addu(act) break;
        // case 5: op_error = op_and(act) break;
        // case 6: op_error = op_andi(act) break;
        // case 7: op_error = op_beq(act) break;
        // case 8: op_error = op_bgez(act) break;
        // case 9: op_error = op_bgtz(act) break;
        // case 10: op_error = op_blez(act) break;
        // case 11: op_error = op_bltz(act) break;
        // case 12: op_error = op_bne(act) break;
        // case 13: op_error = op_break(act) break;
        // case 14: op_error = op_div(act) break;
        // case 15: op_error = op_j(act) break;
        // case 16: op_error = op_jal(act) break;
        // case 17: op_error = op_jalr(act) break;
        // case 18: op_error = op_jr(act) break;
        // case 19: op_error = op_lb(act) break;
        // case 20: op_error = op_lbu(act) break;
        // case 21: op_error = op_lui(act) break;
        // case 22: op_error = op_lw(act) break;
        // case 23: op_error = op_mfhi(act) break;
        // case 24: op_error = op_mflo(act) break;
        // case 25: op_error = op_mult(act) break;
        // case 26: op_error = op_nop(act) break;
        // case 27: op_error = op_or(act) break;
        // case 28: op_error = op_ori(act) break;
        // case 29: op_error = op_sb(act) break;
        // case 30: op_error = op_seb(act) break;
        // case 31: op_error = op_sll(act) break;
        // case 32: op_error = op_slt(act) break;
        // case 33: op_error = op_slti(act) break;
        // case 34: op_error = op_sltiu(act) break;
        // case 35: op_error = op_sltu(act) break;
        // case 36: op_error = op_sra(act) break;
        // case 37: op_error = op_srl(act) break;
        // case 38: op_error = op_sub(act) break;
        // case 39: op_error = op_subu(act) break;
        // case 40: op_error = op_sw(act) break;
        // case 41: op_error = op_syscall(act) break;
        // case 42: op_error = op_xor(act) break;

        default: mips->report = 610; break;
    }
    if(op_error > 0)
    {
    op_report(op_error);            
    }
    return mips;
}


struct ptype *manage_normal(struct ptype *mips, word instr)
{
    mips->n_arg1 = (instr >> 21) & 0x1F;
    mips->n_arg2 = (instr >> 16) & 0x1F;
    mips->inmediate = instr & 0xFFFF;

    return mips;
}

struct ptype *manage_special(struct ptype *mips, word instr)
{
    mips->s_arg1 = (instr >> 21) & 0x1F;
    mips->s_arg2 = (instr >> 16) & 0x1F;
    mips->s_arg3 = (instr >> 11) & 0x1F;
    mips->s_arg4 = (instr >> 6) & 0x1F;

    return mips;
}

struct ptype *manage_special3(struct ptype *mips, word instr)
{
    mips->s_arg1 = (instr >> 16) & 0x1F;
    mips->s_arg2 = (instr >> 11) & 0x1F;

    return mips; 
}

struct ptype *manage_regimm(struct ptype *mips, word instr)
{
    mips->s_arg1 = (instr >> 21) & 0x1F;

    return mips;
}

struct ptype *which_operation_number(struct ptype *mips)
{
    int i;
    for(i = 0; i <= 42; i++)
    {
        if(!strcmp(opnames[i], mips->operation))
        {
            mips->opnum = i;
            mips->report = 0;
            return mips;
        }
    }
    mips->opnum = -1;
    mips->report = 80085; /*operation not found*/
    return mips;
}



/**
*@brief this function obtains the operation code, coded in a 32 bit word
*
*@param wd the word to be analized
*
*@return mips it returns the emulator structure with a new value for the field mips->operation
*
*@note for this function to work correctly, the function load_opcodes MUST be called before its execution
**/
struct ptype *getopcode(struct ptype *mips, word wd)
{

    word opcodeloc; //operation code location
    word instr;

    if(wd == 0){mips->operation = "NOP"; return mips;}

    opcodeloc = get_loc(wd); //gets location of opcode

    char *sopcode = malloc(20); //string operation code
    if(sopcode == NULL){/*error de memoria*/return mips;}
    char *psopcode = malloc(10); //string operation code with the prefix
    if(psopcode == NULL){/*error de memoria*/return mips;}

    struct nlist *np;

    if(opcodeloc == SPECIAL)
    {
        strcpy(psopcode,"S_OPCODE_");
        instr = wd & S_OPCODE_BITS;
    }
    else if(opcodeloc == SPECIAL3)
    {
        strcpy(psopcode,"S3_OPCODE_");
        instr = wd & S3_OPCODE_BITS;
        instr = instr >> 6;
    }
    else if(opcodeloc == REGIMM)
    {
        strcpy(psopcode,"RG_OPCODE_");
        instr = wd & RG_OPCODE_BITS;
        instr = instr >> 16;
    }
    else
    {
        strcpy(psopcode,"OPCODE_");
        instr = opcodeloc;
    }

    sprintf(sopcode,"%x",instr); // we turn the number into word readable string for lookup
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