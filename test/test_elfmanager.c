#include "../src/headers.h"
#include "../src/memorymanagement.h"
#include "../elfapi/include/elf/syms.h"
#include "../elfapi/include/mem.h"
#include "../src/elfmanager.h"
#include "../src/lookup.h"
#include "minunit.h"

int tests_run = 0;
struct ptype mips;
struct ptype *pmips;


int simpoint;
 
 static char * test_creatememory() 
{
	char *filename = "test/test_elf.o";

	struct elfstr *elfdata;

	elfdata = start_and_load(elfdata, filename);
	segment *seg;
	char name[] = ".text";

	seg = get_seg_by_name(elfdata->memory, name);
	mu_assert("get segment by name incorrect.", !strcmp(seg->name,".text"));

	char name2[] = ".data";

	seg = get_seg_by_name(elfdata->memory, name2);
	mu_assert("get segment by name incorrect.", !strcmp(seg->name,".data"));


	mu_assert("is in segment data failed %d\n", is_in_segment(elfdata->memory, seg, 0x4000));
	mu_assert("is in segment data failed %d\n", is_in_segment(elfdata->memory, seg, 0x4002));
	mu_assert("is in segment data failed %d\n", !is_in_segment(elfdata->memory, seg, 0x4004));

	seg = which_seg(elfdata->memory, 0x3003);
	mu_assert("which_seg failed, should be .text", !strcmp(seg->name,".text"));
	seg = which_seg(elfdata->memory, 0x3000);
	mu_assert("which_seg failed, should be .text", !strcmp(seg->name,".text"));
	seg = which_seg(elfdata->memory, 0x3060);
	mu_assert("which_seg failed, should be null", seg == NULL);
	seg = which_seg(elfdata->memory, 0x4000);
	mu_assert("which_seg failed, should be .data", !strcmp(seg->name,".data"));

	// printf("\n------ Fichier ELF \"%s\" : sections lues lors du chargement ------\n", filename) ;
 //    print_mem(elfdata->memory);
 //    stab32_print( elfdata->symtab);

 	destroy_mem(elfdata);
	return 0;
}

 static char * test_writememory()
 {
 	struct ptype *mips = malloc(sizeof(mips));
 	char *filename = "test/test_elf.o";

	struct elfstr *elfdata;

	elfdata = start_and_load(elfdata, filename);

	vaddr32 addr = 0x1234;
	byte bdata = 0xEF;

	elfwritebyte(mips, elfdata->memory, bdata, addr);

 	return 0;
 } 

 
 static char * all_tests() {
     mu_run_test(test_creatememory);
     // mu_run_test(test_writememory);
     return 0;
 }
 
 int main(int argc, char **argv) {

 	pmips = &mips;

	char *result = all_tests();
	if (result != 0) {
	 printf("%s\n", result);
	}
	else {
	 // printf("PARSING TEST 3 PASSED\n");
	}
	// printf("Tests run: %d\n", tests_run);

	return result != 0;
 }