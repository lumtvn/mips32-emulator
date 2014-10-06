#include "../src/headers.h"
#include "../src/reader.h"
#include "minunit.h"

 int tests_run = 0;
 int res;
 struct ptype testdata;
 struct ptype *ptestdata;
 
  static char * test_diff() 
{
            mu_assert("error, the reader result file is different than expected", res == 0);
            return 0;
}
 
 static char * all_tests() {
    mu_run_test(test_diff);
     return 0;

 }
 
 int main(int argc, char **argv) {



     testdata.incoming_line = malloc(MAXSIZE);

     ptestdata = &testdata;

     ptestdata->filename = "./test/testscript.elf";
     ptestdata = readscript(ptestdata);
     
    const char *filepath = "./test/resultfiles/test_reader_result.txt";
 
    FILE *fp = fopen(filepath, "w+");
    if (fp != NULL)
        {
            fputs(ptestdata->full_script, fp);
            fclose(fp);
        }

    res = system("diff test/resultfiles/test_reader_expected.txt test/resultfiles/test_reader_result.txt");
 
     char *result = all_tests();
     if (result != 0) {
         printf("%s\n", result);
     }
     else {
         printf("READING TEST 1 PASSED\n");
     }
     printf("Tests run: %d\n", tests_run);
 
     return result != 0;
 }
