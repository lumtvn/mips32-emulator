
#include "../src/headers.h"
#include "../src/memorymanagement.h"
#include "../src/lookup.h"
#include "minunit.h"

int tests_run = 0;
struct ptype mem;
struct ptype *pmem;


int simpoint;
 
 static char * test_creatememory() 
{
	// pmem->tag = "text";
 	int size = 0x63;
 	pmem = creatememory(pmem, size);

    mu_assert("block not assigned", pmem->memrealpointbase != NULL);
	return 0;
}

 static char * test_createsegment() 
{

	char *name = "mysegment";
	int size = 50;
	int permissions = 1;
	int start = 0x4000;
	struct nlist *np;

 	pmem = createsegment(pmem, name, size, permissions, start);
 	np = lookup("SEGSIZE_mysegment");
    mu_assert("size not assigned", !strcmp(np->defn,"50"));
 	np = lookup("SEGPERM_mysegment");
    mu_assert("permissions not assigned", !strcmp(np->defn,"1"));
 	np = lookup("SEGSTART_mysegment");
    mu_assert("start address not assigned", !strcmp(np->defn,"4000"));

	return 0;
}


 static char * test_write() 
{	

	mbyte bdata;
	mhalfword hwdata;
	mword wdata;

 	simpoint = 0x32;
 	pmem = writeword(pmem, 0x12345678, simpoint);

    mu_assert("fourth byte of word not written", *(pmem->memrealpoint) == 0x78);
    mu_assert("third byte of word not written", *(--pmem->memrealpoint) == 0x56);
    mu_assert("second byte of word not written", *(--pmem->memrealpoint) == 0x34);
    mu_assert("first byte of word not written", *(--pmem->memrealpoint) == 0x12);


 	simpoint = 0x0;
 	pmem = writehalfword(pmem, 0x1122, simpoint);

    mu_assert("halfword not written", *(pmem->memrealpoint) == 0x22);
    mu_assert("halfword not written", *(--pmem->memrealpoint) == 0x11);


 	simpoint = 0x40;
 	pmem = writebyte(pmem, 0x88, simpoint);

    mu_assert("byte not written", *(pmem->memrealpoint) == 0x88);


	return 0;
}

 static char * test_read() 
{
	mbyte bdata;
	mhalfword hwdata;
	mword wdata;

	pmem->memrealpoint = pmem->memrealpointbase + 0x20;

	*(pmem->memrealpoint) = 0x12;
	*(++pmem->memrealpoint) = 0x34;
	*(++pmem->memrealpoint) = 0x56;
	*(++pmem->memrealpoint) = 0x78;

	simpoint = 0x20;
	wdata = readword(pmem, simpoint);

	pmem->memrealpoint = pmem->memrealpointbase + 0x05;

	*(pmem->memrealpoint) = 0x22;
	*(++pmem->memrealpoint) = 0x33;

	simpoint = 0x05;
	hwdata = readhalfword(pmem, simpoint);

	pmem->memrealpoint = pmem->memrealpointbase + 0x60;

	*(pmem->memrealpoint) = 0x11;

	simpoint = 0x60;
	bdata = readbyte(pmem, simpoint);

	mu_assert("byte read incorrect", bdata == 0x11);
    mu_assert("halfword read incorrect", hwdata == 0x2233);
    mu_assert("word read incorrect", wdata == 0x12345678);

	return 0;
}
/*the simulator had some trouble writing and reading powers of 2 so im making sure it works here*/
 static char * test_read_write_2_power() 
{
	mbyte bdata;
	mhalfword hwdata;
	mword wdata;

 	simpoint = 0x32;
 	pmem = writeword(pmem, 0x10000000, simpoint);

 	simpoint = 0x0;
 	pmem = writehalfword(pmem, 0x1000, simpoint);

 	simpoint = 0x40;
 	pmem = writebyte(pmem, 0x20, simpoint);

	simpoint = 0x32;
	wdata = readword(pmem, simpoint);

	simpoint = 0x00;
	hwdata = readhalfword(pmem, simpoint);

	simpoint = 0x40;
	bdata = readbyte(pmem, simpoint);

	mu_assert("byte read incorrect", bdata == 0x20);
    mu_assert("halfword read incorrect", hwdata == 0x1000);
    mu_assert("word read incorrect", wdata == 0x10000000);

    return 0;

}
 
 static char * all_tests() {
     mu_run_test(test_creatememory);
     mu_run_test(test_createsegment);
     mu_run_test(test_write);
     mu_run_test(test_read);
     mu_run_test(test_read_write_2_power);
     return 0;
 }
 
 int main(int argc, char **argv) {

 	pmem = &mem;


 	pmem->segname = malloc(20);
	if(pmem->segname == NULL){pmem->report = 0; printf("malloc null\n");}
	pmem->segsize = malloc(20);
	if(pmem->segsize == NULL){pmem->report = 0; printf("malloc null\n");}
	pmem->segperm = malloc(20);
	if(pmem->segperm == NULL){pmem->report = 0; printf("malloc null\n");}
	pmem->segstart = malloc(20);
	if(pmem->segstart == NULL){pmem->report = 0; printf("malloc null\n");}

	char *result = all_tests();
	if (result != 0) {
	 printf("%s\n", result);
	}
	else {
	 // printf("PARSING TEST 3 PASSED\n");
	}

	free(pmem->segstart);
	free(pmem->segperm);
	free(pmem->segname);
	free(pmem->memrealpointbase);
	// printf("Tests run: %d\n", tests_run);

	return result != 0;
 }