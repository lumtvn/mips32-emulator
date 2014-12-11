#include "../src/headers.h"
#include "../src/elfmanager.h"
#include "minunit.h"

int tests_run = 0;


 
 static char * test_start_and_load() 
{
	char *filename = "test/test_elf.o";

	struct elfstr *elfdata = (struct elfstr *) malloc(sizeof(struct elfstr));
	if (elfdata == NULL){printf("no memory for structure elfdata\n"); mu_assert("",0);}

	elfdata = start_and_load(elfdata, filename, 0x3000);

	segment *seg;
	char name[] = ".text";
// BORRAR VARIABLES NAME Y NAME2 Y REEMPLAZAR CON TEXTO DIRECTAMENTE
	seg = get_seg_by_name(elfdata->memory, name);
	mu_assert("get segment by name incorrect.", !strcmp(seg->name,".text"));
	mu_assert("is in segment text failed \n", is_in_segment(seg, 0x3017, 1));

	char name2[] = ".data";

	seg = get_seg_by_name(elfdata->memory, name2);
	mu_assert("get segment by name incorrect.", !strcmp(seg->name,".data"));


	mu_assert("is in segment data failed 1 \n", is_in_segment(seg, 0x4002, 1));
	mu_assert("is in segment data failed 2 \n", !is_in_segment(seg, 0x4004, 2));

	seg = which_seg(elfdata->memory, 0x3017, 1);
	if(seg == NULL){printf("seg is null 1\n"); mu_assert("", 0);}
	mu_assert("which_seg failed, should be .text 1", !strcmp(seg->name,".text"));
	seg = which_seg(elfdata->memory, 0x3000, 2);
	if(seg == NULL){printf("seg is null 2\n"); mu_assert("", 0);}
	mu_assert("which_seg failed, should be .text 2", !strcmp(seg->name,".text"));
	seg = which_seg(elfdata->memory, 0x3060, 12);
	mu_assert("which_seg failed, should be null", seg == NULL);
	seg = which_seg(elfdata->memory, 0x4000, 3);
	if(seg == NULL){printf("seg is null 3\n"); mu_assert("", 0);}
	mu_assert("which_seg failed, should be .data", !strcmp(seg->name,".data"));

	// printf("\n------ Fichier ELF \"%s\" : sections lues lors du chargement ------\n", filename) ;
 //    print_mem(elfdata->memory);
 //    stab32_print( elfdata->symtab);

 	destroy_mem(elfdata);
 	free(elfdata);

	return 0;
}


static char * test_writebytememory()
{
	char *filename = "test/test_elf.o";

	struct elfstr myelfstr; 
	struct elfstr *elfdata = &myelfstr;
	if (elfdata == NULL){printf("no memory for structure elfdata\n"); mu_assert("",0);}

	elfdata = start_and_load(elfdata, filename, 0x3000);

	struct mipsstr mymips;
	struct mipsstr *mips = &mymips;

	byte data = 0xAA;
	vaddr32 addr = 0x4002;

	mips = elfwritebyte(mips, elfdata->memory, data, addr);

	mu_assert("address not assigned to any segment", mips->report != 501);
	mu_assert("seg->content is null", mips->report != 502);

	mu_assert("there was a problem in writing byte", mips->report == 0);

	segment *seg = get_seg_by_name(elfdata->memory, ".data");
	mu_assert("writing incorrect", *(seg->content + addr - seg->start._32) == data);

	addr = 0x3002;
	mips = elfwritebyte(mips, elfdata->memory, data, addr);
	mu_assert("writing was allowed when it shouln't", mips->report == 503);

	// print_segment_raw_content(seg);


	return 0;

} 

static char * test_writewordmemory()
{
	char *filename = "test/test_elf.o";

	struct elfstr myelfstr; 
	struct elfstr *elfdata = &myelfstr;
	if (elfdata == NULL){printf("no memory for structure elfdata\n"); mu_assert("",0);}

	elfdata = start_and_load(elfdata, filename, 0x3000);

	struct mipsstr mymips;
	struct mipsstr *mips = &mymips;

	word data = 0xAABBCCDD;
	vaddr32 addr = 0x4001;
	mips = elfwriteword(mips, elfdata->memory, data, addr);
	mu_assert("its trying to write in addess out of bounds", mips->report == 501);

	addr = 0x3000;
	mips = elfwriteword(mips, elfdata->memory, data, addr);
	mu_assert("its trying to write in addres without writing permissions", mips->report == 503);

	addr = 0x4000;
	mips = elfwriteword(mips, elfdata->memory, data, addr);

	mu_assert("address not assigned to any segment or writing overruns end of section", mips->report != 501);
	mu_assert("seg->content is null", mips->report != 2);

	mu_assert("there was a problem in writing", mips->report == 0);

	segment *seg = get_seg_by_name(elfdata->memory, ".data");

	// printf("0x%x", *(seg->content + addr - seg->start._32));
	// printf("%x", *(seg->content + addr - seg->start._32+1));
	// printf("%x", *(seg->content + addr - seg->start._32+2));
	// printf("%x\n", *(seg->content + addr - seg->start._32+3));

	mu_assert("fourth byte writing incorrect", *(seg->content + addr - seg->start._32 + 3) == 0xDD);
	mu_assert("third byte writing incorrect", *(seg->content + addr - seg->start._32 + 2) == 0xCC);
	mu_assert("second byte writing incorrect", *(seg->content + addr - seg->start._32 + 1) == 0xBB);
	mu_assert("first byte writing incorrect", *(seg->content + addr - seg->start._32) == 0xAA);

	 // print_segment_raw_content(seg);


	return 0;

} 

static char * test_readbytememory()
{
	char *filename = "test/test_elf.o";

	struct elfstr myelfstr; 
	struct elfstr *elfdata = &myelfstr;
	if (elfdata == NULL){printf("no memory for structure elfdata\n"); mu_assert("",0);}

	elfdata = start_and_load(elfdata, filename, 0x3000);
	mu_assert("file not existant or path incorrect", elfdata->report != 101);
	mu_assert("file is not elf", elfdata->report != 102);

	struct mipsstr mymips;
	struct mipsstr *mips = &mymips;

	vaddr32 addr = 0x3001;

	mips = elfreadbyte(mips, elfdata->memory, addr);

	mu_assert("address not assigned to any segment", mips->report != 501);
	mu_assert("seg->content is null", mips->report != 502);

	mu_assert("there was a problem in reading", mips->report == 0);

	mu_assert("byte read incorrectly",mips->bdata == 0x09);

	
	// segment *seg = get_seg_by_name(elfdata->memory, ".text");
	// print_segment_raw_content(seg);

	return 0;

}

static char * test_readwordmemory()
{
	char *filename = "test/test_elf.o";

	struct elfstr myelfstr; 
	struct elfstr *elfdata = &myelfstr;
	if (elfdata == NULL){printf("no memory for structure elfdata\n"); mu_assert("",0);}

	elfdata = start_and_load(elfdata, filename, 0x3000);

	struct mipsstr mymips;
	struct mipsstr *mips = &mymips;

	vaddr32 addr = 0x3000;

	mips = elfreadword(mips, elfdata->memory, addr);

	mu_assert("address not assigned to any segment", mips->report != 1);
	mu_assert("seg->content is null", mips->report != 2);

	mu_assert("there was a problem in reading", mips->report == 0);

	// printf("0x%x\n", mips->wdata);

	mu_assert("word read incorrectly",mips->wdata == 0x2009000c);


	
	// segment *seg = get_seg_by_name(elfdata->memory, ".text");
	// print_segment_raw_content(seg);

	return 0;

}


static char * test_get_seg_size()
{
	char *filename = "test/test_elf.o";

	struct elfstr myelfstr; 
	struct elfstr *elfdata = &myelfstr;
	if (elfdata == NULL){printf("no memory for structure elfdata\n"); mu_assert("",0);}

	elfdata = start_and_load(elfdata, filename, 0x3000);

	struct mipsstr mymips;
	struct mipsstr *mips = &mymips;


	uint32_t a;
	a = get_seg_size(elfdata->memory, ".text");
	mu_assert("size of text is wrong", a == 24);
	a = get_seg_size(elfdata->memory, ".data");
	mu_assert("size of text is wrong", a == 4);

	return 0;

}

static char * test_get_seg_start()
{
	char *filename = "test/test_elf.o";

	struct elfstr myelfstr; 

	struct mipsstr mymips;
	struct mipsstr *mips = &mymips;
	mips->elfdata = malloc(sizeof(mips->elfdata));

	if (mips->elfdata == NULL){printf("no memory for structure elfdata\n"); mu_assert("",0);}

	mips->elfdata = start_and_load(mips->elfdata, filename, 0x3000);


	vaddr32 a;
	a = get_seg_start(mips->elfdata->memory, ".text");
	// printf("start of text: 0x%x\n",a);
	mu_assert("start of text is wrong", a == 0x3000);
	a = get_seg_start(mips->elfdata->memory, ".data");
	// printf("start of data: 0x%x\n",a);
	mu_assert("start of text is wrong", a == 0x4000);

	return 0;

}


// static char * test_start_mem()
// {
// 	struct elfstr *elfdata;
// 	elfdata = start_mem(elfdata);

// 	printf("\n------ Memory: sections without ELF file loaded------\n") ;
// 	print_mem(elfdata->memory);
// 	stab32_print( elfdata->symtab);

// 	return 0;

// }

 
 static char * all_tests() {
     mu_run_test(test_start_and_load);
     printf("test_start_and_load passed\n");
     mu_run_test(test_writebytememory);
     printf("test_writebytememory passed\n");
     mu_run_test(test_readbytememory);
     printf("test_readbytememory passed\n");
     mu_run_test(test_writewordmemory);
     printf("test_writewordmemory passed\n");
     mu_run_test(test_readwordmemory);
     printf("test_readwordmemory passed\n");  
     mu_run_test(test_get_seg_size);
     printf("test_get_seg_size passed\n");  
     mu_run_test(test_get_seg_start);
     printf("test_get_seg_start passed\n"); 
     return 0;
 }
 
 int main(int argc, char **argv) {


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