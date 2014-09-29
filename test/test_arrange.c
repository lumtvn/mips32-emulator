#include "../src/headers.h"
#include "../src/interpreter.h"
#include "minunit.h"

 int tests_run = 0; 
 struct ptype testdata;
 struct ptype *ptestdata;
 
 

static char * test_operation() {
     mu_assert("error, the operation is different to 'ADD'", testdata.operation == "ADD");
     return 0;
 }

  static char * test_arg1() {
    mu_assert("error, the first argument is different to '$r1'", testdata.arg[0] == "$r1");
     return 0;
 }

  static char * test_arg2() {
    mu_assert("error, the second argument is different to '$r2'", testdata.arg[1] == "$r2");
     return 0;
 }
 
  static char * test_arg3() {
    mu_assert("error, the third argument is different to '$r3'", testdata.arg[2] == "$r3");
     return 0;
 }
 
 static char * all_tests() {
     mu_run_test(test_operation);
     mu_run_test(test_arg[0]);
     mu_run_test(test_arg[1]);
     mu_run_test(test_arg[2]);

     return 0;
 }
 
 int main(int argc, char **argv) {


     //testdata.incoming_line = "ADD $r1, $r2, $r3";

     testdata.tag = "ADD";
     testdata.operation = "$r1";
     testdata.arg[0] = "$r2";
     testdata.arg[1] = "$r3";
     testdata.arg[2] = NULL;
     testdata.arg[3] = NULL;
     testdata.comment = NULL;


     ptestdata = &testdata;
     ptestdata = arrange(ptestdata);

     

     char *result = all_tests();
     if (result != 0) {
         printf("%s\n", result);
     }
     else {
         printf("ALL TESTS PASSED\n");
     }
     printf("Tests run: %d\n", tests_run);
 
     return result != 0;
 }
