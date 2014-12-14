#include "../src/headers.h"
#include "../src/errors.h"
#include "../src/operations.h"
#include "minunit.h"

 int tests_run = 0; 
 struct mipsstr *mips;
 struct mipsstr mymips;

static char * test_all()
{
	mips->disasm_output = malloc(200);

	mips = print_add(mips,9,10,11);
	mu_assert("print_add failed", !strcmp(mips->disasm_output, "ADD $t3, $t1, $t2"));
	mips = print_addi(mips,9,11,0x324F);
	mu_assert("print_addi failed", !strcmp(mips->disasm_output, "ADDI $t3, $t1, 0x324f"));
	mips = print_addu(mips,9,10,11);
	mu_assert("print_addu failed", !strcmp(mips->disasm_output, "ADDU $t3, $t1, $t2"));
	mips = print_addiu(mips,9,11,0x324F);
	mu_assert("print_addiu failed", !strcmp(mips->disasm_output, "ADDIU $t3, $t1, 0x324f"));
	mips = print_and(mips,9,10,11);
	mu_assert("print_and failed", !strcmp(mips->disasm_output, "AND $t3, $t1, $t2"));	
	mips = print_andi(mips,9,11,0x324F);
	mu_assert("print_andi failed", !strcmp(mips->disasm_output, "ANDI $t3, $t1, 0x324f"));
	mips = print_beq(mips,9,11,0x324F);
	mu_assert("print_beq failed", !strcmp(mips->disasm_output, "BEQ $t1, $t3, 0xc940"));
	mips = print_bgez(mips,9,0x324F);
	mu_assert("print_bgez failed", !strcmp(mips->disasm_output, "BGEZ $t1, 0xc940"));	
	mips = print_bgtz(mips,9,0x324F);
	mu_assert("print_bgtz failed", !strcmp(mips->disasm_output, "BGTZ $t1, 0xc940"));	
	mips = print_blez(mips,9,0x324F);
	mu_assert("print_blez failed", !strcmp(mips->disasm_output, "BLEZ $t1, 0xc940"));	
	mips = print_bltz(mips,9,0x324F);
	mu_assert("print_bltz failed", !strcmp(mips->disasm_output, "BLTZ $t1, 0xc940"));	
	mips = print_bne(mips,9,11,0x324F);
	mu_assert("print_bne failed", !strcmp(mips->disasm_output, "BNE $t1, $t3, 0xc940"));
	mips = print_div(mips,9,10);
	mu_assert("print_div failed", !strcmp(mips->disasm_output, "DIV $t1, $t2"));
	mips = print_j(mips,0x2FA2837E);
	mu_assert("print_j failed", !strcmp(mips->disasm_output, "J 0xbe8a0df8"));	
	mips = print_jal(mips,0x2FA2837E);
	mu_assert("print_jal failed", !strcmp(mips->disasm_output, "JAL 0xbe8a0df8"));	
	mips = print_jalr(mips, 9, 10);
	mu_assert("print_jalr failed", !strcmp(mips->disasm_output, "JALR $t2, $t1"));	
	mips = print_jr(mips, 9);
	mu_assert("print_jr failed", !strcmp(mips->disasm_output, "JR $t1"));	
	mips = print_lb(mips, 9, 10, 100);
	mu_assert("print_lb failed", !strcmp(mips->disasm_output, "LB $t2, 100($t1)"));	
	mips = print_lbu(mips, 9, 10, 100);
	mu_assert("print_lbu failed", !strcmp(mips->disasm_output, "LBU $t2, 100($t1)"));	
	mips = print_lui(mips,10, 0x1234);
	mu_assert("print_lui failed", !strcmp(mips->disasm_output, "LUI $t2, 1234"));	
	mips = print_lw(mips, 9, 10, 100);
	mu_assert("print_lw failed", !strcmp(mips->disasm_output, "LW $t2, 100($t1)"));	
	mips = print_mfhi(mips,9);
	mu_assert("print_mfhi failed", !strcmp(mips->disasm_output, "MFHI $t1"));
	mips = print_mflo(mips,9);
	mu_assert("print_mflo failed", !strcmp(mips->disasm_output, "MFLO $t1"));
	mips = print_mult(mips,9,10);
	mu_assert("print_mult failed", !strcmp(mips->disasm_output, "MULT $t1, $t2"));
	mips = print_nop(mips);
	mu_assert("print_nop failed", !strcmp(mips->disasm_output, "NOP"));
	mips = print_or(mips,9,10,11);
	mu_assert("print_or failed", !strcmp(mips->disasm_output, "OR $t3, $t1, $t2"));	
	mips = print_ori(mips,9,11,0x324F);
	mu_assert("print_ori failed", !strcmp(mips->disasm_output, "ORI $t3, $t1, 0x324f"));
	mips = print_sb(mips, 9, 10, 100);
	mu_assert("print_sb failed", !strcmp(mips->disasm_output, "SB $t2, 100($t1)"));	
	mips = print_seb(mips,9,10);
	mu_assert("print_seb failed", !strcmp(mips->disasm_output, "SEB $t2, $t1"));
	mips = print_sll(mips,9,10,3);
	mu_assert("print_sll failed", !strcmp(mips->disasm_output, "SLL $t2, $t1, 3"));
	mips = print_slt(mips,9,10,11);
	mu_assert("print_slt failed", !strcmp(mips->disasm_output, "SLT $t3, $t1, $t2"));
	mips = print_slti(mips,9,10,11);
	mu_assert("print_slti failed", !strcmp(mips->disasm_output, "SLTI $t2, $t1, 0xb"));
	mips = print_sltu(mips,9,10,11);
	mu_assert("print_sltu failed", !strcmp(mips->disasm_output, "SLTU $t3, $t1, $t2"));
	mips = print_sltiu(mips,9,10,11);
	mu_assert("print_sltiu failed", !strcmp(mips->disasm_output, "SLTIU $t2, $t1, 0xb"));
	mips = print_sra(mips,9,10,3);
	mu_assert("print_sra failed", !strcmp(mips->disasm_output, "SRA $t2, $t1, 3"));
	mips = print_srl(mips,9,10,3);
	mu_assert("print_srl failed", !strcmp(mips->disasm_output, "SRL $t2, $t1, 3"));
	mips = print_sub(mips,9,10,11);
	mu_assert("print_sub failed", !strcmp(mips->disasm_output, "SUB $t3, $t1, $t2"));
	mips = print_subu(mips,9,10,11);
	mu_assert("print_subu failed", !strcmp(mips->disasm_output, "SUBU $t3, $t1, $t2"));
	mips = print_sw(mips, 9, 10, 100);
	mu_assert("print_sw failed", !strcmp(mips->disasm_output, "SW $t2, 100($t1)"));	
	mips = print_xor(mips,9,10,11);
	mu_assert("print_xor failed", !strcmp(mips->disasm_output, "XOR $t3, $t1, $t2"));
	// printf("%s\n",mips->disasm_output);
	
	free(mips->disasm_output);

	return 0;
}

 static char * all_tests() {

    mu_run_test(test_all);


	return 0;

 }
 
 int main(int argc, char **argv) {

 	mips = &mymips;
 	// mips = malloc(sizeof(mips));

 	int i;
	for(i = 0; i < 32; i++)
	{
		mips->regs[i] = malloc( sizeof(int) );
		*(mips->regs[i]) = 0;
	}

	mips->hi = malloc(sizeof(int));
	*(mips->hi) = 0;
	mips->lo = malloc(sizeof(int));
	*(mips->lo) = 0;

	*(mips->regs[9]) = 2;
	*(mips->regs[10]) = 3;
	*(mips->regs[12]) = 0xFFFFFFFF;
	*(mips->regs[13]) = 0x1;

    char *result = all_tests();

    if (result != 0) {
     printf("%s\n", result);
    }
    else {
      // printf("TEST PASSED\n");
    }
    // printf("Tests run: %d\n", tests_run);


    for(i = 0; i < 32; i++)
	{
		free(mips->regs[i]);
	}

	free(mips->hi);
	free(mips->lo);

    // free(mips);
    return result != 0;
}