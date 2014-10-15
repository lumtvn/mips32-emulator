#include "../src/headers.h"
#include "../src/environmentcommands.h"
#include "../src/assembler.h"
#include "minunit.h"

 int tests_run = 0; 
 int res;
 struct ptype testdata;
 struct ptype *ptestdata;

 static char * test_load() 
{           
        ptestdata->argenv[0] = "./test/testscript.elf";
        ptestdata = env_load(ptestdata);

        const char *filepath = "./test/resultfiles/test_load_result.txt";

        FILE *fp = fopen(filepath, "w+");
        if (fp != NULL)
            {
                fputs(ptestdata->full_script, fp);
                fclose(fp);
            }

        res = system("diff test/resultfiles/test_load_expected.txt test/resultfiles/test_load_result.txt");

        mu_assert("error, the load result file is different than expected",!res);
        return 0;
}
 
 
 static char * all_tests() {
    mu_run_test(test_load);
     return 0;

 }
 
 int main(int argc, char **argv) {

    ptestdata = &testdata;

    char *result = all_tests();
    if (result != 0) {
     printf("%s\n", result);
    }
    else {
     // printf("ENVIRONMENT TEST PASSED\n");
    }
    // printf("Tests run: %d\n", tests_run);

    return result != 0;
 }
