#include "../src/headers.h"
#include "../src/reader.h"
#include "minunit.h"

 int tests_run = 0; 
 struct ptype testdata;
 struct ptype *ptestdata;
 
 
 static char * all_tests() {
    // no asserts here...
     return 0;

 }
 
 int main(int argc, char **argv) {



     testdata.incoming_line = malloc(MAXSIZE);

     ptestdata = &testdata;

     ptestdata->filename = "./test/testscript.elf";
     ptestdata = readscript(ptestdata);
     printf("\n\n%s\n\n",ptestdata->full_script);
     
    //toggle on and off the printf to check the output of readscript function


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
