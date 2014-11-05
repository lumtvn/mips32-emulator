#include "../src/headers.h"
#include "../src/disassembler.h"
#include "../src/lookup.h"
#include "minunit.h"

 int tests_run = 0; 
 int res;
 struct ptype *mips;

static char * test_load_opcode() 
{
    mword n = 0x03FA819B;
    mips = getopcode(mips, n);

    if(mips->operation != NULL)
    mu_assert("error, opcode not loaded or incorrect", strcmp(mips->operation,"ADD"));
    else
    mu_assert("mips->operation is null", 0);   
    return 0;

}
 
 static char * all_tests() {
    mu_run_test(test_load_opcode);

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
