
#include "../src/headers.h"
#include "../src/memorymanagement.h"
#include "minunit.h"

int tests_run = 0;
struct ptype mem;
struct ptype *pmem;


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

	mbyte bdata;
	mhalfword hwdata;
	mword wdata;

 	simpoint = 0x32;
 	pmem = writeword(pmem, 0x12345678, simpoint);

    mu_assert("fourth byte of word not written", *(pmem->realpoint) == 0x78);
    mu_assert("third byte of word not written", *(--pmem->realpoint) == 0x56);
    mu_assert("second byte of word not written", *(--pmem->realpoint) == 0x34);
    mu_assert("first byte of word not written", *(--pmem->realpoint) == 0x12);


 	simpoint = 0x0;
 	pmem = writehalfword(pmem, 0x1122, simpoint);

    mu_assert("halfword not written", *(pmem->realpoint) == 0x22);
    mu_assert("halfword not written", *(--pmem->realpoint) == 0x11);


 	simpoint = 0x40;
 	pmem = writebyte(pmem, 0x88, simpoint);

    mu_assert("byte not written", *(pmem->realpoint) == 0x88);

	return 0;
}

 static char * test_read() 
{
	mbyte bdata;
	mhalfword hwdata;
	mword wdata;

	pmem->realpoint = pmem->realpointbase + 0x20;

	*(pmem->realpoint) = 0x12;
	*(++pmem->realpoint) = 0x34;
	*(++pmem->realpoint) = 0x56;
	*(++pmem->realpoint) = 0x78;

	simpoint = 0x20;
	wdata = readword(pmem, simpoint);

	pmem->realpoint = pmem->realpointbase + 0x05;

	*(pmem->realpoint) = 0x22;
	*(++pmem->realpoint) = 0x33;

	simpoint = 0x05;
	hwdata = readhalfword(pmem, simpoint);

	pmem->realpoint = pmem->realpointbase + 0x60;

	*(pmem->realpoint) = 0x11;

	simpoint = 0x60;
	bdata = readbyte(pmem, simpoint);

	mu_assert("byte read incorrect", bdata == 0x11);
    mu_assert("halfword read incorrect", hwdata == 0x2233);
    mu_assert("word read incorrect", wdata == 0x12345678);

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