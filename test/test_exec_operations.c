#include "../src/headers.h"
#include "../src/errors.h"
#include "../src/operations.h"
#include "../src/elfmanager.h"
#include "minunit.h"

 int tests_run = 0; 
 struct ptype *mips;
 struct ptype mymips;
 int error;


static char * test_add()
{
	*(mips->regs[9]) = 2;
	*(mips->regs[10]) = 3;
	*(mips->regs[11]) = 0;
	*(mips->regs[12]) = 0xFFFFFFFF;
	*(mips->regs[13]) = 0x1;

	error = op_add(mips,9,10,11);
	mu_assert("add operation failed to add", *(mips->regs[11]) == 5 && error == 0);
	error = op_add(mips,12,13,11);
	mu_assert("add operation failed to return overflow exception", error == 1 && *(mips->regs[11]) == 5);
	
	return 0;
}

static char * test_addi()
{
	*(mips->regs[9]) = 2;
	*(mips->regs[11]) = 0;
	*(mips->regs[12]) = 0xFFFFFFFF;
	error = op_addi(mips,9,11,0x324F);
	mu_assert("addi operation failed to add", *(mips->regs[11]) == (2 + 0x324F));
	error = op_addi(mips,12,11,0x03);
	mu_assert("addi operation failed to return overflow exception", error == 1);
	
	return 0;
}

static char * test_addu()
{
	*(mips->regs[9]) = 2;
	*(mips->regs[10]) = 3;
	*(mips->regs[11]) = 0;
	*(mips->regs[12]) = 0xFFFFFFFF;
	*(mips->regs[13]) = 0x1;

	error = op_addu(mips,9,10,11);
	mu_assert("addu operation failed to add", *(mips->regs[11]) == 5 && error == 0);
	error = op_addu(mips,12,13,11);
	mu_assert("addu operation failed to add overflow", error == 0 && *(mips->regs[11]) == 0);
	
	return 0;
}

static char * test_addiu()
{
	*(mips->regs[9]) = 2;
	*(mips->regs[11]) = 0;
	*(mips->regs[12]) = 0xFFFFFFFF;
	error = op_addiu(mips,9,11,0x324F);
	mu_assert("addiu operation failed to add", *(mips->regs[11]) == (2 + 0x324F) && error == 0);
	error = op_addiu(mips,12,11,0x1);
	mu_assert("addiu operation failed to add overflow", error == 0 && *(mips->regs[11]) == 0);
	
	return 0;
}

static char * test_and()
{
	*(mips->regs[9]) = 0x67537F99;
	*(mips->regs[10]) = 0x47BF040B;
	*(mips->regs[11]) = 0;
	error = op_and(mips,9,10,11);
	mu_assert("and operation failed", *(mips->regs[11]) == 0x47130409 && error == 0);
	
	return 0;
}

static char * test_andi()
{
	*(mips->regs[9]) = 0x47BF040B;
	*(mips->regs[10]) = 0;
	error = op_andi(mips,9,10,0x324F);
	mu_assert("andi operation failed", *(mips->regs[10]) == (0x47BF040B & 0x324F) && error == 0);	
	return 0;
}

static char * test_beq()
{
	*(mips->regs[9]) = 0x47BF040B;
	*(mips->regs[10]) = 0x47BF040B;
	*(mips->regs[11]) = 0x4726710B;
	mips->PC = 0;
	error = op_beq(mips,10,11,16);
	mu_assert("beq operation failed", mips->PC == 0);	
	error = op_beq(mips,9,10,16);
	mu_assert("beq operation failed", mips->PC == 64);	
	return 0;
}

static char * test_bgez()
{
	*(mips->regs[9]) = -1;
	*(mips->regs[10]) = 0;
	*(mips->regs[11]) = 1;
	mips->PC = 0;
	error = op_bgez(mips,9,16);
	mu_assert("bgez 1 operation failed", mips->PC == 0);	
	error = op_bgez(mips,10,16);
	mu_assert("bgez 2 operation failed", mips->PC == 64);	
	error = op_bgez(mips,11,16);
	mu_assert("bgez 3 operation failed", mips->PC == 128);	
	return 0;
}

static char * test_bgtz()
{
	*(mips->regs[9]) = -1;
	*(mips->regs[10]) = 0;
	*(mips->regs[11]) = 1;
	mips->PC = 0;
	error = op_bgtz(mips,9,16);
	mu_assert("bgtz 1 operation failed", mips->PC == 0);	
	error = op_bgtz(mips,10,16);
	mu_assert("bgtz 2 operation failed", mips->PC == 0);	
	error = op_bgtz(mips,11,16);
	mu_assert("bgtz 3 operation failed", mips->PC == 64);	
	return 0;
}

static char * test_blez()
{
	*(mips->regs[9]) = 1;
	*(mips->regs[10]) = 0;
	*(mips->regs[11]) = -1;
	mips->PC = 0;
	error = op_blez(mips,9,16);
	mu_assert("blez 1 operation failed", mips->PC == 0);	
	error = op_blez(mips,10,16);
	mu_assert("blez 2 operation failed", mips->PC == 64);	
	error = op_blez(mips,11,16);
	mu_assert("blez 3 operation failed", mips->PC == 128);	
	return 0;
}

static char * test_bltz()
{
	*(mips->regs[9]) = 1;
	*(mips->regs[10]) = 0;
	*(mips->regs[11]) = -1;
	mips->PC = 0;
	error = op_bltz(mips,9,16);
	mu_assert("bltz 1 operation failed", mips->PC == 0);	
	error = op_bltz(mips,10,16);
	mu_assert("bltz 2 operation failed", mips->PC == 0);	
	error = op_bltz(mips,11,16);
	mu_assert("bltz 3 operation failed", mips->PC == 64);	
	return 0;
}

static char * test_bne()
{
	*(mips->regs[9]) = 0x47BF040B;
	*(mips->regs[10]) = 0x47BF040B;
	*(mips->regs[11]) = 0x4726710B;
	mips->PC = 0;
	error = op_bne(mips,9,10,16);
	mu_assert("bne operation failed", mips->PC == 0);	
	error = op_bne(mips,10,11,16);
	mu_assert("bne operation failed", mips->PC == 64);	
	return 0;
}

static char * test_div()
{
	*(mips->regs[9]) = 10;
	*(mips->regs[10]) = 3;
	*(mips->regs[11]) = 0;
	error = op_div(mips,9,10);
	mu_assert("div operation failed to div", *(mips->lo) == 10/3 && error == 0);
	error = op_div(mips,9,11);
	mu_assert("div operation failed to return div by 0 exception", error == 10);
	
	return 0;
}

static char * test_j()
{	
	mips->PC = 0x90003000;
	error = op_j(mips,0x000032FF);
	mu_assert("jump operation failed to jump", mips->PC == 0x9000CBFC);
	
	return 0;
}

static char * test_jal()
{	
	mips->PC = 0x90003000;
	error = op_jal(mips,0x000032FF);
	mu_assert("jump and link operation failed to store return address",*(mips->regs[31]) == 0x90003008);
	mu_assert("jump and link operation failed to jump", mips->PC == 0x9000CBFC);
	
	return 0;
}

static char * test_jalr()
{	
	*(mips->regs[9]) = 0x9000CBFC;
	*(mips->regs[10]) = 0;
	mips->PC = 0x90003000;
	error = op_jalr(mips,9,10);
	mu_assert("jalr operation failed to store return address",*(mips->regs[31]) == 0x90003008);
	mu_assert("jalr operation failed to jump", mips->PC == 0x9000CBFC);
	*(mips->regs[9]) = 0x9000CBFF;
	error = op_jalr(mips,9,10);
	mu_assert("jalr operation failed to return unaligned", error == 20);
	
	return 0;
}

static char * test_jr()
{	
	mips->PC = 0x90003000;
	*(mips->regs[9]) = 0x9000CBFC;
	error = op_jr(mips,9);
	mu_assert("jr operation failed to jump", mips->PC == 0x9000CBFC);
	*(mips->regs[9]) = 0x9000CBFF;
	error = op_jr(mips,9);
	mu_assert("jr operation failed to return unaligned", error == 21);
	
	return 0;
}


static char * test_lb()
{	
	struct elfstr myelfdata;
    mips->elfdata = &myelfdata;
    mips->elfdata = start_and_load(mips->elfdata, "test/test_elf.o", 0x3000);
    mu_assert("the file does not exist or the path is incorrect", mips->elfdata->report != 100);
    mu_assert("file entered isn't ELF", mips->elfdata->report != 101);


	*(mips->regs[9]) = 0x3000;
	*(mips->regs[10]) = 0x4000;
	error = op_lb(mips,9,10,7);

	mu_assert("lb operation returned read null", error != 30);
	mu_assert("lb operation returned no segment associated", error != 31);
	mu_assert("lb operation failed", *(mips->regs[10]) == 0x20);

	del_mem(mips->elfdata->memory);
    del_stab(mips->elfdata->symtab);
    fclose(mips->elfdata->pf_elf);

	return 0;
}

static char * test_lbu()
{	
	struct elfstr myelfdata;
    mips->elfdata = &myelfdata;
    mips->elfdata = start_and_load(mips->elfdata, "test/test_elf.o", 0x3000);
    mu_assert("the file does not exist or the path is incorrect", mips->elfdata->report != 100);
    mu_assert("file entered isn't ELF", mips->elfdata->report != 101);


	*(mips->regs[9]) = 0x3000;
	*(mips->regs[10]) = 0x4000;
	error = op_lbu(mips,9,10,7);

	mu_assert("lbu operation returned read null", error != 30);
	mu_assert("lbu operation returned no segment associated", error != 31);
	mu_assert("lbu operation failed", *(mips->regs[10]) == 0x20);
	
	del_mem(mips->elfdata->memory);
    del_stab(mips->elfdata->symtab);
    fclose(mips->elfdata->pf_elf);

	return 0;
}

static char * test_lui()
{	
	*(mips->regs[9]) = 0x3000;
	error = op_lui(mips,9,0xFEFE);
	mu_assert("lui operation failed", *(mips->regs[9]) == 0xFEFE0000);

	return 0;
}

static char * test_lw()
{	
	struct elfstr myelfdata;
    mips->elfdata = &myelfdata;
    mips->elfdata = start_and_load(mips->elfdata, "test/test_elf.o", 0x3000);
    mu_assert("the file does not exist or the path is incorrect", mips->elfdata->report != 100);
    mu_assert("file entered isn't ELF", mips->elfdata->report != 101);


	*(mips->regs[9]) = 0x3000;
	*(mips->regs[10]) = 0x4000;
	error = op_lw(mips,9,10,8);
	mu_assert("lw operation returned read null", error != 30);
	mu_assert("lw operation returned no segment associated", error != 31);
	mu_assert("lw operation failed", *(mips->regs[10]) == 0x214a0001);

	error = op_lw(mips,9,10,7);
	mu_assert("lw operation should return address not aligned", error == 50);
	
	del_mem(mips->elfdata->memory);
    del_stab(mips->elfdata->symtab);
    fclose(mips->elfdata->pf_elf);

	return 0;
}

static char * test_mfhi()
{	
	*(mips->hi) = 4;
	*(mips->regs[9]) = 10;
	error = op_mfhi(mips, 9);
	mu_assert("mfhi operation failed",*(mips->regs[9]) == 4);	
	return 0;
}

static char * test_mflo()
{	
	*(mips->lo) = 4;
	*(mips->regs[9]) = 10;
	error = op_mflo(mips, 9);
	mu_assert("mflo operation failed",*(mips->regs[9]) == 4);	
	return 0;
}


static char * test_mult()
{
	*(mips->regs[9]) = 0xABF569FA;
	*(mips->regs[10]) = 0xABAFF543;
	error = op_mult(mips,9,10);
	mu_assert("mult operation failed to mult. lo is wrong", *(mips->lo) == 0x4F8CFE6E && error == 0);
	mu_assert("mult operation failed to mult. hi is wrong", *(mips->hi) == 0x73531F4C && error == 0);
	
	return 0;
}

static char * test_nop()
{
	error = op_nop(mips);
	mu_assert("nop operation failed",error == 0);	
	return 0;
}

static char * test_or()
{
	*(mips->regs[9]) = 0x67537F99;
	*(mips->regs[10]) = 0x47BF040B;
	*(mips->regs[11]) = 0;
	error = op_or(mips,9,10,11);
	mu_assert("or operation failed", *(mips->regs[11]) == 0x67FF7F9B && error == 0);
	
	return 0;
}

static char * test_ori()
{
	*(mips->regs[9]) = 0x47BF040B;
	*(mips->regs[10]) = 0;
	error = op_ori(mips,9,10,0x324F);
	mu_assert("ori operation failed", *(mips->regs[10]) == (0x47BF040B | 0x324F) && error == 0);	
	return 0;
}

static char * test_sb()
{	
	struct elfstr myelfdata;
    mips->elfdata = &myelfdata;
    mips->elfdata = start_and_load(mips->elfdata, "test/test_elf.o", 0x3000);
    mu_assert("the file does not exist or the path is incorrect", mips->elfdata->report != 100);
    mu_assert("file entered isn't ELF", mips->elfdata->report != 101);


	*(mips->regs[9]) = 0x4000;
	*(mips->regs[10]) = 0xFE;
	error = op_sb(mips,9,10,3);
	mu_assert("sb operation returned read null", error != 60);
	mu_assert("sb operation returned no segment associated", error != 61);
	mu_assert("sb operation returned no writing allowed", error != 62);
	mips = elfreadbyte(mips, mips->elfdata->memory, 0x4003);
	mu_assert("sb operation failed", mips->bdata == 0xFE);

	del_mem(mips->elfdata->memory);
    del_stab(mips->elfdata->symtab);
    fclose(mips->elfdata->pf_elf);

	return 0;
}

static char * test_seb()
{
	*(mips->regs[9]) = 0x47BF040B;
	*(mips->regs[10]) = -7;
	*(mips->regs[11]) = 0;
	error = op_seb(mips,9,11);
	mu_assert("seb operation failed to extend positive", *(mips->regs[11]) == 0x0000000B && error == 0);	
	error = op_seb(mips,10,11);
	mu_assert("seb operation failed to extend negative", *(mips->regs[11]) == 0xFFFFFFF9 && error == 0);	
	return 0;
}

static char * test_sll()
{
	*(mips->regs[9]) = 0xFF;
	*(mips->regs[10]) = 0;
	error = op_sll(mips,9,10,2);
	mu_assert("sll operation failed", *(mips->regs[10]) == 0x03FC && error == 0);
	
	return 0;
}

static char * test_slt()
{
	*(mips->regs[9]) = 8;
	*(mips->regs[10]) = 7;
	*(mips->regs[12]) = -2;
	*(mips->regs[13]) = 4;
	*(mips->regs[14]) = -2;
	*(mips->regs[15]) = -8;
	*(mips->regs[11]) = 0;
	error = op_slt(mips,9,10,11);
	mu_assert("slt 1 operation failed", *(mips->regs[11]) == 0 && error == 0);
	error = op_slt(mips,12,13,11);
	mu_assert("slt 2 operation failed", *(mips->regs[11]) == 1 && error == 0);
	error = op_slt(mips,14,15,11);
	mu_assert("slt 3 operation failed", *(mips->regs[11]) == 0 && error == 0);
	
	return 0;
}

static char * test_slti()
{
	*(mips->regs[9]) = 23;
	*(mips->regs[10]) = -40;
	*(mips->regs[11]) = 0;
	error = op_slti(mips,9,11,20);
	mu_assert("slti 1 operation failed", *(mips->regs[11]) == 0 && error == 0);	
	error = op_slti(mips,10,11,20);
	mu_assert("slti 2 operation failed", *(mips->regs[11]) == 1 && error == 0);	
	return 0;
}

static char * test_sltu()
{
	*(mips->regs[9]) = 7;
	*(mips->regs[10]) = 8;
	*(mips->regs[12]) = 0xFFFFFFF3;
	*(mips->regs[13]) = 0x0000000F;
	*(mips->regs[11]) = 0;
	error = op_sltu(mips,9,10,11);
	mu_assert("sltu 1 operation failed", *(mips->regs[11]) == 1 && error == 0);
	error = op_sltu(mips,12,13,11);
	mu_assert("sltu 2 operation failed", *(mips->regs[11]) == 0 && error == 0);
	
	return 0;
}

static char * test_sltiu()
{
	*(mips->regs[9]) = 0xA;
	*(mips->regs[10]) = 0xFFFFFFF3;
	*(mips->regs[11]) = 0;
	error = op_sltiu(mips,9,11,0xE);
	mu_assert("sltiu 1 operation failed", *(mips->regs[11]) == 1 && error == 0);	
	error = op_sltiu(mips,10,11,20);
	mu_assert("sltiu 2 operation failed", *(mips->regs[11]) == 0 && error == 0);	
	return 0;
}

static char * test_sra()
{
	*(mips->regs[9]) = 0xFE000000;
	*(mips->regs[10]) = 0;
	error = op_sra(mips,9,10,8);
	mu_assert("sra operation failed", *(mips->regs[10]) == 0xFFFE0000 && error == 0);
	
	return 0;
}

static char * test_srl()
{
	*(mips->regs[9]) = 0xFE000000;
	*(mips->regs[10]) = 0;
	error = op_srl(mips,9,10,8);
	mu_assert("srl operation failed", *(mips->regs[10]) == 0x00FE0000 && error == 0);
	
	return 0;
}

static char * test_sub()
{
	*(mips->regs[9]) = 7;
	*(mips->regs[10]) = 3;
	*(mips->regs[13]) = 0xFFFFFFFA;
	*(mips->regs[12]) = 0x00000007;
	*(mips->regs[11]) = 0;

	error = op_sub(mips,9,10,11);
	mu_assert("sub operation returned overflow exception",  error == 0);
	mu_assert("sub operation failed to sub", *(mips->regs[11]) == 4);
	error = op_sub(mips,12,13,11);
	printf("%d\n", *(mips->regs[11]));
	mu_assert("sub operation failed to return overflow exception", error == 1);
	mu_assert("sub operation failed to keep original value", *(mips->regs[11]) == 4);
	
	return 0;
}

static char * test_subu()
{
	*(mips->regs[9]) = 7;
	*(mips->regs[10]) = 3;
	*(mips->regs[12]) = 0x0;
	*(mips->regs[13]) = 0x1;
	*(mips->regs[11]) = 0;

	error = op_subu(mips,9,10,11);
	mu_assert("subu 1 operation failed to substract", *(mips->regs[11]) == 4 && error == 0);
	error = op_subu(mips,12,13,11);
	mu_assert("subu 2 operation failed to substract", *(mips->regs[11]) == 0xFFFFFFFF && error == 0);
	
	return 0;
}

static char * test_sw()
{	
	struct elfstr myelfdata;
    mips->elfdata = &myelfdata;
    mips->elfdata = start_and_load(mips->elfdata, "test/test_elf.o", 0x3000);
    mu_assert("the file does not exist or the path is incorrect", mips->elfdata->report != 100);
    mu_assert("file entered isn't ELF", mips->elfdata->report != 101);


	*(mips->regs[9]) = 0x4000;
	*(mips->regs[10]) = 0xFEFEABAB;
	error = op_sw(mips,9,10,0);
	mu_assert("sw operation returned no aligned address", error != 73);
	mu_assert("sw operation returned read null", error != 70);
	mu_assert("sw operation returned no segment associated", error != 71);
	mu_assert("sw operation returned no writing allowed", error != 72);
	mips = elfreadword(mips, mips->elfdata->memory, 0x4000);
	mu_assert("sw operation failed", mips->wdata == 0xFEFEABAB);

	error = op_sw(mips,9,10,3);
	mu_assert("sw operation should return not aligned address", error == 73);


	del_mem(mips->elfdata->memory);
    del_stab(mips->elfdata->symtab);
    fclose(mips->elfdata->pf_elf);

	return 0;
}

static char * test_xor()
{
	*(mips->regs[9]) = 0x67537F99;
	*(mips->regs[10]) = 0x47BF040B;
	*(mips->regs[11]) = 0;
	error = op_xor(mips,9,10,11);
	mu_assert("xor operation failed", *(mips->regs[11]) == 0x20EC7B92 && error == 0);
	
	return 0;
}


 static char * all_tests() {

    mu_run_test(test_add);
    mu_run_test(test_addi);
    mu_run_test(test_addu);
    mu_run_test(test_addiu);
    mu_run_test(test_and);
    mu_run_test(test_andi);
    mu_run_test(test_beq);
    mu_run_test(test_bgez);
    mu_run_test(test_bgtz);
    mu_run_test(test_blez);
    mu_run_test(test_bltz);
    mu_run_test(test_bne);
    mu_run_test(test_nop);
    mu_run_test(test_div);
    mu_run_test(test_j);
    mu_run_test(test_jal);
    mu_run_test(test_jalr);
    mu_run_test(test_jr);
    mu_run_test(test_lb);
    mu_run_test(test_lbu);
    mu_run_test(test_lui);
    mu_run_test(test_lw);
    mu_run_test(test_mfhi);
    mu_run_test(test_mult);
    mu_run_test(test_or);
    mu_run_test(test_ori);
    mu_run_test(test_sb);
    mu_run_test(test_seb);
    mu_run_test(test_sll);
    mu_run_test(test_slt);
    mu_run_test(test_slti);
    mu_run_test(test_sltu);
    mu_run_test(test_sltiu);
    mu_run_test(test_sra);
    mu_run_test(test_srl);
    // mu_run_test(test_sub);
    mu_run_test(test_subu);
    mu_run_test(test_sw);
    mu_run_test(test_xor);

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