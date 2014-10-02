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

     ptestdata = &testdata;
     ptestdata = readscript(ptestdata);
     printf("\n\n%s\n\n",ptestdata->full_script);
   //  ptestdata = parsescript(ptestdata);


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
