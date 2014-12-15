/**
 * @file main.c
 * @author Luciano Mantovani
 * @date October 2014
 * @brief file containing the main function. It starts the program and calls the principal functions
 * 
 *
 *
 **/
#include "headers.h"
#include "elfmanager.h"
#include "disassembler.h"
#include "environment.h"
#include "lookup.h"
#include "errors.h"

void hashregisters();
struct mipsstr *initregisters(struct mipsstr *mips);
void finish(struct mipsstr *mips);


/**
* @brief the main function
*
* -initializes the general mips structure which holds all the simulator general information.
*
* -initializes the registers and creates the hash table of the registers using the function lookup.
* this function was taken from the book "C Programming" by Dennis Ritchie and Brian Kernighan.
* The complete set of functions are hash(), lookup(), and install(). They allow the creation of hash tables.
* 
* -if entered with arguments, will try to initialize a memory from an elf file
* 
* -loads all the operation codes
* 
* -initializes the breakpoint array
*
*
* -after all of this is done, it will run the environment in an endless loop, until "exit" is entered
**/
int main(int argc, char *argv[])
{
	// struct mipsstr mymips;
	struct mipsstr *mips = (struct mipsstr *) malloc(sizeof(struct mipsstr));
	if(mips == NULL){printf("no memory for mips! exiting...\n"); exit(0);}
	struct elfstr myelfdata;
	mips->elfdata = (struct elfstr *) malloc(sizeof(struct elfstr));/*malloc(sizeof(mips->elfdata));*/
	if(mips->elfdata == NULL){printf("no memory for mips! exiting...\n"); exit(0);}

	mips->entry = malloc(MAXSIZE);
	if(mips->entry == NULL){printf("no memory for mips! exiting...\n"); exit(0);}

	// mips->disasm_output = malloc(80);
	// if(mips->disasm_output == NULL){printf("no memory for mips! exiting...\n"); exit(0);}

	mips->fl_file_loaded = false;
	mips->fl_exit = false;

	hashregisters();
	mips = initregisters(mips);
	int error = load_opcodes();
	if(error < 0)
	{
		printf("error loading codes\n");
		finish(mips);
	}
	int i;
	for(i = 0; i < MAXBREAKPOINTS; i++)
		mips->breakpoints[i] = 0xFFFFFFFF;



	if((mips->filename = argv[1]) != NULL && argv[2] != NULL)
		{
			mips->fl_file_loaded = true;
			uint start_mem = (int)strtol(argv[2], (char**)NULL,0);
			mips->elfdata = start_and_load(mips->elfdata,argv[1], start_mem);
			relocate_segment(mips, ".text");
    		relocate_segment(mips, ".data");

			mips->report = mips->elfdata->report;
			if(mips->report > 0)
			{
				report(mips->report);
			}
			else
			{
				mips->fl_file_loaded = true;

				printf("\n---NEW FILE LOADED:  %s ---\n",argv[1]);
				int j = 0;
				int i;
			    print_mem(mips->elfdata->memory);
			    for (i=0; i<NB_SECTIONS; i++) {
			        if (is_in_symbols(section_names[i],mips->elfdata->symtab)) {
	       				print_segment_raw_content(&mips->elfdata->memory->seg[j]);
			            j++;
			        }
			    }
			    segment *segtext = get_seg_by_name(mips->elfdata->memory, ".text");
			    mips->PC = segtext->start._32;
			}		
		}
	else
	{
		printf("starting emulator with no elf file loaded!\n");
		if(argv[2] == NULL)
		{
			printf("no address for memory start specified\n");
		}

		printf("to load new file: load <file> <start of memory>\n");
	}
	while(1)
	{
	runenv(mips);
	if(mips->fl_exit)
		break;
	}

	finish(mips);
	return 0;
	
}
/**
 * @brief we clean up before leaving
 */
void finish(struct mipsstr *mips)
{
	free(mips->entry);
	// free(mips->disasm_output);
	if(mips->fl_file_loaded)
	{
		destroy_mem(mips->elfdata);
		free(mips->elfdata);
	}
	free(mips);

	exit(0);
}

/**
*@brief initializes the registers, giving them a portion of memory and setting to 0 their content
**/
struct mipsstr *initregisters(struct mipsstr *mips)
{
	int i;
	for(i = 0; i < 32; i++)
	{
		mips->regs[i] = malloc( sizeof(int) );
		*(mips->regs[i]) = 0;
	}
	mips->hi = malloc( sizeof(int) );
	mips->lo = malloc( sizeof(int) );
	*(mips->hi) = 0;
	*(mips->lo) = 0;

	return mips;
}

/**
*@brief sets the hash table that holds the names of the registers, and its identifier (number)
**/
void hashregisters()
{
	install("$zero", "0");
	install("$at", "1");
	install("$v0", "2");
	install("$v1", "3");
	install("$a0", "4");
	install("$a1", "5");
	install("$a2", "6");
	install("$a3", "7");
	install("$t0", "8");
	install("$t1", "9");
	install("$t2", "10");
	install("$t3", "11");
	install("$t4", "12");
	install("$t5", "13");
	install("$t6", "14");
	install("$t7", "15");
	install("$s0", "16");
	install("$s1", "17");
	install("$s2", "18");
	install("$s3", "19");
	install("$s4", "20");
	install("$s5", "21");
	install("$s6", "22");
	install("$s7", "23");
	install("$t8", "24");
	install("$t9", "25");
	install("$k0", "26");
	install("$k1", "27");
	install("$gp", "28");
	install("$sp", "29");
	install("$fp", "30");
	install("$ra", "31");
}