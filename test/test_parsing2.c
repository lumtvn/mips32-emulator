#include "../src/headers.h"
#include "../src/assembler.h"
#include "minunit.h"

 int tests_run = 0; 
 struct ptype testdata;
 struct ptype *ptestdata;
 
 

static char * test_operation() 
{
        if(testdata.operation != NULL)
            {
                mu_assert("error, the operation is different to 'ADD'", strcmp(testdata.operation, "ADD") == 0);
                return 0;
            }
        else
            {
                printf("testdata.operation is NULL\n");
                return 0;
            }    
}

static char * test_argline1() 
{
        if(testdata.argline[0]!= NULL)
            {
                mu_assert("error, the argline1 is different to '$r1'", strcmp(testdata.argline[0], "$r1") == 0);
                return 0;
            }
        else
            {
                printf("testdata.argline1 is NULL\n");
                return 0;
            }    
}

static char * test_argline2() 
{
        if(testdata.argline[1] != NULL)
            {
                mu_assert("error, the argline2 is different to '$r2'", strcmp(testdata.argline[1], "$r2") == 0);
                return 0;
            }
        else
            {
                printf("testdata.argline2 is NULL\n");
                return 0;
            }    
}

static char * test_argline3() 
{
        if(testdata.argline[2] != NULL)
            {
                mu_assert("error, the argline3 is different to '$r3'", strcmp(testdata.argline[2], "$r3") == 0);
                return 0;
            }
        else
            {
                printf("testdata.argline3 is NULL\n");
                return 0;
            }    
}
 
 static char * all_tests() {
     mu_run_test(test_operation);
     mu_run_test(test_argline1);
     mu_run_test(test_argline2);
     mu_run_test(test_argline3);

     return 0;
 }
 
 int main(int argc, char **argv) {

     testdata.incoming_line = malloc(MAXSIZE);
     strcpy(testdata.incoming_line,"ADD $r1, $r2, $r3");


     ptestdata = &testdata;
     ptestdata = parseline(ptestdata);

     

     char *result = all_tests();
     if (result != 0) {
         printf("%s\n", result);
     }
     else {
         printf("PARSING TEST 2 PASSED\n");
     }
     printf("Tests run: %d\n", tests_run);
 
     return result != 0;
 }
