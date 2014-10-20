#include "../src/headers.h"
#include "../src/assembler.h"
#include "minunit.h"

 int tests_run = 0; 
 struct ptype testdata;
 struct ptype *ptestdata;
 
 static char * test_tag() 
{
        if(testdata.tag != NULL)
            {
                mu_assert("error, the tag is different to '.tag'", strcmp(testdata.tag, ".tag") == 0);
                return 0;
            }
        else
            {
                printf("testdata.tag is NULL\n");
                return 0;
            }    
}

 
 static char * all_tests() {
     mu_run_test(test_tag);
     return 0;
 }
 
 int main(int argc, char **argv) {

     testdata.incoming_line = malloc(MAXSIZE);
     strcpy(testdata.incoming_line,".tag");


     ptestdata = &testdata;
     ptestdata = parseline(ptestdata);

    printf("ptestdata->label: '%s'\n", ptestdata->label);
    printf("ptestdata->tag: '%s'\n", ptestdata->tag);
    printf("ptestdata->operation: '%s'\n", ptestdata->operation);
    printf("ptestdata->argline[0]: '%s'\n", ptestdata->argline[0]);
    printf("ptestdata->argline[1]: '%s'\n", ptestdata->argline[1]);
    printf("ptestdata->argline[2]: '%s'\n", ptestdata->argline[2]);
    printf("ptestdata->argline[3]: '%s'\n", ptestdata->argline[3]);

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
