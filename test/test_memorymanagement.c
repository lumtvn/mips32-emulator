#include "../src/headers.h"
#include "../src/memorymanagement.h"
#include "minunit.h"

int tests_run = 0;
struct mmemory mem;
struct mmemory *pmem;
 
 static char * test_createtagblock() 
{

}

 
 static char * all_tests() {
     mu_run_test(test_createtagblock);
     return 0;
 }
 
 int main(int argc, char **argv) {

 	pmem = &mem;
 	pmem->tag = "text";
 	pmem->size = 1000;


 	pmem = createtagblock(mem);


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