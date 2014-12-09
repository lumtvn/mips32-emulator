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

struct ptype *execute_text(struct ptype *mips)
{
    segment *segtext = get_seg_by_name(mips->elfdata->memory, ".text");
    word textsize = segtext->size._32;

    while(mips->PC < textsize)
    {
        disasm_instr(mips, mips->PC, D_EXEC);
        if(mips->report > 0){return mips;}

        mips->PC = mips->PC + 4;
    }

    return mips;
}


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


    mips = getopcode(mips,instr); //loads mips->operation with operation name

    mips = which_operation_number(mips); //changes value of mips->opnum to actual operation number
    if(mips->opnum < 0){mips->report = 604; return mips;}

    if(mips->opnum == 14 || mips->opnum == 15) //j and jal instructions
        mips->inmediate = 0x03FFFFFF & instr;

    if(act == D_PRINT)
        sprintf(mips->instr_output, "%08x", instr);

    send_operation(mips, act);

    // printf("hexa in 0x%x: 0x%x, operation: %s\n",i, mips->instr, mips->operation);
    mips->report = 0;

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


struct ptype *send_operation(struct ptype *mips, action act)
{
    int op_error = 0;
    switch(mips->opnum)
    {
    case 0: 
        if(mips->s_arg4 != 0){mips->report = 620; break;}
        if(act == D_EXEC)
        {op_error = op_add(mips, mips->s_arg1, mips->s_arg2, mips->s_arg3); break;}
        else mips = print_add(mips, mips->s_arg1, mips->s_arg2, mips->s_arg3); break;
    

    case 1:
        if(act == D_EXEC) 
        {op_error = op_addi(mips, mips->n_arg1, mips->n_arg2, mips->inmediate); break;}
        else mips = print_addi(mips, mips->n_arg1, mips->n_arg2, mips->inmediate); break;

    case 2:
        if(act == D_EXEC) 
        {op_error = op_addiu(mips, mips->n_arg1, mips->n_arg2, mips->inmediate); break;}
        else mips = print_addiu(mips, mips->n_arg1, mips->n_arg2, mips->inmediate); break;

    case 3: 
        if(mips->s_arg4 != 0){mips->report = 620; break;}
        if(act == D_EXEC) 
        {op_error = op_addu(mips, mips->s_arg1, mips->s_arg2, mips->s_arg3); break;}
        else mips = print_addu(mips, mips->s_arg1, mips->s_arg2, mips->s_arg3); break;

    case 4: 
        if(mips->s_arg4 != 0){mips->report = 620; break;}
        if(act == D_EXEC) 
        {op_error = op_and(mips, mips->s_arg1, mips->s_arg2, mips->s_arg3); break;}
        else mips = print_and(mips, mips->s_arg1, mips->s_arg2, mips->s_arg3); break;
    
    case 5: 
        if(act == D_EXEC) 
        {op_error = op_andi(mips, mips->n_arg1, mips->n_arg2, mips->inmediate); break;}
        else mips = print_andi(mips, mips->n_arg1, mips->n_arg2, mips->inmediate); break;

    case 6: 
        if(act == D_EXEC) 
        {op_error = op_beq(mips, mips->n_arg1, mips->n_arg2, mips->inmediate); break;}
        else mips = print_beq(mips, mips->n_arg1, mips->n_arg2, mips->inmediate); break;

    case 7: 
        if(mips->s_arg2 != 1){mips->report = 620; break;}
        if(act == D_EXEC) 
        {op_error = op_bgez(mips, mips->n_arg1, mips->inmediate); break;}
        else mips = print_bgez(mips, mips->n_arg1, mips->inmediate); break;

    case 8: 
        if(mips->s_arg2 != 0){mips->report = 620; break;}
        if(act == D_EXEC) 
        {op_error = op_bgtz(mips, mips->n_arg1, mips->inmediate); break;}
        else mips = print_bgtz(mips, mips->n_arg1, mips->inmediate); break;

    case 9: 
        if(mips->s_arg2 != 0){mips->report = 620; break;}
        if(act == D_EXEC) 
        {op_error = op_blez(mips, mips->n_arg1, mips->inmediate); break;}
        else mips = print_blez(mips, mips->n_arg1, mips->inmediate); break;

    case 10: 
        if(mips->s_arg2 != 0){mips->report = 620; break;}
        if(act == D_EXEC) 
        {op_error = op_bltz(mips, mips->n_arg1, mips->inmediate); break;}
        else mips = print_bltz(mips, mips->n_arg1, mips->inmediate); break;

    case 11: 
        if(act == D_EXEC) 
        {op_error = op_bne(mips, mips->n_arg1, mips->n_arg2, mips->inmediate); break;}
        else mips = print_bne(mips, mips->n_arg1, mips->n_arg2, mips->inmediate); break;

    // case 13: op_error = op_break(ct) break;

    case 13: 
        if(mips->s_arg3 != 0){mips->report = 620; break;}
        if(mips->s_arg4 != 0){mips->report = 620; break;}
        if(act == D_EXEC) 
        {op_error = op_div(mips, mips->s_arg1, mips->s_arg2); break;}
        else mips = print_div(mips, mips->s_arg1, mips->s_arg2); break;

    case 14:
        if(act == D_EXEC) 
        {op_error = op_j(mips, mips->inmediate); break;}
        else mips = print_j(mips, mips->inmediate); break;

    case 15:
        if(act == D_EXEC) 
        {op_error = op_jal(mips, mips->inmediate); break;}
        else mips = print_jal(mips, mips->inmediate); break;

    case 16: 
        if(mips->s_arg2 != 0){mips->report = 620; break;}
        if(act == D_EXEC) 
        {op_error = op_jalr(mips, mips->s_arg1, mips->s_arg3); break;}
        else mips = print_jalr(mips, mips->s_arg1, mips->s_arg3); break;

    case 17: 
        if(mips->s_arg2 != 0){mips->report = 620; break;}
        if(mips->s_arg3 != 0){mips->report = 620; break;}
        if(act == D_EXEC) 
        {op_error = op_jr(mips, mips->s_arg1); break;}
        else mips = print_jr(mips, mips->s_arg1); break;

    case 18: 
        if(act == D_EXEC) 
        {op_error = op_lb(mips, mips->n_arg1, mips->n_arg2, mips->inmediate); break;}
        else mips = print_lb(mips, mips->n_arg1, mips->n_arg2, mips->inmediate); break;

    case 19: 
        if(act == D_EXEC) 
        {op_error = op_lbu(mips, mips->n_arg1, mips->n_arg2, mips->inmediate); break;}
        else mips = print_lbu(mips, mips->n_arg1, mips->n_arg2, mips->inmediate); break;

    case 20: 
        if(mips->s_arg1 != 0){mips->report = 620; break;}
        if(act == D_EXEC) 
        {op_error = op_lui(mips, mips->n_arg2, mips->inmediate); break;}
        else mips = print_lui(mips, mips->n_arg2, mips->inmediate); break;

    case 21: 
        if(act == D_EXEC) 
        {op_error = op_lw(mips, mips->n_arg1, mips->n_arg2, mips->inmediate); break;}
        else mips = print_lw(mips, mips->n_arg1, mips->n_arg2, mips->inmediate); break;

    case 22: 
        if(mips->s_arg1 != 0 && mips->s_arg2 != 0 && mips->s_arg4 != 0){mips->report = 620; break;}
        if(act == D_EXEC)
        {op_error = op_mfhi(mips, mips->s_arg3); break;}
        else mips = print_mfhi(mips, mips->s_arg3); break;
    
    case 23: 
        if(mips->s_arg1 != 0 && mips->s_arg2 != 0 && mips->s_arg4 != 0){mips->report = 620; break;}
        if(act == D_EXEC)
        {op_error = op_mflo(mips, mips->s_arg3); break;}
        else mips = print_mflo(mips, mips->s_arg3); break;
    

    case 24: 
        if(mips->s_arg3 != 0){mips->report = 620; break;}
        if(mips->s_arg4 != 0){mips->report = 620; break;}
        if(act == D_EXEC) 
        {op_error = op_mult(mips, mips->s_arg1, mips->s_arg2); break;}
        else mips = print_mult(mips, mips->s_arg1, mips->s_arg2); break;

    case 25: 
        if(act == D_EXEC) 
        {op_error = op_nop(mips); break;}
        else mips = print_nop(mips); break;

    case 26: 
        if(mips->s_arg4 != 0){mips->report = 620; break;}
        if(act == D_EXEC) 
        {op_error = op_or(mips, mips->s_arg1, mips->s_arg2, mips->s_arg3); break;}
        else mips = print_or(mips, mips->s_arg1, mips->s_arg2, mips->s_arg3); break;

    case 27: 
        if(act == D_EXEC) 
        {op_error = op_ori(mips, mips->n_arg1, mips->n_arg2, mips->inmediate); break;}
        else mips = print_ori(mips, mips->n_arg1, mips->n_arg2, mips->inmediate); break;

    case 28: 
        if(act == D_EXEC) 
        {op_error = op_sb(mips, mips->n_arg1, mips->n_arg2, mips->inmediate); break;}
        else mips = print_sb(mips, mips->n_arg1, mips->n_arg2, mips->inmediate); break;

    case 29: 
        if(act == D_EXEC) 
        {op_error = op_seb(mips, mips->s_arg1, mips->s_arg2); break;}
        else mips = print_seb(mips, mips->s_arg1, mips->s_arg2); break;

    case 30: 
        if(mips->s_arg1 != 0){mips->report = 620; break;}
        if(act == D_EXEC) 
        {op_error = op_sll(mips, mips->s_arg2, mips->s_arg3, mips->s_arg4); break;}
        else mips = print_sll(mips, mips->s_arg2, mips->s_arg3, mips->s_arg4); break;

    case 31: 
        if(mips->s_arg4 != 0){mips->report = 620; break;}
        if(act == D_EXEC) 
        {op_error = op_slt(mips, mips->s_arg1, mips->s_arg2, mips->s_arg3); break;}
        else mips = print_slt(mips, mips->s_arg1, mips->s_arg2, mips->s_arg3); break;

    case 32: 
        if(act == D_EXEC) 
        {op_error = op_slti(mips, mips->n_arg1, mips->n_arg2, mips->inmediate); break;}
        else mips = print_slti(mips, mips->n_arg1, mips->n_arg2, mips->inmediate); break;

    case 33: 
        if(mips->s_arg4 != 0){mips->report = 620; break;}
        if(act == D_EXEC) 
        {op_error = op_sltu(mips, mips->s_arg1, mips->s_arg2, mips->s_arg3); break;}
        else mips = print_sltu(mips, mips->s_arg1, mips->s_arg2, mips->s_arg3); break;

    case 34: 
        if(act == D_EXEC) 
        {op_error = op_sltiu(mips, mips->n_arg1, mips->n_arg2, mips->inmediate); break;}
        else mips = print_sltiu(mips, mips->n_arg1, mips->n_arg2, mips->inmediate); break;

    case 35: 
        if(mips->s_arg1 != 0){mips->report = 620; break;}
        if(act == D_EXEC) 
        {op_error = op_sra(mips, mips->s_arg2, mips->s_arg3, mips->s_arg4); break;}
        else mips = print_sra(mips, mips->s_arg2, mips->s_arg3, mips->s_arg4); break;

    case 36: 
        if(mips->s_arg1 != 0){mips->report = 620; break;}
        if(act == D_EXEC) 
        {op_error = op_srl(mips, mips->s_arg2, mips->s_arg3, mips->s_arg4); break;}
        else mips = print_srl(mips, mips->s_arg2, mips->s_arg3, mips->s_arg4); break;

    case 37: 
        if(mips->s_arg4 != 0){mips->report = 620; break;}
        if(act == D_EXEC)
        {op_error = op_sub(mips, mips->s_arg1, mips->s_arg2, mips->s_arg3); break;}
        else mips = print_sub(mips, mips->s_arg1, mips->s_arg2, mips->s_arg3); break;


    case 38: 
        if(mips->s_arg4 != 0){mips->report = 620; break;}
        if(act == D_EXEC)
        {op_error = op_subu(mips, mips->s_arg1, mips->s_arg2, mips->s_arg3); break;}
        else mips = print_subu(mips, mips->s_arg1, mips->s_arg2, mips->s_arg3); break;


    // case 40: op_error = op_sw(act) break;

    // case 41: op_error = op_syscall(act) break;

    case 41: 
        if(mips->s_arg4 != 0){mips->report = 620; break;}
        if(act == D_EXEC) 
        {op_error = op_xor(mips, mips->s_arg1, mips->s_arg2, mips->s_arg3); break;}
        else mips = print_xor(mips, mips->s_arg1, mips->s_arg2, mips->s_arg3); break;
    }

    if(op_error > 0)
    {
    op_report(op_error);
    }    

    return mips;
}