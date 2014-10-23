#include "../src/headers.h"
#include "../src/assembler.h"
#include "minunit.h"

 int tests_run = 0; 
 struct ptype mips;
 struct ptype *pmips;

static char * test_parsing1() 
{
    pmips->incoming_line = "label: .text ADD $t1, $t2, $t3";

    pmips = parseline(pmips);

    mu_assert("error, the label is null",  pmips->label != NULL);
    mu_assert("error, the tag is null",  pmips->tag != NULL);
    mu_assert("error, the operation is null",  pmips->operation != NULL);
    mu_assert("error, the argline[0] is null",  pmips->argline[0] != NULL);
    mu_assert("error, the argline[1] is null",  pmips->argline[1] != NULL);
    mu_assert("error, the argline[2] is null",  pmips->argline[2] != NULL);

    mu_assert("error, the label is different to 'label:'", strcmp(pmips->label, "label:") == 0);
    mu_assert("error, the tag is different to '.text'", strcmp(pmips->tag, ".text") == 0);
    mu_assert("error, the operation is different to 'ADD'", strcmp(pmips->operation, "ADD") == 0);
    mu_assert("error, the arg1 is different to '$t1'", strcmp(pmips->argline[0], "$t1") == 0);
    mu_assert("error, the arg2 is different to '$t2'", strcmp(pmips->argline[1], "$t2") == 0);
    mu_assert("error, the arg3 is different to '$t3'", strcmp(pmips->argline[2], "$t3") == 0);

    pmips = clearline(pmips);
    return 0;
}

static char * test_parsing2() 
{
    pmips->incoming_line = ".text ADD $t1, $t2, $t3";

    pmips = parseline(pmips);

    mu_assert("error, the label isn't null",  pmips->label == NULL);

    mu_assert("error, the tag is null",  pmips->tag != NULL);
    mu_assert("error, the operation is null",  pmips->operation != NULL);
    mu_assert("error, the argline[0] is null",  pmips->argline[0] != NULL);
    mu_assert("error, the argline[1] is null",  pmips->argline[1] != NULL);
    mu_assert("error, the argline[2] is null",  pmips->argline[2] != NULL);

    mu_assert("error, the tag is different to '.text'", strcmp(pmips->tag, ".text") == 0);
    mu_assert("error, the operation is different to 'ADD'", strcmp(pmips->operation, "ADD") == 0);
    mu_assert("error, the arg1 is different to '$t1'", strcmp(pmips->argline[0], "$t1") == 0);
    mu_assert("error, the arg2 is different to '$t2'", strcmp(pmips->argline[1], "$t2") == 0);
    mu_assert("error, the arg3 is different to '$t3'", strcmp(pmips->argline[2], "$t3") == 0);

    pmips = clearline(pmips);
    return 0;
}

static char * test_parsing3() 
{
    pmips->incoming_line = "NOP";

    pmips = parseline(pmips);

    mu_assert("error, the label isn't null",  pmips->label == NULL);
    mu_assert("error, the tag isn't null",  pmips->tag == NULL);
    mu_assert("error, the operation is null",  pmips->operation != NULL);
    mu_assert("error, the argline[0] isn't null",  pmips->argline[0] == NULL);
    mu_assert("error, the argline[1] isn't null",  pmips->argline[1] == NULL);
    mu_assert("error, the argline[2] isn't null",  pmips->argline[2] == NULL);

    mu_assert("error, the operation is different to 'NOP'", strcmp(pmips->operation, "NOP") == 0);

    pmips = clearline(pmips);
    return 0;
}

static char * test_parsing4() 
{
    pmips->incoming_line = ".text";

    pmips = parseline(pmips);

    mu_assert("error, the label isn't null",  pmips->label == NULL);
    mu_assert("error, the tag is null",  pmips->tag != NULL);
    mu_assert("error, the operation isn't null",  pmips->operation == NULL);
    mu_assert("error, the argline[0] isn't null",  pmips->argline[0] == NULL);
    mu_assert("error, the argline[1] isn't null",  pmips->argline[1] == NULL);
    mu_assert("error, the argline[2] isn't null",  pmips->argline[2] == NULL);

    mu_assert("error, the tag is different to '.text'", strcmp(pmips->tag, ".text") == 0);

    pmips = clearline(pmips);
    return 0;
}

static char * test_parsing5() 
{
    pmips->incoming_line = "label:";

    pmips = parseline(pmips);

    mu_assert("error, the label is null",  pmips->label != NULL);
    mu_assert("error, the tag isn't null",  pmips->tag == NULL);
    mu_assert("error, the operation isn't null",  pmips->operation == NULL);
    mu_assert("error, the argline[0] isn't null",  pmips->argline[0] == NULL);
    mu_assert("error, the argline[1] isn't null",  pmips->argline[1] == NULL);
    mu_assert("error, the argline[2] isn't null",  pmips->argline[2] == NULL);

    mu_assert("error, the label is different to 'label:'", strcmp(pmips->label, "label:") == 0);

    pmips = clearline(pmips);
    return 0;
}

static char * test_parsing6() 
{
    pmips->incoming_line = "ADD $t1";

    pmips = parseline(pmips);

    mu_assert("error, the label isn't null",  pmips->label == NULL);
    mu_assert("error, the tag isn't null",  pmips->tag == NULL);
    mu_assert("error, the operation is null",  pmips->operation != NULL);
    mu_assert("error, the argline[0] is null",  pmips->argline[0] != NULL);
    mu_assert("error, the argline[1] isn't null",  pmips->argline[1] == NULL);
    mu_assert("error, the argline[2] isn't null",  pmips->argline[2] == NULL);

    mu_assert("error, the operation is different to 'ADD'", strcmp(pmips->operation, "ADD") == 0);
    mu_assert("error, the arg1 is different to '$t1'", strcmp(pmips->argline[0], "$t1") == 0);

    pmips = clearline(pmips);
    return 0;
}

static char * test_parsingnull() 
{
    pmips->incoming_line = "";

    pmips = parseline(pmips);

    mu_assert("error, the tag isn't null",  pmips->tag == NULL);
    mu_assert("error, the operation isn't null",  pmips->operation == NULL);
    mu_assert("error, the argline[0] isn't null",  pmips->argline[0] == NULL);
    mu_assert("error, the argline[1] isn't null",  pmips->argline[1] == NULL);
    mu_assert("error, the argline[2] isn't null",  pmips->argline[2] == NULL);

    pmips = clearline(pmips);
    return 0;
}


 
 static char * all_tests() {
     mu_run_test(test_parsing1);
    printf("test_parsing1 passed\n");
     mu_run_test(test_parsing2);
    printf("test_parsing2 passed\n");
     mu_run_test(test_parsing3);
    printf("test_parsing3 passed\n");
     mu_run_test(test_parsing4);
    printf("test_parsing4 passed\n");
     mu_run_test(test_parsing5);
    printf("test_parsing5 passed\n");
     mu_run_test(test_parsing6);
    printf("test_parsing6 passed\n");
     mu_run_test(test_parsingnull);
    printf("test_parsingnull passed\n");

    pmips = clearline(pmips);
     return 0;
 }
 
 int main(int argc, char **argv) {


     pmips = &mips;

    // printf("mips.label: '%s'\n", mips.label);
    // printf("mips.tag: '%s'\n", mips.tag);
    // printf("mips.operation: '%s'\n", mips.operation);
    // printf("mips.arg[0]: '%s'\n", mips.arg[0]);
    // printf("mips.arg[1]: '%s'\n", mips.arg[1]);
    // printf("mips.arg[2]: '%s'\n", mips.arg[2]);
    // printf("mips.arg[3]: '%s'\n", mips.arg[3]);

     char *result = all_tests();
     if (result != 0) {
         printf("%s\n", result);
     }
     else {
         // printf("PARSING TEST 1 PASSED\n");
     }
     // printf("Tests run: %d\n", tests_run);
 
     return result != 0;
 }
