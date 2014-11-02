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
 
 static char * all_tests() {
    mu_run_test(test_diff);
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
