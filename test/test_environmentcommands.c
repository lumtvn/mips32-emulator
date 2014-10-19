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

 static char * test_set_reg_success() 
{           
    res = system("diff test/resultfiles/test_set_reg_success_expected.txt test/resultfiles/test_set_reg_success_result.txt");
       
    mu_assert("error, the set reg succes result file is different than expected",!res);
    
    return 0;
}

 static char * test_set_reg_invreg() //tries to execute set reg using an invalid register argument
{           
    res = system("diff test/resultfiles/test_set_reg_invreg_expected.txt test/resultfiles/test_set_reg_invreg_result.txt");
       
    mu_assert("error, the set reg invalid register result file is different than expected",!res);
    
    return 0;
}

 static char * test_set_reg_invval() //tries to execute set reg using an invalid register argument
{           
    res = system("diff test/resultfiles/test_set_reg_invval_expected.txt test/resultfiles/test_set_reg_invval_result.txt");
       
    mu_assert("error, the set reg invalid value result file is different than expected",!res);
    
    return 0;
}

 static char * test_set_mem_byte() //tries to execute set reg using an invalid register argument
{           
    res = system("diff test/resultfiles/test_set_mem_byte_expected.txt test/resultfiles/test_set_mem_byte_result.txt");
       
    mu_assert("error, the set mem byte result file is different than expected",!res);
    
    return 0;
}

 static char * test_set_mem_word() //tries to execute set reg using an invalid register argument
{           
    res = system("diff test/resultfiles/test_set_mem_word_expected.txt test/resultfiles/test_set_mem_word_result.txt");
       
    mu_assert("error, the set mem word result file is different than expected",!res);
    
    return 0;
}

 static char * test_disp_reg() //tries to execute set reg using an invalid register argument
{           
    res = system("diff test/resultfiles/test_disp_reg_expected.txt test/resultfiles/test_disp_reg_result.txt");
       
    mu_assert("error, the display register result file is different than expected",!res);
    
    return 0;
}

 static char * test_assert() //tries to execute set reg using an invalid register argument
{           
    res = system("diff test/resultfiles/test_assert_expected.txt test/resultfiles/test_assert_result.txt");
       
    mu_assert("error, the assert result file is different than expected",!res);
    
    return 0;
}
 
 
 static char * all_tests() {
    mu_run_test(test_load);
    mu_run_test(test_disp_reg);
    mu_run_test(test_set_reg_success);
    mu_run_test(test_set_reg_invreg);
    mu_run_test(test_set_reg_invval);
    mu_run_test(test_set_mem_byte);
    mu_run_test(test_set_mem_word);
    mu_run_test(test_assert);
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
