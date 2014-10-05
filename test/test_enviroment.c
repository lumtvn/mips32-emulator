#include "../src/headers.h"
#include "../src/enviroment.h"
#include "minunit.h"

 int tests_run = 0; 
 struct ptype testenv;
 struct ptype *ptestenv;
 
 
 static char * all_tests() {
    // no asserts here...
     return 0;

 }
 
 int main(int argc, char **argv) {
    
    ptestenv = &testenv;

    runenv(ptestenv);

     char *result = all_tests();
     if (result != 0) {
         printf("%s\n", result);
     }
     else {
         printf("READING TEST 1 PASSED\n");
     }
     printf("Tests run: %d\n", tests_run);
 
     return result != 0;
 }
