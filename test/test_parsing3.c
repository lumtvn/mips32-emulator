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


     char *result = all_tests();
     if (result != 0) {
         printf("%s\n", result);
     }
 
     return result != 0;
 }
