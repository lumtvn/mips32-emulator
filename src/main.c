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

void hashregisters();
struct ptype *initregisters(struct ptype *mips);


/**
* @brief the main function
*
* -initializes the general mips structure which holds all the simulator general information.
*
* -initializes the registers and creates the hash table of the registers using the function lookup.
* this function was taken from the book "C Programming" by Dennis Ritchie and Brian Kernighan.
* The complete set of functions are hash(), lookup(), and install(). They allow the creation of hash tables.
*
* -creates a single memory block in which the emulator will work, reading and wirting memory slots.
* the functionality to create many memory blocks and asingn tags to them is not yet implemented
*
*
* -after all of this is done, it will run the environment in an endless loop, until "exit" is entered
**/
int main(int argc, char *argv[])
{
	// struct ptype mymips;
	struct ptype *mips = malloc(sizeof(mips));
	if(mips == NULL){printf("no memory for mips! exiting...\n"); exit(0);}
	struct elfstr myelfdata;
	mips->elfdata = &myelfdata;/*malloc(sizeof(mips->elfdata));*/
	// if(mips->elfdata == NULL){printf("no memory for mips! exiting...\n"); exit(0);}

	mips->entry = malloc(MAXSIZE);
	if(mips->entry == NULL){printf("no memory for mips! exiting...\n"); exit(0);}

	mips->fl_file_loaded = false;
	mips->fl_exit = false;

	hashregisters();
	mips = initregisters(mips);

	if((mips->filename = argv[1]) != NULL)
		{
			mips->fl_file_loaded = true;
			mips->elfdata = start_and_load(mips->elfdata,argv[1]);				
		}
	else
	{
		printf("starting emulator with no elf file loaded!\n");
	}
	while(1)
	{
	runenv(mips);
	if(mips->fl_exit)
		break;
	}

	free(mips->entry);
	// free(mips->elfdata);
	free(mips);
	return 0;
	
}

/**
*@brief initializes the registers, giving them a portion of memory and setting to 0 their content
**/
struct ptype *initregisters(struct ptype *mips)
{
	int i;
	for(i = 0; i < 32; i++)
	{
		mips->regs[i] = malloc( sizeof(int) );
		*(mips->regs[i]) = 0;
	}
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