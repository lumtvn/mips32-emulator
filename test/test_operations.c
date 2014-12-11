#include "../src/headers.h"
#include "../src/errors.h"
#include "../src/operations.h"
#include "minunit.h"

 int tests_run = 0; 
 struct mipsstr *mips;
 struct mipsstr mymips;

static char * test_add()
{

	int i;
	for(i = 0; i < 32; i++)
	{
		mips->regs[i] = malloc( sizeof(int) );
		mu_assert("no room for regs", mips->regs[i] != NULL);
		*(mips->regs[i]) = 0;
	}

	int error;

	*(mips->regs[9]) = 2;
	*(mips->regs[10]) = 3;

	error = op_add(mips,9,10,11);

	mu_assert("add operation failed to add", *(mips->regs[11]) == 5 && error == 0);

	*(mips->regs[9]) = 0xFFFFFFFF;
	*(mips->regs[10]) = 0x1;

	error = op_add(mips,9,10,11);
	if(error > 0)

	mu_assert("add operation failed to return overflow exception", error == 1 && *(mips->regs[11]) == 5);


	for(i = 0; i < 32; i++)
    {
        free(mips->regs[i]);
    }


	return 0;

}

 static char * all_tests() {

    mu_run_test(test_add);


	return 0;

 }
 
 int main(int argc, char **argv) {

 	mips = &mymips;
 	// mips = malloc(sizeof(mips));

/* 	int i;
	for(i = 0; i < 32; i++)
	{
		mips->regs[i] = malloc( sizeof(int) );
		*(mips->regs[i]) = 0;
	}*/

    char *result = all_tests();

    if (result != 0) {
     printf("%s\n", result);
    }
    else {
      // printf("TEST PASSED\n");
    }
    // printf("Tests run: %d\n", tests_run);


/*    for(i = 0; i < 32; i++)
	{
		free(mips->regs[i]);
	}*/

    // free(mips);
    return 0;
}