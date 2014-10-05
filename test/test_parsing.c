#include "../src/headers.h"
#include "../src/assembler.h"
#include "minunit.h"

 int tests_run = 0; 
 struct ptype testdata;
 struct ptype *ptestdata;

static char * test_label() 
{
        if(testdata.label != NULL)
            {
                mu_assert("error, the label is different to 'start'", strcmp(testdata.label, "start") == 0);
                return 0;
            }
        else
            {
                printf("testdata.label is NULL\n");
                return 0;
            }    
}

static char * test_tag() 
{
        if(testdata.tag != NULL)
            {
                mu_assert("error, the tag is different to '.text'", strcmp(testdata.tag, ".text") == 0);
                return 0;
            }
        else
            {
                printf("testdata.tag is NULL\n");
                return 0;
            }    
}

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

static char * test_argline4() 
{
        if(testdata.argline[3] != NULL)
            {
                mu_assert("error, the argline4 is different to '$r4'", strcmp(testdata.argline[3], "$r4") == 0);
                return 0;
            }
        else
            {
                printf("testdata.argline4 is NULL\n");
                return 0;
            }    
}
 
 static char * all_tests() {
     mu_run_test(test_label);
     mu_run_test(test_tag);
     mu_run_test(test_operation);
     mu_run_test(test_argline1);
     mu_run_test(test_argline2);
     mu_run_test(test_argline3);
     mu_run_test(test_argline4);
     return 0;
 }
 
 int main(int argc, char **argv) {



     testdata.incoming_line = malloc(MAXSIZE);
     strcpy(testdata.incoming_line, "start: .text ADD $r1, $r2, $r3");

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
         printf("PARSING TEST 1 PASSED\n");
     }
     printf("Tests run: %d\n", tests_run);
 
     return result != 0;
 }
