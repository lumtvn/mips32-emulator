#include "../src/headers.h"
#include "../src/disassembler.h"
#include "../src/elfmanager.h"
#include "minunit.h"

int tests_run = 0;
struct ptype mymips;
struct ptype *mips;
struct elfstr myelfdata;



static char * test_getopcodes_text()
{

    int size, start;
    mips = &mymips;
    mips->elfdata = &myelfdata;
    // mips->elfdata = malloc(sizeof(mips->elfdata));
    // mu_assert("no memory for mips->elfdata", mips->elfdata != NULL);

    mips->elfdata = start_and_load(mips->elfdata, "test/test_elf.o");

    mu_assert("the file does not exist or the path is incorrect", mips->elfdata->report != 100);
    mu_assert("file entered isn't ELF", mips->elfdata->report != 101);


    size = get_seg_size(mips->elfdata->memory, ".text");
    start = get_seg_start(mips->elfdata->memory, ".text");

    // printf("start: 0x%x\n", start);
    // printf("size: %d\n", size);
    mu_assert("size should be divisable by 4", size%4 == 0);

    mu_assert("opcodes not loaded correctly", load_opcodes() == 0);

    int i;
    for(i = (int)start; i < (int)size + (int)start ; i = i + 4)
    {

        mips = elfreadword(mips, mips->elfdata->memory, i);
        mu_assert("no segment asociated to address", mips->report != 501);
        mu_assert("can't read null content", mips->report != 502);

        mips = getopcode(mips, mips->wdata);
        mu_assert("mips->operation is null, something went wrong", mips->operation != NULL);


        // printf("hexa in 0x%x: 0x%x, operation: %s\n",i, mips->wdata, mips->operation);
        switch(i)
        {
            case 0x3000:mu_assert("wrong operation in address 0x3000", !strcmp(mips->operation, "ADDI")); break;
            case 0x3004:mu_assert("wrong operation in address 0x3004", !strcmp(mips->operation, "ADD")); break;
            case 0x3008:mu_assert("wrong operation in address 0x3008", !strcmp(mips->operation, "ADDI")); break;
            case 0x300C:mu_assert("wrong operation in address 0x300C", !strcmp(mips->operation, "BNE")); break;
            case 0x3010:mu_assert("wrong operation in address 0x3010", !strcmp(mips->operation, "NOP")); break;
            case 0x3014:mu_assert("wrong operation in address 0x3014", !strcmp(mips->operation, "ADD")); break;
            default: mu_assert("?????????", 0);
        }
    }

    // free(mips->elfdata);

    return 0;
}


static char * test_disasm_instr()
{
    mips = &mymips;
    int size, start;
    // mips->elfdata = malloc(sizeof(mips->elfdata));
    // mu_assert("no memory for elfdata", mips->disasm_output != NULL);
    mips->elfdata = &myelfdata;
    mips->disasm_output = malloc(80);
    mu_assert("no memory for disasm_output", mips->disasm_output != NULL);

    mips->elfdata = start_and_load(mips->elfdata, "test/test_elf.o");

    mu_assert("the file does not exist or the path is incorrect", mips->elfdata->report != 100);
    mu_assert("file entered isn't ELF", mips->elfdata->report != 101);

    size = get_seg_size(mips->elfdata->memory, ".text");
    start = get_seg_start(mips->elfdata->memory, ".text");

    // printf("start: 0x%x\n", start);
    // printf("size: %d\n", size);
    mu_assert("size should be divisable by 4", size%4 == 0);

    mu_assert("opcodes not loaded correctly", load_opcodes() == 0);

    mips = disasm_instr(mips, start + 4, D_PRINT);

    mu_assert("error 601, no file loaded", mips->report != 601);
    mu_assert("error 602, reading section out of bounds", mips->report != 602);
    mu_assert("error 603, can't dissassemble in section out of text", mips->report != 603);
    mu_assert("error 604, couldn't find operation", mips->report != 604);
    mu_assert("error 610, operation not implemented or not existant", mips->report != 610);


    mu_assert("disasm_output is wrong", !strcmp(mips->disasm_output,"ADD $t2, $zero, $zero"));

    // destroy_mem(mips->elfdata);
    // free(mips->elfdata);
    free(mips->disasm_output);

    return 0;

}

 static char * all_tests() {

	mu_run_test(test_getopcodes_text);
    mu_run_test(test_disasm_instr);

	return 0;

 }
 
 int main(int argc, char **argv) {

    char *result = all_tests();
    if (result != 0) {
     printf("%s\n", result);
    }
    else {
      // printf("TEST PASSED\n");
    }
    // printf("Tests run: %d\n", tests_run);

    // free(mips);
    // free(mips->elfdata);
    // free(mips);
    return 0;
}


