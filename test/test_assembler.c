#include "../src/headers.h"
#include "../src/assembler.h"
#include "../src/reader.h"
#include "../src/lookup.h"
#include "minunit.h"

 int tests_run = 0; 
 int res;
 struct ptype *mips;

static char * test_firstpass() 
{

    mips->scriptlines[0] = "# Hello, World!";
    mips->scriptlines[1] = ".data";
    mips->scriptlines[2] = "out_string: .asciiz 'Hello, World!'";
    mips->scriptlines[3] = ".text" ;
    mips->scriptlines[4] = "main:" ;
    mips->scriptlines[5] = "li $v0, 4" ;
    mips->scriptlines[6] = "la $a0, out_string";
    mips->scriptlines[7] = "syscall";
    mips->scriptlines[8] = "li $v0, 10";
    mips->scriptlines[9] = "j main";

    mips->nlines = 10;
    
    mips = firstpass(mips);

    struct nlist *np;
    np = lookup("main:");    

    if(np != NULL)
    {
    mu_assert("error, case 1 firstpass failed", atoi(np->defn) == 4);
    }   
    else {mu_assert("error, case 1 lookup returned null", 0);}


    np = lookup("out_string:");    

    if(np != NULL)
    {
    mu_assert("error, case 2 firstpass failed", atoi(np->defn) == 2);
    }   
    else {mu_assert("error, case 2 lookup returned null", 0);}

    return 0;

}
 
 static char * all_tests() {
   
    mu_run_test(test_firstpass);

    return 0;
 }
 
 int main(int argc, char **argv) {


    char *result;

/*    printf("mips->label: '%s'\n", mips->label);
    printf("mips->tag: '%s'\n", mips->tag);
    printf("mips->operation: '%s'\n", mips->operation);
    printf("mips->argline[0]: '%s'\n", mips->argline[0]);
    printf("mips->argline[1]: '%s'\n", mips->argline[1]);
    printf("mips->argline[2]: '%s'\n", mips->argline[2]);
    printf("mips->argline[3]: '%s'\n", mips->argline[3]);*/
    if(mips != NULL)
    {
        result = all_tests();


        if (result != 0) {
        printf("%s\n", result);

        }
        else {
        // printf("PARSING TEST 1 PASSED\n");
        }
        // printf("Tests run: %d\n", tests_run);
    }
 
     return result != 0;
 }
