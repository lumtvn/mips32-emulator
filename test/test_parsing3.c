#include "../src/headers.h"
#include "../src/interpreter.h"
#include "minunit.h"

 int tests_run = 0; 
 struct ptype testdata;
 struct ptype *ptestdata;
 
 

 
 static char * all_tests() {
     return 0;
 }
 
 int main(int argc, char **argv) {

     testdata.incoming_line = malloc(MAXSIZE);
     strcpy(testdata.incoming_line,".tag");


     ptestdata = &testdata;
     ptestdata = parseline(ptestdata);

    // printf("testdata.label: '%s'\n", testdata.label);
    // printf("testdata.tag: '%s'\n", testdata.tag);
    // printf("testdata.operation: '%s'\n", testdata.operation);
    // printf("testdata.arg[0]: '%s'\n", testdata.arg[0]);
    // printf("testdata.arg[1]: '%s'\n", testdata.arg[1]);
    // printf("testdata.arg[2]: '%s'\n", testdata.arg[2]);
    // printf("testdata.arg[3]: '%s'\n", testdata.arg[3]);

     char *result = all_tests();
     if (result != 0) {
         printf("%s\n", result);
     }
     else {
         printf("PARSING TEST 3 PASSED\n");
     }
     printf("Tests run: %d\n", tests_run);
 
     return result != 0;
 }
