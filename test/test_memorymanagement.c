#include "../src/headers.h"
#include "../src/memorymanagement.h"
#include "minunit.h"

int tests_run = 0;
struct mmemory mem;
struct mmemory *pmem;
 
 static char * test_createtagblock() 
{
	return 0;
}

 
 static char * all_tests() {
     mu_run_test(test_createtagblock);
     return 0;
 }
 
 int main(int argc, char **argv) {

 	pmem = &mem;


 	pmem->tag = "text";
 	pmem->blocksize = 0x63;
 	pmem = createtagblock(pmem);

 	pmem->wdata = 0x12345678;
 	pmem->simpoint = 0x32;
 	pmem = writeword(pmem);

 	pmem->hwdata = 0x1122;
 	pmem->simpoint = 0x0;
 	pmem = writehalfword(pmem);

  	pmem->bdata = 0x88;
 	pmem->simpoint = 0x40;
 	pmem = writebyte(pmem);

 	// displaymemory(pmem);
	// printf("now in memory: %d\n", *(pmem->realpointbase));

	pmem->simpoint = 0x32;
	pmem = readword(pmem);
	printf("in address %x: %x\n",pmem->simpoint, pmem->wdata);

	pmem->simpoint = 0x0;
	pmem = readhalfword(pmem);
	printf("in address %x: %x\n",pmem->simpoint, pmem->hwdata);

	pmem->simpoint = 0x40;
	pmem = readbyte(pmem);
	printf("in address %x: %x\n",pmem->simpoint, pmem->bdata);



	char *result = all_tests();
	if (result != 0) {
	 printf("%s\n", result);
	}
	else {
	 // printf("PARSING TEST 3 PASSED\n");
	}
	// printf("Tests run: %d\n", tests_run);

	return result != 0;
 }