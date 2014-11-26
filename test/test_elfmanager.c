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
	mem memory;  // memoire virtuelle, c'est elle qui contiendra toute les données du programme
    stab symtab; // table des symboles
    FILE * pf_elf;

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


	// struct nlist *np;
 
 	// pmips = my_init_mem(pmips, filename);

/* 	mu_assert("memory total size error",pmips->memsize == 12312);

 	np = lookup("SEGSIZE_.text");
 	if(np != NULL)
 	mu_assert("segment text's size error", !strcmp(np->defn, "24"));
 	np = lookup("SEGPERM_.text");
 	if(np != NULL)
 	mu_assert("segment text's permissions error", !strcmp(np->defn, "3"));
 	np = lookup("SEGSTART_.text");
 	if(np != NULL)
 	mu_assert("segment text's start address error", !strcmp(np->defn, "3000"));

 	np = lookup("SEGSIZE_.data");
 	if(np != NULL)
 	mu_assert("segment data's size error", !strcmp(np->defn, "4"));
 	np = lookup("SEGPERM_.data");
 	if(np != NULL)
 	mu_assert("segment data's permissions error", !strcmp(np->defn, "2"));
 	np = lookup("SEGSTART_.data");
 	if(np != NULL)
 	mu_assert("segment data's start address error", !strcmp(np->defn, "4000"));

 	np = lookup("SEGSIZE_.bss");
 	if(np != NULL)
 	mu_assert("segment bss's size error", !strcmp(np->defn, "0"));
 	np = lookup("SEGPERM_.bss");
 	if(np != NULL)
 	mu_assert("segment bss's permissions error", !strcmp(np->defn, "2"));
 	np = lookup("SEGSTART_.bss");
 	if(np != NULL)
 	mu_assert("segment bss's start address error", !strcmp(np->defn, "5000"));
*/
 	// printf("%d\n", pmips->report);

 	// mu_assert("np is null", np != NULL);

 	// pmips = displaymemory(pmips);

 	// pmips = destroymemory(pmips);
	return 0;
}
 
 static char * all_tests() {
     mu_run_test(test_creatememory);
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