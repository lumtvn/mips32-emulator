
#include "../src/headers.h"
#include "../src/memorymanagement.h"
#include "minunit.h"

int tests_run = 0;
struct ptype mem;
struct ptype *pmem;

mbyte bdata;
mhalfword hwdata;
mword wdata;
int simpoint;
 
 static char * test_createblock() 
{
	// pmem->tag = "text";
 	int size = 0x63;
 	pmem = createblock(pmem, size);

    mu_assert("block not assigned", pmem->realpointbase != NULL);
	return 0;
}


 static char * test_write() 
{	

 	wdata = 0x12345678;
 	simpoint = 0x32;
 	pmem = writeword(pmem, wdata, simpoint);

 	hwdata = 0x1122;
 	simpoint = 0x0;
 	pmem = writehalfword(pmem, hwdata, simpoint);

  	bdata = 0x88;
 	simpoint = 0x40;
 	pmem = writebyte(pmem, bdata, simpoint);

    mu_assert("byte not written", bdata == 0x88);
    mu_assert("halfword not written", hwdata == 0x1122);
    mu_assert("word not written", wdata == 0x12345678);

	wdata = 0;
 	hwdata = 0;
	bdata = 0;

	return 0;
}

 static char * test_read() 
{


	simpoint = 0x32;
	wdata = readword(pmem, simpoint);

	simpoint = 0x0;
	hwdata = readhalfword(pmem, simpoint);

	simpoint = 0x40;
	bdata = readbyte(pmem, simpoint);

	mu_assert("byte not read", bdata == 0x88);
    mu_assert("halfword not read", hwdata == 0x1122);
    mu_assert("word not read", wdata == 0x12345678);

	return 0;
}
 
 static char * all_tests() {
     mu_run_test(test_createblock);
     mu_run_test(test_write);
     mu_run_test(test_read);
     return 0;
 }
 
 int main(int argc, char **argv) {

 	pmem = &mem;

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