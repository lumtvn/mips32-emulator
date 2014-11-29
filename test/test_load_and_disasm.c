#include "../src/disassembler.h"
#include "../src/elfmanager.h"
#include "../src/headers.h"
#include "minunit.h"

int tests_run = 0;
struct ptype mymips;
struct ptype *mips;
struct elfstr myelfdata;

static char * test_disasm_text()
{
	int i;
    int size;

    size = get_seg_size(".text");

    for(i = get_seg_start(".text"); i < size; i++)
    {
        mips = elfreadword(mips, mips->elfdata->memory, i);
        mu_assert("no segment asociated to address", mips->report != 501);
        mu_assert("can't read null content", mips->report != 502);


        mips = getopcode(mips, mips->wdata);
        mu_assert("mips->operation is null, something went wrong", mips->operation != NULL);

        printf("%s\n",mips->operation);

        return 0;
    }
	
}


 static char * all_tests() {

	mu_run_test(test_disasm_text);

	return 0;

 }
 
 int main(int argc, char **argv) {

    mips = &mymips;
    mips->elfdata = &myelfdata;

    mips->elfdata = start_and_load(mips->elfdata, "test/test_elf.o");


    char *result = all_tests();
    if (result != 0) {
     printf("%s\n", result);
    }
    else {
     // printf("ENVIRONMENT TEST PASSED\n");
    }
    // printf("Tests run: %d\n", tests_run);

    return result != 0;
 }