#include "../src/headers.h"
#include "../src/errors.h"
#include "../src/operations.h"
#include "minunit.h"

 int tests_run = 0; 
 struct ptype *mips;
 struct ptype mymips;
 int error;


static char * test_add()
{
	error = op_add(mips,9,10,11);
	mu_assert("add operation failed to add", *(mips->regs[11]) == 5 && error == 0);
	error = op_add(mips,12,13,11);
	mu_assert("add operation failed to return overflow exception", error == 1 && *(mips->regs[11]) == 5);
	
	return 0;
}

static char * test_addi()
{
	error = op_addi(mips,9,11,0x324F);
	mu_assert("addi operation failed to add", *(mips->regs[11]) == (2 + 0x324F));
	error = op_addi(mips,12,11,0x03);
	mu_assert("addi operation failed to return overflow exception", error == 1);
	
	return 0;
}

 static char * all_tests() {

    mu_run_test(test_add);
    mu_run_test(test_addi);


	return 0;

 }
 
 int main(int argc, char **argv) {

 	mips = &mymips;
 	// mips = malloc(sizeof(mips));

 	int i;
	for(i = 0; i < 32; i++)
	{
		mips->regs[i] = malloc( sizeof(int) );
		*(mips->regs[i]) = 0;
	}

	*(mips->regs[9]) = 2;
	*(mips->regs[10]) = 3;
	*(mips->regs[12]) = 0xFFFFFFFF;
	*(mips->regs[13]) = 0x1;

    char *result = all_tests();

    if (result != 0) {
     printf("%s\n", result);
    }
    else {
      // printf("TEST PASSED\n");
    }
    // printf("Tests run: %d\n", tests_run);


    for(i = 0; i < 32; i++)
	{
		free(mips->regs[i]);
	}

    // free(mips);
    return result != 0;
}