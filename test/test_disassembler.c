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
    mu_assert("mips->operation is null for n1", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n2);
    if(mips->operation != NULL)
    mu_assert("error, opcode ADDI not loaded or incorrect for n2", !strcmp(mips->operation,"ADDI"));
    else
    mu_assert("mips->operation is null for n2", 0);
    mips->operation = NULL;   
    
    mips = getopcode(mips, n3);
    if(mips->operation != NULL)
    mu_assert("error, opcode ADDI not loaded or incorrect for n3", !strcmp(mips->operation,"ADDI"));
    else
    mu_assert("mips->operation is null for n3", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n4);
    if(mips->operation != NULL)
    mu_assert("error, opcode ADDI not loaded or incorrect for n4", !strcmp(mips->operation,"ADDI"));
    else
    mu_assert("mips->operation is null for n4", 0);
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
    mu_assert("mips->operation is null for n1", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n2);
    if(mips->operation != NULL)
    mu_assert("error, opcode ADDIU not loaded or incorrect for n2", !strcmp(mips->operation,"ADDIU"));
    else
    mu_assert("mips->operation is null for n2", 0);
    mips->operation = NULL;   
    
    mips = getopcode(mips, n3);
    if(mips->operation != NULL)
    mu_assert("error, opcode ADDIU not loaded or incorrect for n3", !strcmp(mips->operation,"ADDIU"));
    else
    mu_assert("mips->operation is null for n3", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n4);
    if(mips->operation != NULL)
    mu_assert("error, opcode ADDIU not loaded or incorrect for n4", !strcmp(mips->operation,"ADDIU"));
    else
    mu_assert("mips->operation is null for n4", 0);
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
    mu_assert("mips->operation is null for n1", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n2);
    if(mips->operation != NULL)
    mu_assert("error, opcode ANDI not loaded or incorrect for n2", !strcmp(mips->operation,"ANDI"));
    else
    mu_assert("mips->operation is null for n2", 0);
    mips->operation = NULL;   
    
    mips = getopcode(mips, n3);
    if(mips->operation != NULL)
    mu_assert("error, opcode ANDI not loaded or incorrect for n3", !strcmp(mips->operation,"ANDI"));
    else
    mu_assert("mips->operation is null for n3", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n4);
    if(mips->operation != NULL)
    mu_assert("error, opcode ANDI not loaded or incorrect for n4", !strcmp(mips->operation,"ANDI"));
    else
    mu_assert("mips->operation is null for n4", 0);
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
    mu_assert("mips->operation is null for n1", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n2);
    if(mips->operation != NULL)
    mu_assert("error, opcode BEQ not loaded or incorrect for n2", !strcmp(mips->operation,"BEQ"));
    else
    mu_assert("mips->operation is null for n2", 0);
    mips->operation = NULL;   
    
    mips = getopcode(mips, n3);
    if(mips->operation != NULL)
    mu_assert("error, opcode BEQ not loaded or incorrect for n3", !strcmp(mips->operation,"BEQ"));
    else
    mu_assert("mips->operation is null for n3", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n4);
    if(mips->operation != NULL)
    mu_assert("error, opcode BEQ not loaded or incorrect for n4", !strcmp(mips->operation,"BEQ"));
    else
    mu_assert("mips->operation is null for n4", 0);
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
    mu_assert("mips->operation is null for n1", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n2);
    if(mips->operation != NULL)
    mu_assert("error, opcode BGTZ not loaded or incorrect for n2", !strcmp(mips->operation,"BGTZ"));
    else
    mu_assert("mips->operation is null for n2", 0);
    mips->operation = NULL;   
    
    mips = getopcode(mips, n3);
    if(mips->operation != NULL)
    mu_assert("error, opcode BGTZ not loaded or incorrect for n3", !strcmp(mips->operation,"BGTZ"));
    else
    mu_assert("mips->operation is null for n3", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n4);
    if(mips->operation != NULL)
    mu_assert("error, opcode BGTZ not loaded or incorrect for n4", !strcmp(mips->operation,"BGTZ"));
    else
    mu_assert("mips->operation is null for n4", 0);
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
    mu_assert("mips->operation is null for n1", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n2);
    if(mips->operation != NULL)
    mu_assert("error, opcode BLEZ not loaded or incorrect for n2", !strcmp(mips->operation,"BLEZ"));
    else
    mu_assert("mips->operation is null for n2", 0);
    mips->operation = NULL;   
    
    mips = getopcode(mips, n3);
    if(mips->operation != NULL)
    mu_assert("error, opcode BLEZ not loaded or incorrect for n3", !strcmp(mips->operation,"BLEZ"));
    else
    mu_assert("mips->operation is null for n3", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n4);
    if(mips->operation != NULL)
    mu_assert("error, opcode BLEZ not loaded or incorrect for n4", !strcmp(mips->operation,"BLEZ"));
    else
    mu_assert("mips->operation is null for n4", 0);
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
    mu_assert("mips->operation is null for n1", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n2);
    if(mips->operation != NULL)
    mu_assert("error, opcode BNE not loaded or incorrect for n2", !strcmp(mips->operation,"BNE"));
    else
    mu_assert("mips->operation is null for n2", 0);
    mips->operation = NULL;   
    
    mips = getopcode(mips, n3);
    if(mips->operation != NULL)
    mu_assert("error, opcode BNE not loaded or incorrect for n3", !strcmp(mips->operation,"BNE"));
    else
    mu_assert("mips->operation is null for n3", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n4);
    if(mips->operation != NULL)
    mu_assert("error, opcode BNE not loaded or incorrect for n4", !strcmp(mips->operation,"BNE"));
    else
    mu_assert("mips->operation is null for n4", 0);
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
    mu_assert("mips->operation is null for n1", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n2);
    if(mips->operation != NULL)
    mu_assert("error, opcode J not loaded or incorrect for n2", !strcmp(mips->operation,"J"));
    else
    mu_assert("mips->operation is null for n2", 0);
    mips->operation = NULL;   
    
    mips = getopcode(mips, n3);
    if(mips->operation != NULL)
    mu_assert("error, opcode J not loaded or incorrect for n3", !strcmp(mips->operation,"J"));
    else
    mu_assert("mips->operation is null for n3", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n4);
    if(mips->operation != NULL)
    mu_assert("error, opcode J not loaded or incorrect for n4", !strcmp(mips->operation,"J"));
    else
    mu_assert("mips->operation is null for n4", 0);
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
    mu_assert("mips->operation is null for n1", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n2);
    if(mips->operation != NULL)
    mu_assert("error, opcode JAL not loaded or incorrect for n2", !strcmp(mips->operation,"JAL"));
    else
    mu_assert("mips->operation is null for n2", 0);
    mips->operation = NULL;   
    
    mips = getopcode(mips, n3);
    if(mips->operation != NULL)
    mu_assert("error, opcode JAL not loaded or incorrect for n3", !strcmp(mips->operation,"JAL"));
    else
    mu_assert("mips->operation is null for n3", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n4);
    if(mips->operation != NULL)
    mu_assert("error, opcode JAL not loaded or incorrect for n4", !strcmp(mips->operation,"JAL"));
    else
    mu_assert("mips->operation is null for n4", 0);
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
    mu_assert("mips->operation is null for n1", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n2);
    if(mips->operation != NULL)
    mu_assert("error, opcode LB not loaded or incorrect for n2", !strcmp(mips->operation,"LB"));
    else
    mu_assert("mips->operation is null for n2", 0);
    mips->operation = NULL;   
    
    mips = getopcode(mips, n3);
    if(mips->operation != NULL)
    mu_assert("error, opcode LB not loaded or incorrect for n3", !strcmp(mips->operation,"LB"));
    else
    mu_assert("mips->operation is null for n3", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n4);
    if(mips->operation != NULL)
    mu_assert("error, opcode LB not loaded or incorrect for n4", !strcmp(mips->operation,"LB"));
    else
    mu_assert("mips->operation is null for n4", 0);
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
    mu_assert("mips->operation is null for n1", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n2);
    if(mips->operation != NULL)
    mu_assert("error, opcode LBU not loaded or incorrect for n2", !strcmp(mips->operation,"LBU"));
    else
    mu_assert("mips->operation is null for n2", 0);
    mips->operation = NULL;   
    
    mips = getopcode(mips, n3);
    if(mips->operation != NULL)
    mu_assert("error, opcode LBU not loaded or incorrect for n3", !strcmp(mips->operation,"LBU"));
    else
    mu_assert("mips->operation is null for n3", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n4);
    if(mips->operation != NULL)
    mu_assert("error, opcode LBU not loaded or incorrect for n4", !strcmp(mips->operation,"LBU"));
    else
    mu_assert("mips->operation is null for n4", 0);
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
    mu_assert("mips->operation is null for n1", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n2);
    if(mips->operation != NULL)
    mu_assert("error, opcode LUI not loaded or incorrect for n2", !strcmp(mips->operation,"LUI"));
    else
    mu_assert("mips->operation is null for n2", 0);
    mips->operation = NULL;   
    
    mips = getopcode(mips, n3);
    if(mips->operation != NULL)
    mu_assert("error, opcode LUI not loaded or incorrect for n3", !strcmp(mips->operation,"LUI"));
    else
    mu_assert("mips->operation is null for n3", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n4);
    if(mips->operation != NULL)
    mu_assert("error, opcode LUI not loaded or incorrect for n4", !strcmp(mips->operation,"LUI"));
    else
    mu_assert("mips->operation is null for n4", 0);
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
    mu_assert("mips->operation is null for n1", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n2);
    if(mips->operation != NULL)
    mu_assert("error, opcode LW not loaded or incorrect for n2", !strcmp(mips->operation,"LW"));
    else
    mu_assert("mips->operation is null for n2", 0);
    mips->operation = NULL;   
    
    mips = getopcode(mips, n3);
    if(mips->operation != NULL)
    mu_assert("error, opcode LW not loaded or incorrect for n3", !strcmp(mips->operation,"LW"));
    else
    mu_assert("mips->operation is null for n3", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n4);
    if(mips->operation != NULL)
    mu_assert("error, opcode LW not loaded or incorrect for n4", !strcmp(mips->operation,"LW"));
    else
    mu_assert("mips->operation is null for n4", 0);
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
    mu_assert("mips->operation is null for n1", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n2);
    if(mips->operation != NULL)
    mu_assert("error, opcode ORI not loaded or incorrect for n2", !strcmp(mips->operation,"ORI"));
    else
    mu_assert("mips->operation is null for n2", 0);
    mips->operation = NULL;   
    
    mips = getopcode(mips, n3);
    if(mips->operation != NULL)
    mu_assert("error, opcode ORI not loaded or incorrect for n3", !strcmp(mips->operation,"ORI"));
    else
    mu_assert("mips->operation is null for n3", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n4);
    if(mips->operation != NULL)
    mu_assert("error, opcode ORI not loaded or incorrect for n4", !strcmp(mips->operation,"ORI"));
    else
    mu_assert("mips->operation is null for n4", 0);
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
    mu_assert("mips->operation is null for n1", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n2);
    if(mips->operation != NULL)
    mu_assert("error, opcode SB not loaded or incorrect for n2", !strcmp(mips->operation,"SB"));
    else
    mu_assert("mips->operation is null for n2", 0);
    mips->operation = NULL;   
    
    mips = getopcode(mips, n3);
    if(mips->operation != NULL)
    mu_assert("error, opcode SB not loaded or incorrect for n3", !strcmp(mips->operation,"SB"));
    else
    mu_assert("mips->operation is null for n3", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n4);
    if(mips->operation != NULL)
    mu_assert("error, opcode SB not loaded or incorrect for n4", !strcmp(mips->operation,"SB"));
    else
    mu_assert("mips->operation is null for n4", 0);
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
    mu_assert("mips->operation is null for n1", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n2);
    if(mips->operation != NULL)
    mu_assert("error, opcode SLTI not loaded or incorrect for n2", !strcmp(mips->operation,"SLTI"));
    else
    mu_assert("mips->operation is null for n2", 0);
    mips->operation = NULL;   
    
    mips = getopcode(mips, n3);
    if(mips->operation != NULL)
    mu_assert("error, opcode SLTI not loaded or incorrect for n3", !strcmp(mips->operation,"SLTI"));
    else
    mu_assert("mips->operation is null for n3", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n4);
    if(mips->operation != NULL)
    mu_assert("error, opcode SLTI not loaded or incorrect for n4", !strcmp(mips->operation,"SLTI"));
    else
    mu_assert("mips->operation is null for n4", 0);
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
    mu_assert("mips->operation is null for n1", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n2);
    if(mips->operation != NULL)
    mu_assert("error, opcode SLTIU not loaded or incorrect for n2", !strcmp(mips->operation,"SLTIU"));
    else
    mu_assert("mips->operation is null for n2", 0);
    mips->operation = NULL;   
    
    mips = getopcode(mips, n3);
    if(mips->operation != NULL)
    mu_assert("error, opcode SLTIU not loaded or incorrect for n3", !strcmp(mips->operation,"SLTIU"));
    else
    mu_assert("mips->operation is null for n3", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n4);
    if(mips->operation != NULL)
    mu_assert("error, opcode SLTIU not loaded or incorrect for n4", !strcmp(mips->operation,"SLTIU"));
    else
    mu_assert("mips->operation is null for n4", 0);
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
    mu_assert("mips->operation is null for n1", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n2);
    if(mips->operation != NULL)
    mu_assert("error, opcode SW not loaded or incorrect for n2", !strcmp(mips->operation,"SW"));
    else
    mu_assert("mips->operation is null for n2", 0);
    mips->operation = NULL;   
    
    mips = getopcode(mips, n3);
    if(mips->operation != NULL)
    mu_assert("error, opcode SW not loaded or incorrect for n3", !strcmp(mips->operation,"SW"));
    else
    mu_assert("mips->operation is null for n3", 0);
    mips->operation = NULL;   

    mips = getopcode(mips, n4);
    if(mips->operation != NULL)
    mu_assert("error, opcode SW not loaded or incorrect for n4", !strcmp(mips->operation,"SW"));
    else
    mu_assert("mips->operation is null for n4", 0);
    mips->operation = NULL;   

    return 0;

}


 static char * all_tests() {
    mu_run_test(test_load_opcodes);
    printf("test_load_opcodes passed\n");
    mu_run_test(test_ADDI);
    printf("test_ADDI passed\n");
    mu_run_test(test_ADDIU);
    printf("test_ADDIU passed\n");
    mu_run_test(test_ANDI);
    printf("test_ANDI passed\n");
    mu_run_test(test_BEQ);
    printf("test_BEQ passed\n");
    mu_run_test(test_BGTZ);
    printf("test_BGTZ passed\n");
    mu_run_test(test_BLEZ);
    printf("test_BLEZ passed\n");
    mu_run_test(test_BNE);
    printf("test_BNE passed\n");
    mu_run_test(test_J);
    printf("test_J passed\n");
    mu_run_test(test_JAL);
    printf("test_JAL passed\n");
    mu_run_test(test_LB);
    printf("test_LB passed\n");
    mu_run_test(test_LBU);
    printf("test_LBU passed\n");
    mu_run_test(test_LUI);
    printf("test_LUI passed\n");
    mu_run_test(test_LW);
    printf("test_LW passed\n");
    mu_run_test(test_ORI);
    printf("test_ORI passed\n");
    mu_run_test(test_SB);
    printf("test_SB passed\n");
    mu_run_test(test_SLTI);
    printf("test_SLTI passed\n");
    mu_run_test(test_SLTIU);
    printf("test_SLTIU passed\n");
    mu_run_test(test_SW);
    printf("test_SW passed\n");

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
        // printf("Tests run: %d\n", tests_run);
    }
    else
    {
       printf("unable to allocate size for structure\n");
    }
 
     return result != 0;
 }
