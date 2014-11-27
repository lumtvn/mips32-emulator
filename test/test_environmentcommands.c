#include "../src/headers.h"
#include "../src/environmentcommands.h"
#include "../src/disassembler.h"
#include "minunit.h"

int tests_run = 0; 
int res;
struct ptype testdata;
struct ptype *ptestdata;
struct elfstr myelfstr;


 static char * test_load() 
{           
    ptestdata->elfdata = &myelfstr;
    ptestdata->argenv[0] = "./test/test_elf.o";

    dup2(fileno(stdout), fileno(stderr));
    ptestdata = env_load(ptestdata);

    // res = system("diff test/resultfiles/test_load_expected.txt test/resultfiles/test_load_result.txt");

    // mu_assert("error, the load result file is different than expected",!res);

    return 0;
}
 static char * test_set_mem_byte() 
{
    ptestdata->n_argenv = 4;

    ptestdata->argenv[0] = "mem";
    ptestdata->argenv[1] = "byte";
    ptestdata->argenv[2] = "10";
    ptestdata->argenv[3] = "15";

    ptestdata = env_set(ptestdata);

    mu_assert("deberia haber algun error pero no hay", ptestdata->report == 501);

    ptestdata->argenv[0] = "mem";
    ptestdata->argenv[1] = "byte";
    ptestdata->argenv[2] = "0x3000";
    ptestdata->argenv[3] = "0xFF";

    ptestdata = env_set(ptestdata);

    mu_assert("deberia haber algun error pero no hay", ptestdata->report == 503);

    ptestdata->argenv[0] = "mem";
    ptestdata->argenv[1] = "byte";
    ptestdata->argenv[2] = "0x4001";
    ptestdata->argenv[3] = "0xFF";

    ptestdata = env_set(ptestdata);

    mu_assert("no deberia haber errores", ptestdata->report == 0);

    return 0;
}

 static char * test_set_mem_word()
 {
    ptestdata->n_argenv = 4;

    ptestdata->argenv[0] = "mem";
    ptestdata->argenv[1] = "word";
    ptestdata->argenv[2] = "10";
    ptestdata->argenv[3] = "15";

    ptestdata = env_set(ptestdata);

    mu_assert("it's accepting a non-aligned address", ptestdata->report == 415);

    ptestdata->argenv[0] = "mem";
    ptestdata->argenv[1] = "word";
    ptestdata->argenv[2] = "0x3000";
    ptestdata->argenv[3] = "0xFF";

    ptestdata = env_set(ptestdata);

    mu_assert("it's writing into a segment with no writing access", ptestdata->report == 503);

    ptestdata->argenv[0] = "mem";
    ptestdata->argenv[1] = "word";
    ptestdata->argenv[2] = "0x4000";
    ptestdata->argenv[3] = "0xABCDEF12";

    ptestdata = env_set(ptestdata);

    mu_assert("it should pass here", ptestdata->report == 0);
 }



 static char * sys_test_set_reg() 
{           
    res = system("diff test/resultfiles/test_set_reg_expected.txt test/resultfiles/test_set_reg_result.txt");
       
    mu_assert("error, the set reg result file is different than expected",!res);

    return 0;
}
 static char * sys_test_set_mem_byte() //tries to execute set reg using an invalid register argument
{           
    res = system("diff test/resultfiles/test_set_mem_byte_expected.txt test/resultfiles/test_set_mem_byte_result.txt");
       
    mu_assert("error, the set mem byte result file is different than expected",!res);

    return 0;
}

 static char * sys_test_set_mem_word() //tries to execute set reg using an invalid register argument
{           
    res = system("diff test/resultfiles/test_set_mem_word_expected.txt test/resultfiles/test_set_mem_word_result.txt");
       
    mu_assert("error, the set mem word result file is different than expected",!res);
    
    return 0;
}

 static char * sys_test_disp_reg() //tries to execute set reg using an invalid register argument
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

static char * test_find_illegal_character()
{
    char *succ1 = "0x00FAFA";
    char *succ2 = "0x012322";
    char *succ3 = "032292";
    char *fail1 = "78fd78as";
    char *fail2 = "0x0GHTT";
    char *fail3 = "0x0xxx0x";
    char *fail4 = "0x0ABKKK";

    mu_assert("error, case 1 should have passed, it failed", find_illegal_character(succ1) == 0);
    mu_assert("error, case 2 should have passed, it failed", find_illegal_character(succ2) == 0);
    mu_assert("error, case 3 should have passed, it failed", find_illegal_character(succ3) == 0);
    mu_assert("error, case 4 should have failed, it passed", find_illegal_character(fail1) == 1);
    mu_assert("error, case 5 should have failed, it passed", find_illegal_character(fail2) == 1);
    mu_assert("error, case 6 should have failed, it passed", find_illegal_character(fail3) == 1);
    mu_assert("error, case 7 should have failed, it passed", find_illegal_character(fail4) == 1);

    return 0;

}
 
 
 static char * all_tests() {
    mu_run_test(test_load);
    mu_run_test(test_set_mem_byte);
    mu_run_test(test_set_mem_word);
    // mu_run_test(test_set_reg);
    // mu_run_test(test_disp_reg);

    mu_run_test(sys_test_disp_reg);
    mu_run_test(sys_test_set_reg);
    mu_run_test(sys_test_set_mem_byte);
    mu_run_test(sys_test_set_mem_word);
    mu_run_test(test_assert);
    mu_run_test(test_find_illegal_character);
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

