#include "../src/headers.h"
#include "../src/memorymanagement.h"
#include "../elfapi/include/elf/syms.h"
#include "../elfapi/include/mem.h"
#include "../src/elfmanager.h"
#include "../src/lookup.h"
#include "minunit.h"

int tests_run = 0;
struct ptype mips;
struct ptype *pmips;


int simpoint;
 
 static char * test_creatememory() 
{
	char *filename = "test/test_elf.o";
	struct nlist *np;
 
 	pmips = my_init_mem(pmips, filename);

 	printf("memory total size: %d\n",pmips->memsize);

 	np = lookup("SEGSIZE_.text");
 	if(np != NULL)
 	printf("segment text's size: %s\n", np->defn);
 	np = lookup("SEGPERM_.text");
 	if(np != NULL)
 	printf("segment text's permissions: %s\n", np->defn);
 	np = lookup("SEGSTART_.text");
 	if(np != NULL)
 	printf("segment text's start address: %s\n", np->defn);

 	np = lookup("SEGSIZE_.data");
 	if(np != NULL)
 	printf("segment data's size: %s\n", np->defn);
 	np = lookup("SEGPERM_.data");
 	if(np != NULL)
 	printf("segment data's permissions: %s\n", np->defn);
 	np = lookup("SEGSTART_.data");
 	if(np != NULL)
 	printf("segment data's start address: %s\n", np->defn);

 	np = lookup("SEGSIZE_.bss");
 	if(np != NULL)
 	printf("segment bss's size: %s\n", np->defn);
 	np = lookup("SEGPERM_.bss");
 	if(np != NULL)
 	printf("segment bss's permissions: %s\n", np->defn);
 	np = lookup("SEGSTART_.bss");
 	if(np != NULL)
 	printf("segment bss's start address: %s\n", np->defn);

 	printf("%d\n", pmips->report);

 	mu_assert("np is null", np != NULL);

 	// pmips = displaymemory(pmips);

 	pmips = destroymemory(pmips);
	return 0;
}
 
 static char * all_tests() {
     mu_run_test(test_creatememory);
     return 0;
 }
 
 int main(int argc, char **argv) {

 	pmips = &mips;

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