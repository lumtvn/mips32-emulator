#include "../src/headers.h"
#include "../src/disassembler.h"
#include "../src/lookup.h"
#include "minunit.h"

 int tests_run = 0; 
 int res;
 struct ptype *mips;

static char * test_load_opcodes() 
{
    if(load_opcodes() < 0)
    {
        printf("error, opcodes not installed\n");
        mu_assert("", 0);
    }

    return 0;

}

static char * test_ADD() 
{
    mword n1 = 0x00FA8120;
    mword n2 = 0x01267A60;
    mword n3 = 0x0226DFA0;
    mword n4 = 0x03872AE0;

    mips = getopcode(mips, n1);
    if(mips->operation != NULL)
    mu_assert("error, opcode ADD not loaded or incorrect for n1", !strcmp(mips->operation,"ADD"));
    else
    mu_assert("mips->operation is null for n1 in test_ADD", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n2);
    if(mips->operation != NULL)
    mu_assert("error, opcode ADD not loaded or incorrect for n2", !strcmp(mips->operation,"ADD"));
    else
    mu_assert("mips->operation is null for n2 in test_ADD", 0);
    mips->operation = NULL;   
    
    mips = getopcode(mips, n3);
    if(mips->operation != NULL)
    mu_assert("error, opcode ADD not loaded or incorrect for n3", !strcmp(mips->operation,"ADD"));
    else
    mu_assert("mips->operation is null for n3 in test_ADD", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n4);
    if(mips->operation != NULL)
    mu_assert("error, opcode ADD not loaded or incorrect for n4", !strcmp(mips->operation,"ADD"));
    else
    mu_assert("mips->operation is null for n4 in test_ADD", 0);
    mips->operation = NULL;   

    return 0;

}

static char * test_ADDI() 
{
    mword n1 = 0x20FA819B;
    mword n2 = 0x21267ABD;
    mword n3 = 0x2226DFA3;
    mword n4 = 0x23872AAF;

    mips = getopcode(mips, n1);
    if(mips->operation != NULL)
    mu_assert("error, opcode ADDI not loaded or incorrect for n1", !strcmp(mips->operation,"ADDI"));
    else
    mu_assert("mips->operation is null for n1 in test_ADDI", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n2);
    if(mips->operation != NULL)
    mu_assert("error, opcode ADDI not loaded or incorrect for n2", !strcmp(mips->operation,"ADDI"));
    else
    mu_assert("mips->operation is null for n2 in test_ADDI", 0);
    mips->operation = NULL;   
    
    mips = getopcode(mips, n3);
    if(mips->operation != NULL)
    mu_assert("error, opcode ADDI not loaded or incorrect for n3", !strcmp(mips->operation,"ADDI"));
    else
    mu_assert("mips->operation is null for n3 in test_ADDI", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n4);
    if(mips->operation != NULL)
    mu_assert("error, opcode ADDI not loaded or incorrect for n4", !strcmp(mips->operation,"ADDI"));
    else
    mu_assert("mips->operation is null for n4 in test_ADDI", 0);
    mips->operation = NULL;   

    return 0;

}

static char * test_ADDIU() 
{
    mword n1 = 0x24FA819B;
    mword n2 = 0x25267ABD;
    mword n3 = 0x2626DFA3;
    mword n4 = 0x27872AAF;

    mips = getopcode(mips, n1);
    if(mips->operation != NULL)
    mu_assert("error, opcode ADDIU not loaded or incorrect for n1", !strcmp(mips->operation,"ADDIU"));
    else
    mu_assert("mips->operation is null for n1 in test_ADDIU", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n2);
    if(mips->operation != NULL)
    mu_assert("error, opcode ADDIU not loaded or incorrect for n2", !strcmp(mips->operation,"ADDIU"));
    else
    mu_assert("mips->operation is null for n2 in test_ADDIU", 0);
    mips->operation = NULL;   
    
    mips = getopcode(mips, n3);
    if(mips->operation != NULL)
    mu_assert("error, opcode ADDIU not loaded or incorrect for n3", !strcmp(mips->operation,"ADDIU"));
    else
    mu_assert("mips->operation is null for n3 in test_ADDIU", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n4);
    if(mips->operation != NULL)
    mu_assert("error, opcode ADDIU not loaded or incorrect for n4", !strcmp(mips->operation,"ADDIU"));
    else
    mu_assert("mips->operation is null for n4 in test_ADDIU", 0);
    mips->operation = NULL;   

    return 0;

}

static char * test_ADDU() 
{
    mword n1 = 0x00FA8121;
    mword n2 = 0x01267A21;
    mword n3 = 0x0226DF21;
    mword n4 = 0x03872A21;

    mips = getopcode(mips, n1);
    if(mips->operation != NULL)
    mu_assert("error, opcode ADDU not loaded or incorrect for n1", !strcmp(mips->operation,"ADDU"));
    else
    mu_assert("mips->operation is null for n1 in test_ADDU", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n2);
    if(mips->operation != NULL)
    mu_assert("error, opcode ADDU not loaded or incorrect for n2", !strcmp(mips->operation,"ADDU"));
    else
    mu_assert("mips->operation is null for n2 in test_ADDU", 0);
    mips->operation = NULL;   
    
    mips = getopcode(mips, n3);
    if(mips->operation != NULL)
    mu_assert("error, opcode ADDU not loaded or incorrect for n3", !strcmp(mips->operation,"ADDU"));
    else
    mu_assert("mips->operation is null for n3 in test_ADDU", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n4);
    if(mips->operation != NULL)
    mu_assert("error, opcode ADDU not loaded or incorrect for n4", !strcmp(mips->operation,"ADDU"));
    else
    mu_assert("mips->operation is null for n4 in test_ADDU", 0);
    mips->operation = NULL;   

    return 0;

}

static char * test_AND() 
{
    mword n1 = 0x00FA8124;
    mword n2 = 0x01267A24;
    mword n3 = 0x0226DF24;
    mword n4 = 0x03872A24;

    mips = getopcode(mips, n1);
    if(mips->operation != NULL)
    mu_assert("error, opcode AND not loaded or incorrect for n1", !strcmp(mips->operation,"AND"));
    else
    mu_assert("mips->operation is null for n1 in test_AND", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n2);
    if(mips->operation != NULL)
    mu_assert("error, opcode AND not loaded or incorrect for n2", !strcmp(mips->operation,"AND"));
    else
    mu_assert("mips->operation is null for n2 in test_AND", 0);
    mips->operation = NULL;   
    
    mips = getopcode(mips, n3);
    if(mips->operation != NULL)
    mu_assert("error, opcode AND not loaded or incorrect for n3", !strcmp(mips->operation,"AND"));
    else
    mu_assert("mips->operation is null for n3 in test_AND", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n4);
    if(mips->operation != NULL)
    mu_assert("error, opcode AND not loaded or incorrect for n4", !strcmp(mips->operation,"AND"));
    else
    mu_assert("mips->operation is null for n4 in test_AND", 0);
    mips->operation = NULL;   

    return 0;

}

static char * test_ANDI() 
{
    mword n1 = 0x30FA819B;
    mword n2 = 0x31267ABD;
    mword n3 = 0x3226DFA3;
    mword n4 = 0x33872AAF;

    mips = getopcode(mips, n1);
    if(mips->operation != NULL)
    mu_assert("error, opcode ANDI not loaded or incorrect for n1", !strcmp(mips->operation,"ANDI"));
    else
    mu_assert("mips->operation is null for n1 in test_ANDI", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n2);
    if(mips->operation != NULL)
    mu_assert("error, opcode ANDI not loaded or incorrect for n2", !strcmp(mips->operation,"ANDI"));
    else
    mu_assert("mips->operation is null for n2 in test_ANDI", 0);
    mips->operation = NULL;   
    
    mips = getopcode(mips, n3);
    if(mips->operation != NULL)
    mu_assert("error, opcode ANDI not loaded or incorrect for n3", !strcmp(mips->operation,"ANDI"));
    else
    mu_assert("mips->operation is null for n3 in test_ANDI", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n4);
    if(mips->operation != NULL)
    mu_assert("error, opcode ANDI not loaded or incorrect for n4", !strcmp(mips->operation,"ANDI"));
    else
    mu_assert("mips->operation is null for n4 in test_ANDI", 0);
    mips->operation = NULL;   

    return 0;

}

static char * test_BEQ() 
{
    mword n1 = 0x10FA819B;
    mword n2 = 0x11A67ABD;
    mword n3 = 0x1226DFA3;
    mword n4 = 0x13872AAF;

    mips = getopcode(mips, n1);
    if(mips->operation != NULL)
    mu_assert("error, opcode BEQ not loaded or incorrect for n1", !strcmp(mips->operation,"BEQ"));
    else
    mu_assert("mips->operation is null for n1 in test_BEQ", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n2);
    if(mips->operation != NULL)
    mu_assert("error, opcode BEQ not loaded or incorrect for n2", !strcmp(mips->operation,"BEQ"));
    else
    mu_assert("mips->operation is null for n2 in test_BEQ", 0);
    mips->operation = NULL;   
    
    mips = getopcode(mips, n3);
    if(mips->operation != NULL)
    mu_assert("error, opcode BEQ not loaded or incorrect for n3", !strcmp(mips->operation,"BEQ"));
    else
    mu_assert("mips->operation is null for n3 in test_BEQ", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n4);
    if(mips->operation != NULL)
    mu_assert("error, opcode BEQ not loaded or incorrect for n4", !strcmp(mips->operation,"BEQ"));
    else
    mu_assert("mips->operation is null for n4 in test_BEQ", 0);
    mips->operation = NULL;   

    return 0;

}

static char * test_BGEZ() 
{
    mword n1 = 0x04218124;
    mword n2 = 0x05417A24;
    mword n3 = 0x0681DF24;
    mword n4 = 0x07612A24;

    mips = getopcode(mips, n1);
    if(mips->operation != NULL)
    mu_assert("error, opcode BGEZ not loaded or incorrect for n1", !strcmp(mips->operation,"BGEZ"));
    else
    mu_assert("mips->operation is null for n1 in test_BGEZ", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n2);
    if(mips->operation != NULL)
    mu_assert("error, opcode BGEZ not loaded or incorrect for n2", !strcmp(mips->operation,"BGEZ"));
    else
    mu_assert("mips->operation is null for n2 in test_BGEZ", 0);
    mips->operation = NULL;   
    
    mips = getopcode(mips, n3);
    if(mips->operation != NULL)
    mu_assert("error, opcode BGEZ not loaded or incorrect for n3", !strcmp(mips->operation,"BGEZ"));
    else
    mu_assert("mips->operation is null for n3 in test_BGEZ", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n4);
    if(mips->operation != NULL)
    mu_assert("error, opcode BGEZ not loaded or incorrect for n4", !strcmp(mips->operation,"BGEZ"));
    else
    mu_assert("mips->operation is null for n4 in test_BGEZ", 0);
    mips->operation = NULL;   

    return 0;

}

static char * test_BGTZ() 
{
    mword n1 = 0x1CFA819B;
    mword n2 = 0x1D267ABD;
    mword n3 = 0x1E26DFA3;
    mword n4 = 0x1F3872AF;

    mips = getopcode(mips, n1);
    if(mips->operation != NULL)
    mu_assert("error, opcode BGTZ not loaded or incorrect for n1", !strcmp(mips->operation,"BGTZ"));
    else
    mu_assert("mips->operation is null for n1 in test_BGTZ", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n2);
    if(mips->operation != NULL)
    mu_assert("error, opcode BGTZ not loaded or incorrect for n2", !strcmp(mips->operation,"BGTZ"));
    else
    mu_assert("mips->operation is null for n2 in test_BGTZ", 0);
    mips->operation = NULL;   
    
    mips = getopcode(mips, n3);
    if(mips->operation != NULL)
    mu_assert("error, opcode BGTZ not loaded or incorrect for n3", !strcmp(mips->operation,"BGTZ"));
    else
    mu_assert("mips->operation is null for n3 in test_BGTZ", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n4);
    if(mips->operation != NULL)
    mu_assert("error, opcode BGTZ not loaded or incorrect for n4", !strcmp(mips->operation,"BGTZ"));
    else
    mu_assert("mips->operation is null for n4 in test_BGTZ", 0);
    mips->operation = NULL;   

    return 0;

}

static char * test_BLEZ() 
{
    mword n1 = 0x18FA819B;
    mword n2 = 0x19267ABD;
    mword n3 = 0x1A26DFA3;
    mword n4 = 0x1B872AAF;

    mips = getopcode(mips, n1);
    if(mips->operation != NULL)
    mu_assert("error, opcode BLEZ not loaded or incorrect for n1", !strcmp(mips->operation,"BLEZ"));
    else
    mu_assert("mips->operation is null for n1 in test_BLEZ", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n2);
    if(mips->operation != NULL)
    mu_assert("error, opcode BLEZ not loaded or incorrect for n2", !strcmp(mips->operation,"BLEZ"));
    else
    mu_assert("mips->operation is null for n2 in test_BLEZ", 0);
    mips->operation = NULL;   
    
    mips = getopcode(mips, n3);
    if(mips->operation != NULL)
    mu_assert("error, opcode BLEZ not loaded or incorrect for n3", !strcmp(mips->operation,"BLEZ"));
    else
    mu_assert("mips->operation is null for n3 in test_BLEZ", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n4);
    if(mips->operation != NULL)
    mu_assert("error, opcode BLEZ not loaded or incorrect for n4", !strcmp(mips->operation,"BLEZ"));
    else
    mu_assert("mips->operation is null for n4 in test_BLEZ", 0);
    mips->operation = NULL;   

    return 0;

}

static char * test_BLTZ() 
{
    mword n1 = 0x04208114;
    mword n2 = 0x05407A6D;
    mword n3 = 0x0680DF34;
    mword n4 = 0x07602AF1;

    mips = getopcode(mips, n1);
    if(mips->operation != NULL)
    mu_assert("error, opcode BLTZ not loaded or incorrect for n1", !strcmp(mips->operation,"BLTZ"));
    else
    mu_assert("mips->operation is null for n1 in test_BLTZ", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n2);
    if(mips->operation != NULL)
    mu_assert("error, opcode BLTZ not loaded or incorrect for n2", !strcmp(mips->operation,"BLTZ"));
    else
    mu_assert("mips->operation is null for n2 in test_BLTZ", 0);
    mips->operation = NULL;   
    
    mips = getopcode(mips, n3);
    if(mips->operation != NULL)
    mu_assert("error, opcode BLTZ not loaded or incorrect for n3", !strcmp(mips->operation,"BLTZ"));
    else
    mu_assert("mips->operation is null for n3 in test_BLTZ", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n4);
    if(mips->operation != NULL)
    mu_assert("error, opcode BLTZ not loaded or incorrect for n4", !strcmp(mips->operation,"BLTZ"));
    else
    mu_assert("mips->operation is null for n4 in test_BLTZ", 0);
    mips->operation = NULL;   

    return 0;

}

static char * test_BNE() 
{
    mword n1 = 0x14FA819B;
    mword n2 = 0x15267ABD;
    mword n3 = 0x1626DFA3;
    mword n4 = 0x17872AAF;

    mips = getopcode(mips, n1);
    if(mips->operation != NULL)
    mu_assert("error, opcode BNE not loaded or incorrect for n1", !strcmp(mips->operation,"BNE"));
    else
    mu_assert("mips->operation is null for n1 in test_BNE", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n2);
    if(mips->operation != NULL)
    mu_assert("error, opcode BNE not loaded or incorrect for n2", !strcmp(mips->operation,"BNE"));
    else
    mu_assert("mips->operation is null for n2 in test_BNE", 0);
    mips->operation = NULL;   
    
    mips = getopcode(mips, n3);
    if(mips->operation != NULL)
    mu_assert("error, opcode BNE not loaded or incorrect for n3", !strcmp(mips->operation,"BNE"));
    else
    mu_assert("mips->operation is null for n3 in test_BNE", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n4);
    if(mips->operation != NULL)
    mu_assert("error, opcode BNE not loaded or incorrect for n4", !strcmp(mips->operation,"BNE"));
    else
    mu_assert("mips->operation is null for n4 in test_BNE", 0);
    mips->operation = NULL;   

    return 0;

}

static char * test_BREAK() 
{
    mword n1 = 0x00FA810D;
    mword n2 = 0x01267A4D;
    mword n3 = 0x0226DF8D;
    mword n4 = 0x03872ACD;

    mips = getopcode(mips, n1);
    if(mips->operation != NULL)
    mu_assert("error, opcode BREAK not loaded or incorrect for n1", !strcmp(mips->operation,"BREAK"));
    else
    mu_assert("mips->operation is null for n1 in test_BREAK", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n2);
    if(mips->operation != NULL)
    mu_assert("error, opcode BREAK not loaded or incorrect for n2", !strcmp(mips->operation,"BREAK"));
    else
    mu_assert("mips->operation is null for n2 in test_BREAK", 0);
    mips->operation = NULL;   
    
    mips = getopcode(mips, n3);
    if(mips->operation != NULL)
    mu_assert("error, opcode BREAK not loaded or incorrect for n3", !strcmp(mips->operation,"BREAK"));
    else
    mu_assert("mips->operation is null for n3 in test_BREAK", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n4);
    if(mips->operation != NULL)
    mu_assert("error, opcode BREAK not loaded or incorrect for n4", !strcmp(mips->operation,"BREAK"));
    else
    mu_assert("mips->operation is null for n4 in test_BREAK", 0);
    mips->operation = NULL;   

    return 0;

}

static char * test_DIV() 
{
    mword n1 = 0x00FA811A;
    mword n2 = 0x01267A1A;
    mword n3 = 0x0226DF1A;
    mword n4 = 0x03872A1A;

    mips = getopcode(mips, n1);
    if(mips->operation != NULL)
    mu_assert("error, opcode DIV not loaded or incorrect for n1", !strcmp(mips->operation,"DIV"));
    else
    mu_assert("mips->operation is null for n1 in test_DIV", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n2);
    if(mips->operation != NULL)
    mu_assert("error, opcode DIV not loaded or incorrect for n2", !strcmp(mips->operation,"DIV"));
    else
    mu_assert("mips->operation is null for n2 in test_DIV", 0);
    mips->operation = NULL;   
    
    mips = getopcode(mips, n3);
    if(mips->operation != NULL)
    mu_assert("error, opcode DIV not loaded or incorrect for n3", !strcmp(mips->operation,"DIV"));
    else
    mu_assert("mips->operation is null for n3 in test_DIV", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n4);
    if(mips->operation != NULL)
    mu_assert("error, opcode DIV not loaded or incorrect for n4", !strcmp(mips->operation,"DIV"));
    else
    mu_assert("mips->operation is null for n4 in test_DIV", 0);
    mips->operation = NULL;   

    return 0;

}

static char * test_J() 
{
    mword n1 = 0x08FA819B;
    mword n2 = 0x09267ABD;
    mword n3 = 0x0A26DFA3;
    mword n4 = 0x0B872AAF;

    mips = getopcode(mips, n1);
    if(mips->operation != NULL)
    mu_assert("error, opcode J not loaded or incorrect for n1", !strcmp(mips->operation,"J"));
    else
    mu_assert("mips->operation is null for n1 in test_J", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n2);
    if(mips->operation != NULL)
    mu_assert("error, opcode J not loaded or incorrect for n2", !strcmp(mips->operation,"J"));
    else
    mu_assert("mips->operation is null for n2 in test_J", 0);
    mips->operation = NULL;   
    
    mips = getopcode(mips, n3);
    if(mips->operation != NULL)
    mu_assert("error, opcode J not loaded or incorrect for n3", !strcmp(mips->operation,"J"));
    else
    mu_assert("mips->operation is null for n3 in test_J", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n4);
    if(mips->operation != NULL)
    mu_assert("error, opcode J not loaded or incorrect for n4", !strcmp(mips->operation,"J"));
    else
    mu_assert("mips->operation is null for n4 in test_J", 0);
    mips->operation = NULL;   

    return 0;

}

static char * test_JAL() 
{
    mword n1 = 0x0CFA819B;
    mword n2 = 0x0D267ABD;
    mword n3 = 0x0E26DFA3;
    mword n4 = 0x0F872AAF;

    mips = getopcode(mips, n1);
    if(mips->operation != NULL)
    mu_assert("error, opcode JAL not loaded or incorrect for n1", !strcmp(mips->operation,"JAL"));
    else
    mu_assert("mips->operation is null for n1 in test_JAL", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n2);
    if(mips->operation != NULL)
    mu_assert("error, opcode JAL not loaded or incorrect for n2", !strcmp(mips->operation,"JAL"));
    else
    mu_assert("mips->operation is null for n2 in test_JAL", 0);
    mips->operation = NULL;   
    
    mips = getopcode(mips, n3);
    if(mips->operation != NULL)
    mu_assert("error, opcode JAL not loaded or incorrect for n3", !strcmp(mips->operation,"JAL"));
    else
    mu_assert("mips->operation is null for n3 in test_JAL", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n4);
    if(mips->operation != NULL)
    mu_assert("error, opcode JAL not loaded or incorrect for n4", !strcmp(mips->operation,"JAL"));
    else
    mu_assert("mips->operation is null for n4 in test_JAL", 0);
    mips->operation = NULL;   

    return 0;

}

static char * test_JALR() 
{
    mword n1 = 0x00FA8109;
    mword n2 = 0x01267A49;
    mword n3 = 0x0226DF89;
    mword n4 = 0x03872AC9;

    mips = getopcode(mips, n1);
    if(mips->operation != NULL)
    mu_assert("error, opcode JALR not loaded or incorrect for n1", !strcmp(mips->operation,"JALR"));
    else
    mu_assert("mips->operation is null for n1 in test_JALR", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n2);
    if(mips->operation != NULL)
    mu_assert("error, opcode JALR not loaded or incorrect for n2", !strcmp(mips->operation,"JALR"));
    else
    mu_assert("mips->operation is null for n2 in test_JALR", 0);
    mips->operation = NULL;   
    
    mips = getopcode(mips, n3);
    if(mips->operation != NULL)
    mu_assert("error, opcode JALR not loaded or incorrect for n3", !strcmp(mips->operation,"JALR"));
    else
    mu_assert("mips->operation is null for n3 in test_JALR", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n4);
    if(mips->operation != NULL)
    mu_assert("error, opcode JALR not loaded or incorrect for n4", !strcmp(mips->operation,"JALR"));
    else
    mu_assert("mips->operation is null for n4 in test_JALR", 0);
    mips->operation = NULL;   

    return 0;

}

static char * test_JR() 
{
    mword n1 = 0x00FA8108;
    mword n2 = 0x01267A48;
    mword n3 = 0x0226DF88;
    mword n4 = 0x03872AC8;

    mips = getopcode(mips, n1);
    if(mips->operation != NULL)
    mu_assert("error, opcode JR not loaded or incorrect for n1", !strcmp(mips->operation,"JR"));
    else
    mu_assert("mips->operation is null for n1 in test_JR", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n2);
    if(mips->operation != NULL)
    mu_assert("error, opcode JR not loaded or incorrect for n2", !strcmp(mips->operation,"JR"));
    else
    mu_assert("mips->operation is null for n2 in test_JR", 0);
    mips->operation = NULL;   
    
    mips = getopcode(mips, n3);
    if(mips->operation != NULL)
    mu_assert("error, opcode JR not loaded or incorrect for n3", !strcmp(mips->operation,"JR"));
    else
    mu_assert("mips->operation is null for n3 in test_JR", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n4);
    if(mips->operation != NULL)
    mu_assert("error, opcode JR not loaded or incorrect for n4", !strcmp(mips->operation,"JR"));
    else
    mu_assert("mips->operation is null for n4 in test_JR", 0);
    mips->operation = NULL;   

    return 0;

}

static char * test_LB() 
{
    mword n1 = 0x80FA819B;
    mword n2 = 0x81267ABD;
    mword n3 = 0x8226DFA3;
    mword n4 = 0x83872AAF;

    mips = getopcode(mips, n1);
    if(mips->operation != NULL)
    mu_assert("error, opcode LB not loaded or incorrect for n1", !strcmp(mips->operation,"LB"));
    else
    mu_assert("mips->operation is null for n1 in test_LB", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n2);
    if(mips->operation != NULL)
    mu_assert("error, opcode LB not loaded or incorrect for n2", !strcmp(mips->operation,"LB"));
    else
    mu_assert("mips->operation is null for n2 in test_LB", 0);
    mips->operation = NULL;   
    
    mips = getopcode(mips, n3);
    if(mips->operation != NULL)
    mu_assert("error, opcode LB not loaded or incorrect for n3", !strcmp(mips->operation,"LB"));
    else
    mu_assert("mips->operation is null for n3 in test_LB", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n4);
    if(mips->operation != NULL)
    mu_assert("error, opcode LB not loaded or incorrect for n4", !strcmp(mips->operation,"LB"));
    else
    mu_assert("mips->operation is null for n4 in test_LB", 0);
    mips->operation = NULL;   

    return 0;

}

static char * test_LBU() 
{
    mword n1 = 0x90FA819B;
    mword n2 = 0x91267ABD;
    mword n3 = 0x9226DFA3;
    mword n4 = 0x93872AAF;

    mips = getopcode(mips, n1);
    if(mips->operation != NULL)
    mu_assert("error, opcode LBU not loaded or incorrect for n1", !strcmp(mips->operation,"LBU"));
    else
    mu_assert("mips->operation is null for n1 in test_LBU", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n2);
    if(mips->operation != NULL)
    mu_assert("error, opcode LBU not loaded or incorrect for n2", !strcmp(mips->operation,"LBU"));
    else
    mu_assert("mips->operation is null for n2 in test_LBU", 0);
    mips->operation = NULL;   
    
    mips = getopcode(mips, n3);
    if(mips->operation != NULL)
    mu_assert("error, opcode LBU not loaded or incorrect for n3", !strcmp(mips->operation,"LBU"));
    else
    mu_assert("mips->operation is null for n3 in test_LBU", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n4);
    if(mips->operation != NULL)
    mu_assert("error, opcode LBU not loaded or incorrect for n4", !strcmp(mips->operation,"LBU"));
    else
    mu_assert("mips->operation is null for n4 in test_LBU", 0);
    mips->operation = NULL;   

    return 0;

}

static char * test_LUI() 
{
    mword n1 = 0x3CFA819B;
    mword n2 = 0x3D267ABD;
    mword n3 = 0x3E26DFA3;
    mword n4 = 0x3F872AAF;

    mips = getopcode(mips, n1);
    if(mips->operation != NULL)
    mu_assert("error, opcode LUI not loaded or incorrect for n1", !strcmp(mips->operation,"LUI"));
    else
    mu_assert("mips->operation is null for n1 in test_LUI", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n2);
    if(mips->operation != NULL)
    mu_assert("error, opcode LUI not loaded or incorrect for n2", !strcmp(mips->operation,"LUI"));
    else
    mu_assert("mips->operation is null for n2 in test_LUI", 0);
    mips->operation = NULL;   
    
    mips = getopcode(mips, n3);
    if(mips->operation != NULL)
    mu_assert("error, opcode LUI not loaded or incorrect for n3", !strcmp(mips->operation,"LUI"));
    else
    mu_assert("mips->operation is null for n3 in test_LUI", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n4);
    if(mips->operation != NULL)
    mu_assert("error, opcode LUI not loaded or incorrect for n4", !strcmp(mips->operation,"LUI"));
    else
    mu_assert("mips->operation is null for n4 in test_LUI", 0);
    mips->operation = NULL;   

    return 0;

}

static char * test_LW() 
{
    mword n1 = 0x8CFA819B;
    mword n2 = 0x8D267ABD;
    mword n3 = 0x8E26DFA3;
    mword n4 = 0x8F872AAF;

    mips = getopcode(mips, n1);
    if(mips->operation != NULL)
    mu_assert("error, opcode LW not loaded or incorrect for n1", !strcmp(mips->operation,"LW"));
    else
    mu_assert("mips->operation is null for n1 in test_LW", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n2);
    if(mips->operation != NULL)
    mu_assert("error, opcode LW not loaded or incorrect for n2", !strcmp(mips->operation,"LW"));
    else
    mu_assert("mips->operation is null for n2 in test_LW", 0);
    mips->operation = NULL;   
    
    mips = getopcode(mips, n3);
    if(mips->operation != NULL)
    mu_assert("error, opcode LW not loaded or incorrect for n3", !strcmp(mips->operation,"LW"));
    else
    mu_assert("mips->operation is null for n3 in test_LW", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n4);
    if(mips->operation != NULL)
    mu_assert("error, opcode LW not loaded or incorrect for n4", !strcmp(mips->operation,"LW"));
    else
    mu_assert("mips->operation is null for n4 in test_LW", 0);
    mips->operation = NULL;   

    return 0;

}

static char * test_MFHI() 
{
    mword n1 = 0x00FA8110;
    mword n2 = 0x01267A10;
    mword n3 = 0x0226DF10;
    mword n4 = 0x03872A10;

    mips = getopcode(mips, n1);
    if(mips->operation != NULL)
    mu_assert("error, opcode MFHI not loaded or incorrect for n1", !strcmp(mips->operation,"MFHI"));
    else
    mu_assert("mips->operation is null for n1 in test_MFHI", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n2);
    if(mips->operation != NULL)
    mu_assert("error, opcode MFHI not loaded or incorrect for n2", !strcmp(mips->operation,"MFHI"));
    else
    mu_assert("mips->operation is null for n2 in test_MFHI", 0);
    mips->operation = NULL;   
    
    mips = getopcode(mips, n3);
    if(mips->operation != NULL)
    mu_assert("error, opcode MFHI not loaded or incorrect for n3", !strcmp(mips->operation,"MFHI"));
    else
    mu_assert("mips->operation is null for n3 in test_MFHI", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n4);
    if(mips->operation != NULL)
    mu_assert("error, opcode MFHI not loaded or incorrect for n4", !strcmp(mips->operation,"MFHI"));
    else
    mu_assert("mips->operation is null for n4 in test_MFHI", 0);
    mips->operation = NULL;   

    return 0;

}

static char * test_MFLO() 
{
    mword n1 = 0x00FA8112;
    mword n2 = 0x00267A12;
    mword n3 = 0x0026DF12;
    mword n4 = 0x00872A12;

    mips = getopcode(mips, n1);
    if(mips->operation != NULL)
    mu_assert("error, opcode MFLO not loaded or incorrect for n1", !strcmp(mips->operation,"MFLO"));
    else
    mu_assert("mips->operation is null for n1 in test_MFLO", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n2);
    if(mips->operation != NULL)
    mu_assert("error, opcode MFLO not loaded or incorrect for n2", !strcmp(mips->operation,"MFLO"));
    else
    mu_assert("mips->operation is null for n2 in test_MFLO", 0);
    mips->operation = NULL;   
    
    mips = getopcode(mips, n3);
    if(mips->operation != NULL)
    mu_assert("error, opcode MFLO not loaded or incorrect for n3", !strcmp(mips->operation,"MFLO"));
    else
    mu_assert("mips->operation is null for n3 in test_MFLO", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n4);
    if(mips->operation != NULL)
    mu_assert("error, opcode MFLO not loaded or incorrect for n4", !strcmp(mips->operation,"MFLO"));
    else
    mu_assert("mips->operation is null for n4 in test_MFLO", 0);
    mips->operation = NULL;   

    return 0;

}

static char * test_MULT() 
{
    mword n1 = 0x00FA8118;
    mword n2 = 0x01267A18;
    mword n3 = 0x0226DF18;
    mword n4 = 0x03872A18;

    mips = getopcode(mips, n1);
    if(mips->operation != NULL)
    mu_assert("error, opcode MULT not loaded or incorrect for n1", !strcmp(mips->operation,"MULT"));
    else
    mu_assert("mips->operation is null for n1 in test_MULT", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n2);
    if(mips->operation != NULL)
    mu_assert("error, opcode MULT not loaded or incorrect for n2", !strcmp(mips->operation,"MULT"));
    else
    mu_assert("mips->operation is null for n2 in test_MULT", 0);
    mips->operation = NULL;   
    
    mips = getopcode(mips, n3);
    if(mips->operation != NULL)
    mu_assert("error, opcode MULT not loaded or incorrect for n3", !strcmp(mips->operation,"MULT"));
    else
    mu_assert("mips->operation is null for n3 in test_MULT", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n4);
    if(mips->operation != NULL)
    mu_assert("error, opcode MULT not loaded or incorrect for n4", !strcmp(mips->operation,"MULT"));
    else
    mu_assert("mips->operation is null for n4 in test_MULT", 0);
    mips->operation = NULL;   

    return 0;

}

static char * test_NOP() 
{
    mword n1 = 0X00000000;

    mips = getopcode(mips, n1);
    if(mips->operation != NULL)
    mu_assert("error, opcode NOP not loaded or incorrect for n1", !strcmp(mips->operation,"NOP"));
    else
    mu_assert("mips->operation is null for n1 in test_NOP", 0);
    mips->operation = NULL;   

    return 0;

}

static char * test_OR() 
{
    mword n1 = 0x00FA8125;
    mword n2 = 0x01267A25;
    mword n3 = 0x0226DF25;
    mword n4 = 0x03872A25;

    mips = getopcode(mips, n1);
    if(mips->operation != NULL)
    mu_assert("error, opcode OR not loaded or incorrect for n1", !strcmp(mips->operation,"OR"));
    else
    mu_assert("mips->operation is null for n1 in test_OR", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n2);
    if(mips->operation != NULL)
    mu_assert("error, opcode OR not loaded or incorrect for n2", !strcmp(mips->operation,"OR"));
    else
    mu_assert("mips->operation is null for n2 in test_OR", 0);
    mips->operation = NULL;   
    
    mips = getopcode(mips, n3);
    if(mips->operation != NULL)
    mu_assert("error, opcode OR not loaded or incorrect for n3", !strcmp(mips->operation,"OR"));
    else
    mu_assert("mips->operation is null for n3 in test_OR", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n4);
    if(mips->operation != NULL)
    mu_assert("error, opcode OR not loaded or incorrect for n4", !strcmp(mips->operation,"OR"));
    else
    mu_assert("mips->operation is null for n4 in test_OR", 0);
    mips->operation = NULL;   

    return 0;

}

static char * test_ORI() 
{
    mword n1 = 0x34FA819B;
    mword n2 = 0x35267ABD;
    mword n3 = 0x3626DFA3;
    mword n4 = 0x37872AAF;

    mips = getopcode(mips, n1);
    if(mips->operation != NULL)
    mu_assert("error, opcode ORI not loaded or incorrect for n1", !strcmp(mips->operation,"ORI"));
    else
    mu_assert("mips->operation is null for n1 in test_ORI", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n2);
    if(mips->operation != NULL)
    mu_assert("error, opcode ORI not loaded or incorrect for n2", !strcmp(mips->operation,"ORI"));
    else
    mu_assert("mips->operation is null for n2 in test_ORI", 0);
    mips->operation = NULL;   
    
    mips = getopcode(mips, n3);
    if(mips->operation != NULL)
    mu_assert("error, opcode ORI not loaded or incorrect for n3", !strcmp(mips->operation,"ORI"));
    else
    mu_assert("mips->operation is null for n3 in test_ORI", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n4);
    if(mips->operation != NULL)
    mu_assert("error, opcode ORI not loaded or incorrect for n4", !strcmp(mips->operation,"ORI"));
    else
    mu_assert("mips->operation is null for n4 in test_ORI", 0);
    mips->operation = NULL;   

    return 0;

}

static char * test_SB() 
{
    mword n1 = 0xA0FA819B;
    mword n2 = 0xA1267ABD;
    mword n3 = 0xA226DFA3;
    mword n4 = 0xA3872AAF;

    mips = getopcode(mips, n1);
    if(mips->operation != NULL)
    mu_assert("error, opcode SB not loaded or incorrect for n1", !strcmp(mips->operation,"SB"));
    else
    mu_assert("mips->operation is null for n1 in test_SB", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n2);
    if(mips->operation != NULL)
    mu_assert("error, opcode SB not loaded or incorrect for n2", !strcmp(mips->operation,"SB"));
    else
    mu_assert("mips->operation is null for n2 in test_SB", 0);
    mips->operation = NULL;   
    
    mips = getopcode(mips, n3);
    if(mips->operation != NULL)
    mu_assert("error, opcode SB not loaded or incorrect for n3", !strcmp(mips->operation,"SB"));
    else
    mu_assert("mips->operation is null for n3 in test_SB", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n4);
    if(mips->operation != NULL)
    mu_assert("error, opcode SB not loaded or incorrect for n4", !strcmp(mips->operation,"SB"));
    else
    mu_assert("mips->operation is null for n4 in test_SB", 0);
    mips->operation = NULL;   

    return 0;

}

static char * test_SEB() 
{
    mword n1 = 0x7CFA8404;
    mword n2 = 0x7D267C1D;
    mword n3 = 0x7E26D413;
    mword n4 = 0x7F872C0F;

    mips = getopcode(mips, n1);
    if(mips->operation != NULL)
    mu_assert("error, opcode SEB not loaded or incorrect for n1", !strcmp(mips->operation,"SEB"));
    else
    mu_assert("mips->operation is null for n1 in test_SEB", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n2);
    if(mips->operation != NULL)
    mu_assert("error, opcode SEB not loaded or incorrect for n2", !strcmp(mips->operation,"SEB"));
    else
    mu_assert("mips->operation is null for n2 in test_SEB", 0);
    mips->operation = NULL;   
    
    mips = getopcode(mips, n3);
    if(mips->operation != NULL)
    mu_assert("error, opcode SEB not loaded or incorrect for n3", !strcmp(mips->operation,"SEB"));
    else
    mu_assert("mips->operation is null for n3 in test_SEB", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n4);
    if(mips->operation != NULL)
    mu_assert("error, opcode SEB not loaded or incorrect for n4", !strcmp(mips->operation,"SEB"));
    else
    mu_assert("mips->operation is null for n4 in test_SEB", 0);
    mips->operation = NULL;   

    return 0;

}

static char * test_SLL() 
{
    mword n1 = 0x00FA8100;
    mword n2 = 0x00267A40;
    mword n3 = 0x0026DF80;
    mword n4 = 0x00872AC0;

    mips = getopcode(mips, n1);
    if(mips->operation != NULL)
    mu_assert("error, opcode SLL not loaded or incorrect for n1", !strcmp(mips->operation,"SLL"));
    else
    mu_assert("mips->operation is null for n1 in test_SLL", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n2);
    if(mips->operation != NULL)
    mu_assert("error, opcode SLL not loaded or incorrect for n2", !strcmp(mips->operation,"SLL"));
    else
    mu_assert("mips->operation is null for n2 in test_SLL", 0);
    mips->operation = NULL;   
    
    mips = getopcode(mips, n3);
    if(mips->operation != NULL)
    mu_assert("error, opcode SLL not loaded or incorrect for n3", !strcmp(mips->operation,"SLL"));
    else
    mu_assert("mips->operation is null for n3 in test_SLL", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n4);
    if(mips->operation != NULL)
    mu_assert("error, opcode SLL not loaded or incorrect for n4", !strcmp(mips->operation,"SLL"));
    else
    mu_assert("mips->operation is null for n4 in test_SLL", 0);
    mips->operation = NULL;   

    return 0;

}

static char * test_SLT() 
{
    mword n1 = 0x00FA812A;
    mword n2 = 0x01267A2A;
    mword n3 = 0x0226DF2A;
    mword n4 = 0x03872A2A;

    mips = getopcode(mips, n1);
    if(mips->operation != NULL)
    mu_assert("error, opcode SLT not loaded or incorrect for n1", !strcmp(mips->operation,"SLT"));
    else
    mu_assert("mips->operation is null for n1 in test_SLT", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n2);
    if(mips->operation != NULL)
    mu_assert("error, opcode SLT not loaded or incorrect for n2", !strcmp(mips->operation,"SLT"));
    else
    mu_assert("mips->operation is null for n2 in test_SLT", 0);
    mips->operation = NULL;   
    
    mips = getopcode(mips, n3);
    if(mips->operation != NULL)
    mu_assert("error, opcode SLT not loaded or incorrect for n3", !strcmp(mips->operation,"SLT"));
    else
    mu_assert("mips->operation is null for n3 in test_SLT", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n4);
    if(mips->operation != NULL)
    mu_assert("error, opcode SLT not loaded or incorrect for n4", !strcmp(mips->operation,"SLT"));
    else
    mu_assert("mips->operation is null for n4 in test_SLT", 0);
    mips->operation = NULL;   

    return 0;

}

static char * test_SLTI() 
{
    mword n1 = 0x28FA819B;
    mword n2 = 0x29267ABD;
    mword n3 = 0x2A26DFA3;
    mword n4 = 0x2B872AAF;

    mips = getopcode(mips, n1);
    if(mips->operation != NULL)
    mu_assert("error, opcode SLTI not loaded or incorrect for n1", !strcmp(mips->operation,"SLTI"));
    else
    mu_assert("mips->operation is null for n1 in test_SLTI", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n2);
    if(mips->operation != NULL)
    mu_assert("error, opcode SLTI not loaded or incorrect for n2", !strcmp(mips->operation,"SLTI"));
    else
    mu_assert("mips->operation is null for n2 in test_SLTI", 0);
    mips->operation = NULL;   
    
    mips = getopcode(mips, n3);
    if(mips->operation != NULL)
    mu_assert("error, opcode SLTI not loaded or incorrect for n3", !strcmp(mips->operation,"SLTI"));
    else
    mu_assert("mips->operation is null for n3 in test_SLTI", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n4);
    if(mips->operation != NULL)
    mu_assert("error, opcode SLTI not loaded or incorrect for n4", !strcmp(mips->operation,"SLTI"));
    else
    mu_assert("mips->operation is null for n4 in test_SLTI", 0);
    mips->operation = NULL;   

    return 0;

}

static char * test_SLTIU() 
{
    mword n1 = 0x2CFA819B;
    mword n2 = 0x2D267ABD;
    mword n3 = 0x2E26DFA3;
    mword n4 = 0x2F872AAF;

    mips = getopcode(mips, n1);
    if(mips->operation != NULL)
    mu_assert("error, opcode SLTIU not loaded or incorrect for n1", !strcmp(mips->operation,"SLTIU"));
    else
    mu_assert("mips->operation is null for n1 in test_SLTIU", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n2);
    if(mips->operation != NULL)
    mu_assert("error, opcode SLTIU not loaded or incorrect for n2", !strcmp(mips->operation,"SLTIU"));
    else
    mu_assert("mips->operation is null for n2 in test_SLTIU", 0);
    mips->operation = NULL;   
    
    mips = getopcode(mips, n3);
    if(mips->operation != NULL)
    mu_assert("error, opcode SLTIU not loaded or incorrect for n3", !strcmp(mips->operation,"SLTIU"));
    else
    mu_assert("mips->operation is null for n3 in test_SLTIU", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n4);
    if(mips->operation != NULL)
    mu_assert("error, opcode SLTIU not loaded or incorrect for n4", !strcmp(mips->operation,"SLTIU"));
    else
    mu_assert("mips->operation is null for n4 in test_SLTIU", 0);
    mips->operation = NULL;   

    return 0;

}

static char * test_SLTU() 
{
    mword n1 = 0x00FA812B;
    mword n2 = 0x01267A2B;
    mword n3 = 0x0226DF2B;
    mword n4 = 0x03872A2B;

    mips = getopcode(mips, n1);
    if(mips->operation != NULL)
    mu_assert("error, opcode SLTU not loaded or incorrect for n1", !strcmp(mips->operation,"SLTU"));
    else
    mu_assert("mips->operation is null for n1 in test_SLTU", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n2);
    if(mips->operation != NULL)
    mu_assert("error, opcode SLTU not loaded or incorrect for n2", !strcmp(mips->operation,"SLTU"));
    else
    mu_assert("mips->operation is null for n2 in test_SLTU", 0);
    mips->operation = NULL;   
    
    mips = getopcode(mips, n3);
    if(mips->operation != NULL)
    mu_assert("error, opcode SLTU not loaded or incorrect for n3", !strcmp(mips->operation,"SLTU"));
    else
    mu_assert("mips->operation is null for n3 in test_SLTU", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n4);
    if(mips->operation != NULL)
    mu_assert("error, opcode SLTU not loaded or incorrect for n4", !strcmp(mips->operation,"SLTU"));
    else
    mu_assert("mips->operation is null for n4 in test_SLTU", 0);
    mips->operation = NULL;   

    return 0;

}

static char * test_SRA() 
{
    mword n1 = 0x00FA8103;
    mword n2 = 0x00267A43;
    mword n3 = 0x0026DF83;
    mword n4 = 0x00872AC3;

    mips = getopcode(mips, n1);
    if(mips->operation != NULL)
    mu_assert("error, opcode SRA not loaded or incorrect for n1", !strcmp(mips->operation,"SRA"));
    else
    mu_assert("mips->operation is null for n1 in test_SRA", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n2);
    if(mips->operation != NULL)
    mu_assert("error, opcode SRA not loaded or incorrect for n2", !strcmp(mips->operation,"SRA"));
    else
    mu_assert("mips->operation is null for n2 in test_SRA", 0);
    mips->operation = NULL;   
    
    mips = getopcode(mips, n3);
    if(mips->operation != NULL)
    mu_assert("error, opcode SRA not loaded or incorrect for n3", !strcmp(mips->operation,"SRA"));
    else
    mu_assert("mips->operation is null for n3 in test_SRA", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n4);
    if(mips->operation != NULL)
    mu_assert("error, opcode SRA not loaded or incorrect for n4", !strcmp(mips->operation,"SRA"));
    else
    mu_assert("mips->operation is null for n4 in test_SRA", 0);
    mips->operation = NULL;   

    return 0;

}

static char * test_SRL() 
{
    mword n1 = 0x00FA8102;
    mword n2 = 0x00267A42;
    mword n3 = 0x0026DF82;
    mword n4 = 0x00872AC2;

    mips = getopcode(mips, n1);
    if(mips->operation != NULL)
    mu_assert("error, opcode SRL not loaded or incorrect for n1", !strcmp(mips->operation,"SRL"));
    else
    mu_assert("mips->operation is null for n1 in test_SRL", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n2);
    if(mips->operation != NULL)
    mu_assert("error, opcode SRL not loaded or incorrect for n2", !strcmp(mips->operation,"SRL"));
    else
    mu_assert("mips->operation is null for n2 in test_SRL", 0);
    mips->operation = NULL;   
    
    mips = getopcode(mips, n3);
    if(mips->operation != NULL)
    mu_assert("error, opcode SRL not loaded or incorrect for n3", !strcmp(mips->operation,"SRL"));
    else
    mu_assert("mips->operation is null for n3 in test_SRL", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n4);
    if(mips->operation != NULL)
    mu_assert("error, opcode SRL not loaded or incorrect for n4", !strcmp(mips->operation,"SRL"));
    else
    mu_assert("mips->operation is null for n4 in test_SRL", 0);
    mips->operation = NULL;   

    return 0;

}

static char * test_SUB() 
{
    mword n1 = 0x00FA8122;
    mword n2 = 0x01267A22;
    mword n3 = 0x0226DF22;
    mword n4 = 0x03872A22;

    mips = getopcode(mips, n1);
    if(mips->operation != NULL)
    mu_assert("error, opcode SUB not loaded or incorrect for n1", !strcmp(mips->operation,"SUB"));
    else
    mu_assert("mips->operation is null for n1 in test_SUB", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n2);
    if(mips->operation != NULL)
    mu_assert("error, opcode SUB not loaded or incorrect for n2", !strcmp(mips->operation,"SUB"));
    else
    mu_assert("mips->operation is null for n2 in test_SUB", 0);
    mips->operation = NULL;   
    
    mips = getopcode(mips, n3);
    if(mips->operation != NULL)
    mu_assert("error, opcode SUB not loaded or incorrect for n3", !strcmp(mips->operation,"SUB"));
    else
    mu_assert("mips->operation is null for n3 in test_SUB", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n4);
    if(mips->operation != NULL)
    mu_assert("error, opcode SUB not loaded or incorrect for n4", !strcmp(mips->operation,"SUB"));
    else
    mu_assert("mips->operation is null for n4 in test_SUB", 0);
    mips->operation = NULL;   

    return 0;

}

static char * test_SUBU() 
{
    mword n1 = 0x00FA8123;
    mword n2 = 0x01267A23;
    mword n3 = 0x0226DF23;
    mword n4 = 0x03872A23;

    mips = getopcode(mips, n1);
    if(mips->operation != NULL)
    mu_assert("error, opcode SUBU not loaded or incorrect for n1", !strcmp(mips->operation,"SUBU"));
    else
    mu_assert("mips->operation is null for n1 in test_SUBU", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n2);
    if(mips->operation != NULL)
    mu_assert("error, opcode SUBU not loaded or incorrect for n2", !strcmp(mips->operation,"SUBU"));
    else
    mu_assert("mips->operation is null for n2 in test_SUBU", 0);
    mips->operation = NULL;   
    
    mips = getopcode(mips, n3);
    if(mips->operation != NULL)
    mu_assert("error, opcode SUBU not loaded or incorrect for n3", !strcmp(mips->operation,"SUBU"));
    else
    mu_assert("mips->operation is null for n3 in test_SUBU", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n4);
    if(mips->operation != NULL)
    mu_assert("error, opcode SUBU not loaded or incorrect for n4", !strcmp(mips->operation,"SUBU"));
    else
    mu_assert("mips->operation is null for n4 in test_SUBU", 0);
    mips->operation = NULL;   

    return 0;

}

static char * test_SW() 
{
    mword n1 = 0xACFA819B;
    mword n2 = 0xAD267ABD;
    mword n3 = 0xAE26DFA3;
    mword n4 = 0xAF872AAF;

    mips = getopcode(mips, n1);
    if(mips->operation != NULL)
    mu_assert("error, opcode SW not loaded or incorrect for n1", !strcmp(mips->operation,"SW"));
    else
    mu_assert("mips->operation is null for n1 in test_SW", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n2);
    if(mips->operation != NULL)
    mu_assert("error, opcode SW not loaded or incorrect for n2", !strcmp(mips->operation,"SW"));
    else
    mu_assert("mips->operation is null for n2 in test_SW", 0);
    mips->operation = NULL;   
    
    mips = getopcode(mips, n3);
    if(mips->operation != NULL)
    mu_assert("error, opcode SW not loaded or incorrect for n3", !strcmp(mips->operation,"SW"));
    else
    mu_assert("mips->operation is null for n3 in test_SW", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n4);
    if(mips->operation != NULL)
    mu_assert("error, opcode SW not loaded or incorrect for n4", !strcmp(mips->operation,"SW"));
    else
    mu_assert("mips->operation is null for n4 in test_SW", 0);
    mips->operation = NULL;   

    return 0;

}

static char * test_SYSCALL() 
{
    mword n1 = 0x00FA810C;
    mword n2 = 0x01267A4C;
    mword n3 = 0x0226DF8C;
    mword n4 = 0x03872ACC;

    mips = getopcode(mips, n1);
    if(mips->operation != NULL)
    mu_assert("error, opcode SYSCALL not loaded or incorrect for n1", !strcmp(mips->operation,"SYSCALL"));
    else
    mu_assert("mips->operation is null for n1 in test_SYSCALL", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n2);
    if(mips->operation != NULL)
    mu_assert("error, opcode SYSCALL not loaded or incorrect for n2", !strcmp(mips->operation,"SYSCALL"));
    else
    mu_assert("mips->operation is null for n2 in test_SYSCALL", 0);
    mips->operation = NULL;   
    
    mips = getopcode(mips, n3);
    if(mips->operation != NULL)
    mu_assert("error, opcode SYSCALL not loaded or incorrect for n3", !strcmp(mips->operation,"SYSCALL"));
    else
    mu_assert("mips->operation is null for n3 in test_SYSCALL", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n4);
    if(mips->operation != NULL)
    mu_assert("error, opcode SYSCALL not loaded or incorrect for n4", !strcmp(mips->operation,"SYSCALL"));
    else
    mu_assert("mips->operation is null for n4 in test_SYSCALL", 0);
    mips->operation = NULL;   

    return 0;

}

static char * test_XOR() 
{
    mword n1 = 0x00FA8126;
    mword n2 = 0x01267A26;
    mword n3 = 0x0226DF26;
    mword n4 = 0x03872A26;

    mips = getopcode(mips, n1);
    if(mips->operation != NULL)
    mu_assert("error, opcode XOR not loaded or incorrect for n1", !strcmp(mips->operation,"XOR"));
    else
    mu_assert("mips->operation is null for n1 in test_XOR", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n2);
    if(mips->operation != NULL)
    mu_assert("error, opcode XOR not loaded or incorrect for n2", !strcmp(mips->operation,"XOR"));
    else
    mu_assert("mips->operation is null for n2 in test_XOR", 0);
    mips->operation = NULL;   
    
    mips = getopcode(mips, n3);
    if(mips->operation != NULL)
    mu_assert("error, opcode XOR not loaded or incorrect for n3", !strcmp(mips->operation,"XOR"));
    else
    mu_assert("mips->operation is null for n3 in test_XOR", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n4);
    if(mips->operation != NULL)
    mu_assert("error, opcode XOR not loaded or incorrect for n4", !strcmp(mips->operation,"XOR"));
    else
    mu_assert("mips->operation is null for n4 in test_XOR", 0);
    mips->operation = NULL;   

    return 0;

}


static char * test_which_operation()
{
    mips->operation = malloc(10);
    strcpy(mips->operation, "BNE");

    mips = which_operation_number(mips);

    mu_assert("opnum is 0", mips->opnum != 0);

    mu_assert("wrong operation number", mips->opnum == 11);

    free(mips->operation);

    return 0;
} 

static char * test_send_operation()
{
    mips->opnum = 0;
    mips->s_arg1 = 0;
    mips->s_arg2 = 1;
    mips->s_arg3 = 2;

    mips->disasm_output = malloc(80);

    mips = send_operation(mips, D_PRINT);

    mu_assert("printing incorrect for ADD $v0, $zero, $at", !strcmp(mips->disasm_output, "ADD $v0, $zero, $at"));

    free(mips->disasm_output);

    return 0;
}



 static char * all_tests() {
    mu_run_test(test_load_opcodes);
    mu_run_test(test_ADD);
    tests_run++;
    mu_run_test(test_ADDI);
    tests_run++;
    mu_run_test(test_ADDIU);
    tests_run++;
    mu_run_test(test_ADDU);
    tests_run++;
    mu_run_test(test_AND);
    tests_run++;
    mu_run_test(test_ANDI);
    tests_run++;
    mu_run_test(test_BEQ);
    tests_run++;
    mu_run_test(test_BGEZ);
    tests_run++;
    mu_run_test(test_BGTZ);
    tests_run++;
    mu_run_test(test_BLEZ);
    tests_run++;
    mu_run_test(test_BLTZ);
    tests_run++;
    mu_run_test(test_BNE);
    tests_run++;
    mu_run_test(test_BREAK);
    tests_run++;
    mu_run_test(test_DIV);
    tests_run++;
    mu_run_test(test_J);
    tests_run++;
    mu_run_test(test_JAL);
    tests_run++;
    mu_run_test(test_JALR);
    tests_run++;
    mu_run_test(test_JR);
    tests_run++;
    mu_run_test(test_LB);
    tests_run++;
    mu_run_test(test_LBU);
    tests_run++;
    mu_run_test(test_LUI);
    tests_run++;
    mu_run_test(test_LW);
    tests_run++;
    mu_run_test(test_MFHI);
    tests_run++;
    mu_run_test(test_MFLO);
    tests_run++;
    mu_run_test(test_MULT);
    tests_run++;
    mu_run_test(test_NOP);
    tests_run++;
    mu_run_test(test_OR);
    tests_run++;
    mu_run_test(test_ORI);
    tests_run++;
    mu_run_test(test_SB);
    tests_run++;
    mu_run_test(test_SEB);
    tests_run++;
    mu_run_test(test_SLL);
    tests_run++;
    mu_run_test(test_SLT);
    tests_run++;
    mu_run_test(test_SLTI);
    tests_run++;
    mu_run_test(test_SLTIU);
    tests_run++;
    mu_run_test(test_SLTU);
    tests_run++;
    mu_run_test(test_SRA);
    tests_run++;
    mu_run_test(test_SRL);
    tests_run++;
    mu_run_test(test_SUB);
    tests_run++;
    mu_run_test(test_SUBU);
    tests_run++;
    mu_run_test(test_SW);
    tests_run++;
    mu_run_test(test_SYSCALL);
    tests_run++;
    mu_run_test(test_XOR);
    tests_run++;    
    mu_run_test(test_which_operation);
    mu_run_test(test_send_operation);
    return 0;
 }
 
 int main(int argc, char **argv) {

    char *result;
    mips = malloc(sizeof(mips));

    if(mips != NULL)
    {
        result = all_tests();


        if (result != 0) {
        printf("%s\n", result);

        }
        else {
        // printf("PARSING TEST 1 PASSED\n");
        }
         printf("ran tests for %d instructions\n", tests_run/2);
    }
    else
    {
       printf("unable to allocate size for structure\n");
    }

    free(mips);
 
     return result != 0;

 }
