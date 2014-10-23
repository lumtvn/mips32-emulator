#include "../src/headers.h"
#include "minunit.h"

 int tests_run = 0; 
 int res;
 struct ptype testdata;
 struct ptype *ptestdata;

 static char * test_diff() 
{
    res = system("diff test/resultfiles/test_autoloader_expected.txt test/resultfiles/test_autoloader_result.txt");

    mu_assert("error, the autoloader result file is different than expected",res == 0);
    return 0;
}
 
 
 static char * all_tests() {
    mu_run_test(test_diff);
     return 0;

 }
 
 int main(int argc, char **argv) {


     char *result = all_tests();
     if (result != 0) {
         printf("%s\n", result);
     }
     else {
         // printf("AUTOLOADER TEST PASSED\n");
     }
     // printf("Tests run: %d\n", tests_run);
 
     return result != 0;
 }
