#include "../src/headers.h"
#include "../src/reader.h"
#include "minunit.h"

 int tests_run = 0;
 int res;
 struct ptype *mips;
 
  static char * test_diff() 
{

    mips->filename = "./test/testscript.elf";
    mips = readscript(mips);

    const char *filepath = "./test/resultfiles/test_reader_result.txt";
 
    FILE *fp = fopen(filepath, "w+");
    if (fp != NULL)
        {
            fputs(mips->full_script, fp);
            fclose(fp);
        }

    res = system("diff test/resultfiles/test_reader_expected.txt test/resultfiles/test_reader_result.txt");

    mu_assert("error, files test/resultfiles/test_reader_expected.txt test/resultfiles/test_reader_result.txt differ",res == 0);
    return 0;
}

static char * test_parsing1() 
{
    strcpy(mips->incoming_line,"label: .text ADD $t1, $t2, $t3");

    mips = parseline(mips);

    mu_assert("error, the label is null",  mips->label != NULL);
    mu_assert("error, the tag is null",  mips->tag != NULL);
    mu_assert("error, the operation is null",  mips->operation != NULL);
    mu_assert("error, the argline[0] is null",  mips->argline[0] != NULL);
    mu_assert("error, the argline[1] is null",  mips->argline[1] != NULL);
    mu_assert("error, the argline[2] is null",  mips->argline[2] != NULL);

    mu_assert("error, the label is different to 'label:'", strcmp(mips->label, "label:") == 0);
    mu_assert("error, the tag is different to '.text'", strcmp(mips->tag, ".text") == 0);
    mu_assert("error, the operation is different to 'ADD'", strcmp(mips->operation, "ADD") == 0);
    mu_assert("error, the arg1 is different to '$t1'", strcmp(mips->argline[0], "$t1") == 0);
    mu_assert("error, the arg2 is different to '$t2'", strcmp(mips->argline[1], "$t2") == 0);
    mu_assert("error, the arg3 is different to '$t3'", strcmp(mips->argline[2], "$t3") == 0);

    mips = clearline(mips);
    return 0;
}

static char * test_parsing2() 
{
    strcpy(mips->incoming_line, ".text ADD $t1, $t2, $t3");

    mips = parseline(mips);

    mu_assert("error, the label isn't null",  mips->label == NULL);

    mu_assert("error, the tag is null",  mips->tag != NULL);
    mu_assert("error, the operation is null",  mips->operation != NULL);
    mu_assert("error, the argline[0] is null",  mips->argline[0] != NULL);
    mu_assert("error, the argline[1] is null",  mips->argline[1] != NULL);
    mu_assert("error, the argline[2] is null",  mips->argline[2] != NULL);

    mu_assert("error, the tag is different to '.text'", strcmp(mips->tag, ".text") == 0);
    mu_assert("error, the operation is different to 'ADD'", strcmp(mips->operation, "ADD") == 0);
    mu_assert("error, the arg1 is different to '$t1'", strcmp(mips->argline[0], "$t1") == 0);
    mu_assert("error, the arg2 is different to '$t2'", strcmp(mips->argline[1], "$t2") == 0);
    mu_assert("error, the arg3 is different to '$t3'", strcmp(mips->argline[2], "$t3") == 0);

    mips = clearline(mips);
    return 0;
}

static char * test_parsing3() 
{
    strcpy(mips->incoming_line, "NOP");

    mips = parseline(mips);

    mu_assert("error, the label isn't null",  mips->label == NULL);
    mu_assert("error, the tag isn't null",  mips->tag == NULL);
    mu_assert("error, the operation is null",  mips->operation != NULL);
    mu_assert("error, the argline[0] isn't null",  mips->argline[0] == NULL);
    mu_assert("error, the argline[1] isn't null",  mips->argline[1] == NULL);
    mu_assert("error, the argline[2] isn't null",  mips->argline[2] == NULL);

    mu_assert("error, the operation is different to 'NOP'", strcmp(mips->operation, "NOP") == 0);

    mips = clearline(mips);
    return 0;
}

static char * test_parsing4() 
{
    strcpy(mips->incoming_line, ".text");

    mips = parseline(mips);

    mu_assert("error, the label isn't null",  mips->label == NULL);
    mu_assert("error, the tag is null",  mips->tag != NULL);
    mu_assert("error, the operation isn't null",  mips->operation == NULL);
    mu_assert("error, the argline[0] isn't null",  mips->argline[0] == NULL);
    mu_assert("error, the argline[1] isn't null",  mips->argline[1] == NULL);
    mu_assert("error, the argline[2] isn't null",  mips->argline[2] == NULL);

    mu_assert("error, the tag is different to '.text'", strcmp(mips->tag, ".text") == 0);

    mips = clearline(mips);
    return 0;
}

static char * test_parsing5() 
{
    strcpy(mips->incoming_line, "label:");

    mips = parseline(mips);

    mu_assert("error, the label is null",  mips->label != NULL);
    mu_assert("error, the tag isn't null",  mips->tag == NULL);
    mu_assert("error, the operation isn't null",  mips->operation == NULL);
    mu_assert("error, the argline[0] isn't null",  mips->argline[0] == NULL);
    mu_assert("error, the argline[1] isn't null",  mips->argline[1] == NULL);
    mu_assert("error, the argline[2] isn't null",  mips->argline[2] == NULL);

    mu_assert("error, the label is different to 'label:'", strcmp(mips->label, "label:") == 0);

    mips = clearline(mips);
    return 0;
}

static char * test_parsing6() 
{
    strcpy(mips->incoming_line, "ADD $t1");

    mips = parseline(mips);

    mu_assert("error, the label isn't null",  mips->label == NULL);
    mu_assert("error, the tag isn't null",  mips->tag == NULL);
    mu_assert("error, the operation is null",  mips->operation != NULL);
    mu_assert("error, the argline[0] is null",  mips->argline[0] != NULL);
    mu_assert("error, the argline[1] isn't null",  mips->argline[1] == NULL);
    mu_assert("error, the argline[2] isn't null",  mips->argline[2] == NULL);

    mu_assert("error, the operation is different to 'ADD'", strcmp(mips->operation, "ADD") == 0);
    mu_assert("error, the arg1 is different to '$t1'", strcmp(mips->argline[0], "$t1") == 0);

    mips = clearline(mips);
    return 0;
}

static char * test_parsingnull() 
{
    strcpy(mips->incoming_line, "\n");

    mips = parseline(mips);

    mu_assert("error, the tag isn't null",  mips->tag == NULL);
    mu_assert("error, the operation isn't null",  mips->operation == NULL);
    mu_assert("error, the argline[0] isn't null",  mips->argline[0] == NULL);
    mu_assert("error, the argline[1] isn't null",  mips->argline[1] == NULL);
    mu_assert("error, the argline[2] isn't null",  mips->argline[2] == NULL);

    mips = clearline(mips);
    return 0;
}

static char * test_splitscript() 
{
    mips->filename = "./test/testscript.elf";

    mips = readscript(mips);

    mips = splitscript(mips);
/*    int i;
    for(i = 0; i < mips->nlines; i++)
        printf("scriptlines[%d]: %s\n",i,mips->scriptlines[i] );*/

    const char *filepath = "./test/resultfiles/test_splitscript_result.txt";

        FILE *fp = fopen(filepath, "w+");
        if (fp != NULL)
        {
            int i;
            for(i = 0; i < mips->nlines; i++)
            {
                fputs(mips->scriptlines[i], fp); 
                fputs("\n",fp);
            }
            fclose(fp);
        }

    res = system("diff test/resultfiles/test_splitscript_result.txt test/resultfiles/test_splitscript_expected.txt");

    mu_assert("error, the splitscript result file is different than expected",!res);

    return 0;
}
 
 static char * all_tests() {
    mu_run_test(test_diff);
    printf("test_diff passed\n");
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
    mu_run_test(test_splitscript);
    printf("test_splitscript passed\n");
     return 0;

 }
int main(int argc, char **argv) 
{
    mips = malloc(sizeof(struct ptype));


    char *result = all_tests();

    if (result != 0) {
     printf("%s\n", result);
    }
    else {
     // printf("READING TEST PASSED\n");
    }
    // printf("Tests run: %d\n", tests_run);

    return result != 0;
}
