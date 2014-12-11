#include "../src/headers.h"
#include "../src/environmentcommands.h"
#include "../src/disassembler.h"
#include "minunit.h"

int tests_run = 0; 
int res;
struct mipsstr testdata;
struct mipsstr *mips;
struct elfstr myelfstr;


 static char * test_load() 
{           
    mips->elfdata = &myelfstr;
    mips->argenv[0] = "./test/test_elf.o";
    mips->argenv[1] = "0x3000";
    mips->n_argenv = 2;

    dup2(fileno(stdout), fileno(stderr));
    mips = env_load(mips);

    mu_assert("hay error en env_load", mips->report == 0);

    // res = system("diff test/resultfiles/test_load_expected.txt test/resultfiles/test_load_result.txt");

    // mu_assert("error, the load result file is different than expected",!res);

    return 0;
}
 static char * test_set_mem_byte() 
{
    mips->n_argenv = 4;

    mips->argenv[0] = "mem";
    mips->argenv[1] = "byte";
    mips->argenv[2] = "10";
    mips->argenv[3] = "15";

    mips = env_set(mips);

    mu_assert("deberia haber error 501 pero no hay", mips->report == 501);

    mips->argenv[0] = "mem";
    mips->argenv[1] = "byte";
    mips->argenv[2] = "0x3000";
    mips->argenv[3] = "0xFF";

    mips = env_set(mips);

    mu_assert("deberia haber error 503 pero no hay", mips->report == 503);

    mips->argenv[0] = "mem";
    mips->argenv[1] = "byte";
    mips->argenv[2] = "0x4001";
    mips->argenv[3] = "0xFF";

    mips = env_set(mips);

    mu_assert("no deberia haber errores", mips->report == 0);

    return 0;
}

 static char * test_set_mem_word()
 {
    mips->n_argenv = 4;

    mips->argenv[0] = "mem";
    mips->argenv[1] = "word";
    mips->argenv[2] = "10";
    mips->argenv[3] = "15";

    mips = env_set(mips);

    mu_assert("it's accepting a non-aligned address", mips->report == 415);

    mips->argenv[0] = "mem";
    mips->argenv[1] = "word";
    mips->argenv[2] = "0x3000";
    mips->argenv[3] = "0xFF";

    mips = env_set(mips);

    mu_assert("it's writing into a segment with no writing access", mips->report == 503);

    mips->argenv[0] = "mem";
    mips->argenv[1] = "word";
    mips->argenv[2] = "0x4000";
    mips->argenv[3] = "0xABCDEF12";

    mips = env_set(mips);

    mu_assert("it should pass here", mips->report == 0);
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

 static char * test_disasm() //tries to execute set reg using an invalid register argument
{           
    res = system("diff test/resultfiles/test_disasm_expected.txt test/resultfiles/test_disasm_result.txt");
       
    mu_assert("error, the disasm result file is different than expected",!res);
    
    return 0;
}

 static char * test_break() //tries to execute set reg using an invalid register argument
{           
    res = system("diff test/resultfiles/test_break_expected.txt test/resultfiles/test_break_result.txt");
       
    mu_assert("error, the break result file is different than expected",!res);
    
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
    mu_run_test(test_disasm);
    mu_run_test(test_break);
    mu_run_test(test_find_illegal_character);
     return 0;

 }
 
 int main(int argc, char **argv) {

    mips = (struct mipsstr *) malloc(sizeof(struct mipsstr));

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

