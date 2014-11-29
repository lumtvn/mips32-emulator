#include "../src/headers.h"
#include "../src/disassembler.h"
#include "../src/elfmanager.h"
#include "minunit.h"

int tests_run = 0;
// struct ptype mymips;
struct ptype *mips;
 struct elfstr myelfdata;



static char * test_disasm_text()
{

    int size, start;
    mips = malloc(sizeof(mips));
    mu_assert("no memory for mips", mips != NULL);
    mips->elfdata = &myelfdata;

    char *file;
    printf("choose file to disassemble\n");
    fgets(file, 100, stdin);
    mu_assert("file is null", file != NULL);
    strtok(file, "\n");

    // mips->elfdata = malloc(sizeof(mips->elfdata));
    // mu_assert("no memory for mips->elfdata", mips->elfdata != NULL);

    mips->elfdata = start_and_load(mips->elfdata, file);

    if(mips->elfdata->report == 100)
    {
        printf("the file %s does not exist or the path is incorrect\n", file);
        mu_assert("",0);
    }
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


         printf("hexa in 0x%x: 0x%x, operation: %s\n",i, mips->wdata, mips->operation);
    }

    // free(mips->elfdata);
    free(mips);

    return 0;
}


 static char * all_tests() {

	mu_run_test(test_disasm_text);

	return 0;

 }
 
 int main(int argc, char **argv) {

    // mips = &mymips;

    char *result = all_tests();
    if (result != 0) {
     printf("%s\n", result);
    }
    else {
     // printf("ENVIRONMENT TEST PASSED\n");
    }
    // printf("Tests run: %d\n", tests_run);

    // free(mips);
    // free(mips->elfdata);

    return result != 0;
 }