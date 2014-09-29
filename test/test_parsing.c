#include "../src/headers.h"
#include "../src/interpreter.h"
#include "minunit.h"

 int tests_run = 0; 
 struct ptype testdata;
 struct ptype *ptestdata;
 
 static char * test_tag() {
     mu_assert("error, the tag is different to '.text'", strcmp(testdata.tag, ".text") == 0);
     return 0;
 }
 
 static char * test_operation() {
     mu_assert("error, the operation is different to 'ADD'", strcmp(testdata.operation, "ADD") == 0);
     return 0;
 }

  static char * test_arg1() {
    mu_assert("error, the first argument is different to '$r1'", strcmp(testdata.arg[0], "$r1") == 0);
     return 0;
 }

  static char * test_arg2() {
    mu_assert("error, the second argument is different to '$r2'", strcmp(testdata.arg[1], "$r2") == 0);
     return 0;
 }
 
  static char * test_arg3() {
    mu_assert("error, the third argument is different to '$r3'", strcmp(testdata.arg[2], "$r3") == 0);
     return 0;
 }
 
  static char * test_arg4() {
    mu_assert("error, the fourth argument is different to '$r4'", strcmp(testdata.arg[3], "$r4") == 0);
     return 0;
 }
 
 static char * all_tests() {
     mu_run_test(test_tag);
     mu_run_test(test_operation);
     mu_run_test(test_arg1);
     mu_run_test(test_arg2);
     mu_run_test(test_arg3);
     mu_run_test(test_arg4);
     return 0;
 }
 
 int main(int argc, char **argv) {



     testdata.incoming_line = malloc(MAXSIZE);
     strcpy(testdata.incoming_line, ".text ADD $r1, $r2, $r3, $r4  # r2 + r3 ---> r1");

     ptestdata = &testdata;
     ptestdata = parse(ptestdata);

    printf("testdata.tag: '%s'\n", testdata.tag);
    printf("testdata.operation: '%s'\n", testdata.operation);
    printf("testdata.arg[0]: '%s'\n", testdata.arg[0]);
    printf("testdata.arg[1]: '%s'\n", testdata.arg[1]);
    printf("testdata.arg[2]: '%s'\n", testdata.arg[2]);
    printf("testdata.arg[3]: '%s'\n", testdata.arg[3]);

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
